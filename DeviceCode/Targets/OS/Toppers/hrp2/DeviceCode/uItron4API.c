////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Device Drivers, Ltd.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "uItron4API.h"
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
// #include <sys/time.h> // gettimeofday()
#include <time.h>
// #include <semaphore.h>
#include <ctype.h>    // isdigit(),toupper()
#include <errno.h>    // EAGAIN
// #include <getopt.h>

#if defined(MALLOC_ZEROED)
#define _MAJOR_VER_  5
#else
#define _MAJOR_VER_  1
#endif

#ifdef uItron4_COM_ALWAYS_SER0
#define MY_SERPORT 0
#else
#define MY_SERPORT ComPortNum
#endif

//
// import hal_vsnprintf()
//

// extern int uItron4_vsnprintf(char *buffer, size_t size, char *format, va_list arg );

// Global datas
void *guItron4_CustomHeap;
void *guItron4_Heap;
jmp_buf guItron4_ResetBuffer;


int uItron4_USART_Write( int ComPortNum, const char* Data, size_t size )
{
	size_t result = fwrite(Data, size, 1, stdout);
	return (result > 0 ? size : 0);
}

int uItron4_USART_Read( int ComPortNum, char* Data, size_t size )
{
	size_t result = fread(Data, size, 1, stdin);
	return (result > 0 ? size : 0);
}


void uItron4_debug_printf( const char* format, ... )
{
    char    buffer[256];
    va_list arg_ptr;

    va_start( arg_ptr, format );

	//vsnprintf( buffer, sizeof(buffer)-1, format, arg_ptr );
	// uItron4_vsnprintf( buffer, sizeof(buffer)-1, (char *) format, arg_ptr );

	fwrite(buffer, strlen(buffer), 1, stdout);

    va_end( arg_ptr );
}

void uItron4_Debug_CurrentTicks()
{
	/*
	if (LINUXDBG > 0)
	{
	    struct timeval now;
	    if (gettimeofday(&now, NULL) != 0)
		{
			LINUXDBG_error("gettimeofday %ld\r\n");
	    }
	}
	*/
}

///////////////
//
// Arithmetics
//
double uItron4_ceil(double x)
{
    return(ceil(x));
}

double uItron4_pow(double x, double y)
{
	return(pow(x, y));
}

double uItron4_floor(double x)
{
	return(floor(x));}


double uItron4_fmod(double x, double y)
{	return(fmod(x, y));}

////////////////////////////////////////////////////
//
// Dual Timer
//
#define TIMER_INTERRUPT_PERIOD (50*1000) // 50 ms 
//#define TIMER_INTERRUPT_MARGIN 1000 // 1 ms
#define TIMER_INTERRUPT_MARGIN 333 //
#define TIMER_INTERRUPT_RETRY (500)

static long long period = TIMER_INTERRUPT_PERIOD;
static long long margin = TIMER_INTERRUPT_MARGIN;
static long long retry  = TIMER_INTERRUPT_RETRY;
static int ptimer_status;

// static struct itimerspec ittime;
// static struct itimerspec itzero;
// static struct sigaction sigact;
// static sigset_t masks;
// static timer_t main_timer;
static int irql;
static unsigned int masked;

// static sem_t sync;
// static sem_t block;
// static sem_t timer;
static void set_mask(unsigned int m);
static unsigned int get_mask();

static struct dual_timer
{
    long long checked;
    long long set;
    long long periodic;
    long long sporadic;
    long long nearest;
} master;

long long uItron4_Time_CurrentTicks();
static void timer_set(long long t);
static void periodic_timer_set(long long t);
static void sporadic_timer_set(long long t);

static void timer_zero(struct itimerspec *it)
{
	/*
    it->it_interval.tv_sec = it->it_interval.tv_nsec =
		it->it_value.tv_sec = it->it_value.tv_nsec = 0;
	*/
}

static void timer_clear()
{
    // if (timer_settime(main_timer, 0, &itzero, NULL) != 0)
    //{
    //    LINUXDBG_error("timer_settime\r\n");
    //}
}

long long uItron4_Time_CurrentTicks()
{
	/*
    struct timeval now;

    if (gettimeofday(&now, NULL) != 0)
    {
		LINUXDBG_error("gettimeofday\r\n");
		return 0LL;
    }
    return(now.tv_sec * 1000000LL + now.tv_usec);
	*/

	return 0;
}

