////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>

//--//
// adding your native codes here...

#ifdef PLATFORM_ARM_TOPPERSHRP2
#include "tinyclr_application.h"
#include "tinyhal.h"
#endif

#include "uItron4API.h"
////////////////////////////////////////////////////////////////////////////////////////////////////

#define DebuggerPort_Flush(p) \
	fflush(stdout)

#define DebuggerPort_Write(port, buffer, len ) \
	fwrite(buffer, len, 1, stdout)

#ifdef vsnprintf
#undef vsnprintf
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////

/*
#ifdef __cplusplus
extern "C"
{
void uItron4_assert(int i);
}
#endif
*/

#ifdef __cplusplus
extern "C"
{
void MFabort(void);
}
#endif

#ifdef __cplusplus
extern "C"
{
void MFmain();
} // extern "C"
#endif

/*
extern "C"
{
  int uItron4_vsnprintf(char *buffer, size_t size, char *format, va_list arg )
  {
	return(vsnprintf(buffer, size, format, arg));
  }
} // extern "C"
*/

#if !defined(BUILD_RTM)
int uItron4_debug;
#endif
char *uItron4_assembly;
char TinyClr_Dat_Start[128*1024]; //128KB for Assembly
char TinyClr_Dat_End  [1       ];

#if !defined(BUILD_RTM)

void debug_printf(char const* format, ... )
{
    char    buffer[256];
    va_list arg_ptr;

    va_start( arg_ptr, format );

	int len = vsnprintf( buffer, sizeof(buffer)-1, format, arg_ptr );
    // flush existing characters
    DebuggerPort_Flush( USART_DEFAULT_PORT );

    // write string
    DebuggerPort_Write( USART_DEFAULT_PORT, buffer, len );

    // flush new characters
    DebuggerPort_Flush( USART_DEFAULT_PORT );

    va_end( arg_ptr );
}

void lcd_printf(char const * format,...)
{
    char    buffer[256];
    va_list arg_ptr;

    va_start( arg_ptr, format );

	int len = vsnprintf( buffer, sizeof(buffer)-1, format, arg_ptr );
    // flush existing characters
    DebuggerPort_Flush( USART_DEFAULT_PORT );

    // write string
    DebuggerPort_Write( USART_DEFAULT_PORT, buffer, len );

    // flush new characters
    DebuggerPort_Flush( USART_DEFAULT_PORT );

    va_end( arg_ptr );
}

#endif

/////////////////////////////////////////////////////////////////////

void InitCRuntime()
{
    //setlocale( LC_ALL, "" );
}

/////////////////////////////////////////////////////////////////////

#ifdef hal_strlen_s
#undef hal_strlen_s
int hal_strlen_s(char const*str)
{
    return(strlen(str));
}
#define hal_strlen_s( str ) strlen(str)
#endif

#ifdef hal_strncmp_s
#undef hal_strncmp_s
int hal_strncmp_s(const char* str1, const char* str2, size_t num )
{
    return(strncmp(str1, str2, num));
}
#define hal_strncmp_s( str1, str2, num ) strncmp(str1, str2, num)
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////

/*
#ifdef __cplusplus
void uItron4_assert(int i)
{
	ASSERT(i);
}
#endif
*/

#ifdef __cplusplus
void MFabort(void)
{
}
#endif


void* CustomHeap();
void* Heap();
size_t CustomHeapSize();
size_t HeapSize();

size_t HeapSize()       { return(uItron4_HeapSize()); }
size_t CustomHeapSize() { return(uItron4_CustomHeapSize()); }
void*  Heap()           { debug_printf(" H:%p\r\n", guItron4_Heap);       return (guItron4_Heap); }
void*  CustomHeap()     { debug_printf("CH:%p\r\n", guItron4_CustomHeap); return (guItron4_CustomHeap); }

// Dummy declaration
int HeapBegin;
int HeapEnd;
int CustomHeapBegin;
int CustomHeapEnd;

//-//
void MFmain()
{
	int size;
	int ReturnValue;

	uItron4_assembly = (char *) "TINYCLR.DAT";
	// uItron4_assembly = (char *) "TINYCLR.afx";

	// 引数チェック
	// タイマ周りの設定
	uItron4_load_options();
	// if (LINUXDBG > 0)
	// {
	// 	LINUXDBG_print("debug:%d, CWD:%s, Assembly:%s \r\n", LINUXDBG, getcwd(NULL, 0), uItron4_assembly);
	// }

	// Assembly IOs
	// 左デバイス?, 右メモリ領域?
	size = uItron4_loadAssembly(uItron4_assembly, TinyClr_Dat_Start);
	if (size <= 0)
	{
		// LINUXDBG_print("##### MFmain: assembly load Error ! (%d) #####\r\n", size);
		//return;
	}
	// if (LINUXDBG > 3)
	// {
	// 	LINUXDBG_print("Assembly:%s loaded size:%d\r\n", uItron4_assembly, size);
	// }

	guItron4_Heap = uItron4_allocHeap();
	if (NULL == guItron4_Heap)
	{
		// LINUXDBG_error("##### MFmain: allocHeap Error ! #####\r\n");
	}
	
	guItron4_CustomHeap = uItron4_allocCustomHeap();
	if (NULL == guItron4_CustomHeap)
	{
		// LINUXDBG_error("##### MFmain: allocCustomHeap Error ! #####\r\n");
	}


REBOOT:
    if((ReturnValue = setjmp(guItron4_ResetBuffer)) == 0)
    {
		InitCRuntime();

#ifdef PLATFORM_ARM_TOPPERSHRP2
		CPU_Initialize();

		HAL_Time_Initialize();

		HAL_Initialize();
#endif

		if (LINUXDBG > 0)
		{
			// LINUXDBG_print("HAL: H=%p(%d), C=%p(%d)\r\n", 				guItron4_Heap, uItron4_HeapSize(),				guItron4_CustomHeap, uItron4_CustomHeapSize());
		}
#ifdef PLATFORM_ARM_TOPPERSHRP2
		ApplicationEntryPoint();
#endif
		HAL_Uninitialize();
		// HAL_Time_Uninitialize();
	}
	else if (ReturnValue == RESTART)
	{
		debug_printf("Restarted by longjmp()...\n");
		goto REBOOT;
	}
	else if (ReturnValue == SHUTDOWN)
	{
		debug_printf("Terminate by shutdown from longjmp()...\n");
	}
	else
	{
		debug_printf("Unknown terminate by longjmp()...\n");
	}
	// LINUXDBG_print("MFmain Terminated.\n");

	uItron4_freeHeap(guItron4_Heap);
	uItron4_freeHeap(guItron4_CustomHeap);
}

///////////////////////////////////////////////////////////////////////////////////////////

// Helpers //

extern "C" {

	void periodic_timer()
	{
		// SOCKETS_ProcessSocketActivity(SOCK_SOCKET_ERROR);

		// this also schedules the next one, if there is one
		// HAL_COMPLETION::DequeueAndExec();
	}
}
///////////////////////////////////////////////////////////////////////////////////////////
