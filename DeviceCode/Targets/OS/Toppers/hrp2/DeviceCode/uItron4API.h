////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Device Drivers, Ltd.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _UITRON4_API_H_
#define _UITRON4_API_H_

// #include <tgmath.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <setjmp.h>

#if !defined(BUILD_RTM)
#define UITRON4_DEBUG_LEVEL 5
#endif

#define UITRON4_COM_ALWAYS_SER0 1

#define UITRON4_DEFAULT_DBG_PORT 0
#define UITRON4_DEFAULT_LCD_PORT 0
#define UITRON4_DEFAULT_SER_PORT 0
#define UITRON4_DEFAULT_TCP_PORT 0

#define HAL_COMPLETION_IDELEVALUE 0x000FFFFFFFFFFFFFull

#define UITRON4_HEAP_SIZE ((1024*1024)+(256*1024)) //1.25MB,0x00140000
#define UITRON4_CUSTOM_HEAP_SIZE 0

extern void *guItron4_CustomHeap;
extern void *guItron4_Heap;
extern jmp_buf guItron4_ResetBuffer;
extern char *uItron4_assembly;

// #define LINUXDBG_error(f, a) uItron4_debug_printf("** ERROR ** %s: " f, __FUNCTION__, ##a)
#if !defined(BUILD_RTM)
extern int uItron4_debug;
#define LINUXDBG uItron4_debug
// #define LINUXDBG_print(f,a) uItron4_debug_printf("# %s: " f, __FUNCTION__, ##a)
#else
#define LINUXDBG 0
#define LINUXDBG_print(f,a)
#endif

#ifdef __cplusplus
extern "C" {
#endif

//
// Timers
//
enum wakeup_actions
{
	INITIALIZE = 0,
    WAKEUP = 1,    /* Indicate current status to others */
    SLEEPING = 2,  /* Indicate current status to others */
    ALARM = 3,     /* External Instruction to set alarm */
    HIBERNATE = 4, /* External Instruction to hibernate, deep sleep */
    SHUTDOWN = 5,  /* External Instruction to exit, shutdown */
    RESTART = 6,   /* External Instruction to restart, reboot */
    EXIT = 9       /* External Instruction to stop this timer, terminate */
};

//
//	Debug Options //
//
extern int uItron4_opt_ticks;        //'T'
extern int uItron4_opt_ticks_number;
extern int uItron4_opt_wait;         //'W'
extern int uItron4_opt_wait_ms;
extern int uItron4_opt_assert;       //'E' or 'X'
//
//	C_syntax_APIs()... //
//
extern int uItron4_USART_Write( int ComPortNum, const char* Data, size_t size );
extern int uItron4_USART_Read( int ComPortNum, char* Data, size_t size );

extern double uItron4_ceil(double x);
extern double uItron4_pow(double x, double y);
extern double uItron4_floor(double x);
extern double uItron4_fmod(double x, double y);

extern void uItron4_Time_Init();
extern void uItron4_Time_Exit();
extern long long uItron4_Time_CurrentTicks();
extern void uItron4_Time_SetCompare(unsigned long long CompareValue);
extern void uItron4_Time_Sleep_MicroSeconds(unsigned long uSec);

extern void uItron4_CPU_Change_State(int status);
extern void uItron4_CPU_Restart(void);
extern void uItron4_CPU_Sleep(void);
extern void uItron4_CPU_Shutdown(void);

extern int  uItron4_InterruptsAreEnabled(void);
extern void uItron4_InterruptEnable(void);
extern void uItron4_InterruptDisable(void);

extern void*  uItron4_allocHeap(void);
extern void*  uItron4_allocCustomHeap(void);
extern size_t uItron4_HeapSize(void);
extern size_t uItron4_CustomHeapSize(void);
extern void   uItron4_freeHeap ( void*  ptr );

extern int    uItron4_loadAssembly(char *name, char *addr);
// extern int    uItron4_load_options(int ac, char **av);
extern int    uItron4_load_options();

extern void uItron4_debug_printf( const char* format, ... );

extern void periodic_timer();

extern void uItron4_assert(int i);

#ifdef __cplusplus
}
#endif  // __cplusplus

//
//
//
// typedef unsigned int uint32_t;

#endif // _UITRON4_API_H_
// EOF =======================================================================