// #define print_master(a) \
// 	do { \
// 	 if (LINUXDBG > 5) \
//      LINUXDBG_print("CHK:%06lld, SET:%06lld, PER:%06lld, SPO:%06lld, NEA:%06lld\r\n", \
//       master.checked, \
//       master.set, \
//       master.periodic, \
//       master.sporadic, \
//       master.nearest); \
//    } while (0)

void sporadic_handler()
{
    // print_master();
}

void periodic_handler()
{
    // print_master();

	if (ptimer_status)
    {
		periodic_timer();
    }
}

static void timer_handler(int sig)
{
    long long now = uItron4_Time_CurrentTicks();
    master.checked = now;

    // if(sig != SIGALRM) return;

	/*
	if (sem_trywait(&timer) == EAGAIN)
	{
		timer_set(retry);
	}
	else // got sem
	{
		irql = 1;
        if (now >= master.sporadic)
        {
            sporadic_handler();
            master.nearest = master.periodic;
            master.sporadic = HAL_COMPLETION_IDELEVALUE;
        }
        if (now >= master.periodic)
        {
            master.periodic = now + period; // tentative set befor evaluate
            master.nearest =
                master.periodic > master.sporadic ? master.sporadic : master.periodic;
            periodic_handler();
        }
        periodic_timer_set(master.nearest - now);
		irql = 0;
		sem_post(&timer);
    }
	*/
}

static void timer_set(long long t)
{
    int sec, usec;
	long long t_original = t;

    if (t < margin) // 1ms
    {
        t = margin; // at least 1 ms to next timer
    }
    timer_clear();
    // timer_zero(&ittime);
    usec = t % 1000000;
    sec = t / 1000000;
//     ittime.it_value.tv_sec = sec;      // set secs
//     ittime.it_value.tv_nsec = usec * 1000; // set nsecs

    // if (timer_settime(main_timer, 0, &ittime, NULL) != 0)
    // {
    //    LINUXDBG_error("timer_settime\r\n");
    //}
}

static void periodic_timer_set(long long t)
{
    long long now = uItron4_Time_CurrentTicks();
    long long notify;

    if (t <= 0)
    {
//	    LINUXDBG_error("SET Invalid value: %lld\r\n", t);
        t = 1; // at least 1 ms to next timer
		// uItron4_assert(0);
    }
    notify = now + t;

	if (irql == 0)
	{
	    // sem_wait(&timer);
	}
	
    master.periodic = notify;

    if (notify > master.sporadic)
    {
        master.nearest = master.sporadic;
    }
    else
    {
        master.nearest = notify;
    }
    now = uItron4_Time_CurrentTicks();
    master.set = now;
    timer_set(master.nearest - now);

	if (irql == 0)
	{
	    // sem_post(&timer);
	}
}

static void sporadic_timer_set(long long t)
{
    long long now = uItron4_Time_CurrentTicks();
    long long notify;
    int update_needed = 0;

    if (t <= 0)
    {
//	    LINUXDBG_error("SET Invalid value: %lld\r\n", t);
        t = 1; // at least 1 ms to next timer
		// uItron4_assert(0);
    }
    notify = now + t;

	if (irql == 0)
	{
	    // sem_wait(&timer);
	}
    master.sporadic = notify;

    if (notify > master.periodic)
    {
        master.nearest = master.periodic;
    }
    else
    {
        update_needed = 1;
        master.nearest = notify;
    }

    if (update_needed)
    {
        now = uItron4_Time_CurrentTicks();
        master.set = now;
        timer_set(master.nearest - now);
    }
	if (irql == 0)
	{
	    // sem_post(&timer);
	}
}

int periodic_start()
{
    ptimer_status = 1;

	periodic_timer_set(period);

	return 0;
}

void periodic_terminate()
{
    ptimer_status = 0;

	// timer clear
    // if (timer_settime(main_timer, 0, &itzero, NULL) != 0)
    //{
	//    LINUXDBG_error("timer_settime\r\n");
	//	return;
    // }
    master.periodic = HAL_COMPLETION_IDELEVALUE;
    master.sporadic = HAL_COMPLETION_IDELEVALUE;
    master.nearest = HAL_COMPLETION_IDELEVALUE;
}

void uItron4_Time_Init()
{
    // timer_zero(&ittime);
    // // itzero = ittime;

//    sigact.sa_handler = timer_handler;
//    sigact.sa_flags = 0;
    //sigemptyset(&sigact.sa_mask);
    // sigemptyset(&masks);
    // sigaddset(&masks, SIGALRM);
    masked = 0;

    //if (sigaction(SIGALRM, &sigact, NULL) != 0)
    //{
	//    LINUXDBG_error("sigaction\r\n");
	//	return;
    //}
    // if (timer_create(CLOCK_REALTIME, NULL,&main_timer) != 0)
    // {
	//    LINUXDBG_error("main_timer_create\r\n");
	// 	return;
    // }
	// timer clear
    // if (timer_settime(main_timer, 0, &itzero, NULL) != 0)
    // {
	//    LINUXDBG_error("timer_settime\r\n");
	//	return;
    // }

    master.periodic = HAL_COMPLETION_IDELEVALUE;
    master.sporadic = HAL_COMPLETION_IDELEVALUE;
    master.nearest = HAL_COMPLETION_IDELEVALUE;

	//semaphore
    // sem_init(&sync, 0, 1);
    // sem_init(&block, 0, 1);
    // sem_init(&timer, 0, 1);

    // if (periodic_start() != 0)
	// {
    //     LINUXDBG_error("periodic_start\r\n");
	// 	return;
	// }
}

void uItron4_Time_Exit()
{
	// timer clear
    // if (timer_settime(main_timer, 0, &itzero, NULL) != 0)
    // {
    //    LINUXDBG_error("timer_settime\r\n");
	//	return;
    // }
	
	// timer delete
    // if (timer_delete(main_timer) != 0)
    // {
    //     LINUXDBG_error("timer_delete\r\n");
	//	return;
    // }

	periodic_terminate();

	//semaphore
    // sem_destroy(&timer);
    // sem_destroy(&block);
    // sem_destroy(&sync);
}

void uItron4_Time_SetCompare(unsigned long long CompareValue)
{
	long long estimate = CompareValue - uItron4_Time_CurrentTicks(); // usecs

	if (estimate <= 0)
	{
		// if (LINUXDBG > 2)
			// LINUXDBG_print("estimate<=0:%lld\r\n", estimate);
		return;
	}
	sporadic_timer_set(estimate);
}

void uItron4_Time_Sleep_MicroSeconds(unsigned long uSec)
{
	//if (LINUXDBG > 1)
		// LINUXDBG_print("arg = %0lu\r\n", uSec);

	// usleep(uSec);
}

void uItron4_CPU_Change_State(int status)
{
	switch(status)
	{
	case RESTART:
		uItron4_CPU_Restart();
		break;

	case HIBERNATE:
		// do nothing
		break;

	case SHUTDOWN:
		uItron4_CPU_Shutdown();
		break;

	default:
		break;
	}
}

void uItron4_CPU_Sleep(void)
{
	// pause();
}

void uItron4_CPU_Restart(void)
{
	longjmp(guItron4_ResetBuffer, RESTART);
	/* NOTREACHED */
}

void uItron4_CPU_Shutdown(void)
{
	longjmp(guItron4_ResetBuffer, SHUTDOWN);
	/* NOTREACHED */
}

int uItron4_InterruptsAreEnabled(void)
{
	return(!masked);
}

void uItron4_InterruptEnable(void)
{
	if (!uItron4_InterruptsAreEnabled())
	{
		// if (irql == 0)
		    // sigprocmask(SIG_BLOCK, &masks, NULL);

	    // sem_wait(&sync);
		masked = 0;
		// sem_post(&block);
	    // sem_post(&sync);

		// if (irql == 0)
			// sigprocmask(SIG_UNBLOCK, &masks, NULL);
	}
}

void uItron4_InterruptDisable(void)
{
	if (uItron4_InterruptsAreEnabled())
	{
		// if (irql == 0)
		    // sigprocmask(SIG_BLOCK, &masks, NULL);

	    // sem_wait(&sync);
		masked = 1;
	    // sem_wait(&block);
	    // sem_post(&sync);

		// if (irql == 0)
			// sigprocmask(SIG_UNBLOCK, &masks, NULL);
	}
}

///////////////
//
// Memories
//
void*  uItron4_allocHeap(void)         { return  malloc( (size_t) UITRON4_HEAP_SIZE ); }
void*  uItron4_allocCustomHeap(void)   { return  malloc( (size_t) UITRON4_CUSTOM_HEAP_SIZE ); }
size_t uItron4_HeapSize(void)          { return  UITRON4_HEAP_SIZE; }
size_t uItron4_CustomHeapSize(void)    { return  UITRON4_CUSTOM_HEAP_SIZE; }
void   uItron4_freeHeap ( void*  ptr ) {         free ( ptr ); }

///////////////
//
// Assembly IOs
//
int uItron4_loadAssembly(char *name, char *addr)
{
	int fdi;
    char *p;
	size_t length;
	int total = 0;

    fdi = open(name, O_RDONLY);
	if (fdi < 0)
	{
//        LINUXDBG_error("Open error (%d:%s). assembly file = %s.\r\n", errno, strerror(errno), name);
		return -2;
	}
	p = addr;
	while((length = read(fdi, p, 512)) > 0)
	{
		p += 512;
		total += length;
		if (total >= (128*1024))
		{
//	        LINUXDBG_error("Too big assembly file, over 512*1024 = %s.\r\n", name);
			close(fdi);
			return -3;
		}
	}
	if (length < 0)
	{
//        LINUXDBG_error("Read error (%d:%s). assembly file = %s.\r\n", errno, strerror(errno), name);
		return -4;
	}

	close(fdi);

	return total;
}

///////////////
//
// Load options
//
int uItron4_opt_ticks;        //'T'
int uItron4_opt_ticks_number = 20;
int uItron4_opt_wait;         //'W'
int uItron4_opt_wait_ms = 1;
int uItron4_opt_assert = 1;   //'E' or 'X'

// int uItron4_load_options(int ac, char **av)
int uItron4_load_options()
{
    int opt;

// 	while((opt = getopt(ac, av, "dDeEf:F:t:T:w:W:xXzZ")) != -1)
//     {
//         switch (toupper(opt)) {
//         case 'D':
// #if !defined(BUILD_RTM)
//             uItron4_debug++;
// #endif
//             break;
//         case 'Z':
// #if !defined(BUILD_RTM)
//             uItron4_debug = 0;
// #endif
//             break;
//         case 'T':
//             uItron4_opt_ticks++;    //'T'
//             if (isdigit(*optarg))
//             {
//                 uItron4_opt_ticks_number = atoi(optarg);
//             }
//             else while((toupper(*optarg)) == 'T')
//                 {
//                     uItron4_opt_ticks++;
//                     optarg++;
//                 }
//             break;
//         case 'W':
//             uItron4_opt_wait++;     //'W'
//             if (isdigit(*optarg))
//             {
//                 uItron4_opt_wait_ms = atoi(optarg);
//             }
//             else while((toupper(*optarg)) == 'W')
//                 {
//                     uItron4_opt_wait++;
//                     optarg++;
//                 }
//             if (uItron4_opt_wait_ms == 0)
//                 uItron4_opt_wait_ms = uItron4_opt_wait * 100; // msec
//             break;
// 
//         case 'E':
//             uItron4_opt_assert++;
//             break;
//         case 'X':
//             uItron4_opt_assert = 0;
//             break;
//         case 'F':
//             uItron4_assembly = optarg;
//             break;
// 
//         case '?': /* '?' */
//         default:
//             fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n",
//                 av[0]);
//             exit(EXIT_FAILURE);
//         }
//     }

// 	if (LINUXDBG > 1)
// 	{
// 	    LINUXDBG_print("ac=%d, optind=%d\n", ac, optind);
// 	}
//     if (optind > ac)
//     {
//         LINUXDBG_error("Expected argument after options\n");
//         exit(EXIT_FAILURE);
//     }
//     else if (optind < ac)
//     {
//         uItron4_assembly = av[optind];
//     }

    //
    // uItron4_opt_ticks == 1,2,3,...
    // uItron4_opt_ticks_number == 0~100000...
    //
    if (uItron4_opt_ticks_number > 0)
    {
        // direct number setting of msec
        period = uItron4_opt_ticks_number * 1000;
    }
    else if (uItron4_opt_ticks > 0)
    {
        // 100 msec base setting
        period = uItron4_opt_ticks * 100 * 1000;
    }

#if !defined(BUILD_RTM)
	if (LINUXDBG > 0)
	{
	    // LINUXDBG_print("assembly = %s\r\n", uItron4_assembly);

		// LINUXDBG_print("timer:%d\r\n", period);
		// LINUXDBG_print("ticks:%d\r\n", uItron4_opt_ticks);
		// LINUXDBG_print("ticks_number:%d\r\n", uItron4_opt_ticks_number);
		// LINUXDBG_print("wait:%d\r\n", uItron4_opt_wait);
		// LINUXDBG_print("wait_ms:%d\r\n", uItron4_opt_wait_ms);
		// LINUXDBG_print("assert:%d\r\n", uItron4_opt_assert);
		// LINUXDBG_print("debug:%d\r\n", uItron4_debug);
	}
#endif
	// return optind;
	return 0;
}
