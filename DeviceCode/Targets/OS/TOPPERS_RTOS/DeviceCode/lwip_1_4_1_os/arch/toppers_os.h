/* ----------------------------------------------------------------------
 * $Date:        5. February 2013
 * $Revision:    V1.02
 *
 * Project:      TOPPERS-RTOS API
 * Title:        TOPPERS_os.h RTX header file
 *
 * Version 0.02
 *    Initial Proposal Phase
 * Version 0.03
 *    osKernelStart added, optional feature: main started as thread
 *    osSemaphores have standard behavior
 *    osTimerCreate does not start the timer, added osTimerStart
 *    osThreadPass is renamed to osThreadYield
 * Version 1.01
 *    Support for C++ interface
 *     - const attribute removed from the osXxxxDef_t typedef's
 *     - const attribute added to the osXxxxDef macros
 *    Added: osTimerDelete, osMutexDelete, osSemaphoreDelete
 *    Added: osKernelInitialize
 * Version 1.02
 *    Control functions for short timeouts in microsecond resolution:
 *    Added: osKernelSysTick, osKernelSysTickFrequency, osKernelSysTickMicroSec
 *    Removed: osSignalGet 
 *----------------------------------------------------------------------------
 *
 * Copyright (c) 2013 ARM LIMITED
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  - Neither the name of ARM  nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *---------------------------------------------------------------------------*/


#ifndef _TOPPERS_OS_H
#define _TOPPERS_OS_H

#define osTOPPERS           0x10002      ///< TOPPERS-RTOS API version (main [31:16] .sub [15:0])

#define osTOPPERS_RTX     ((4<<16)|78)   ///< RTOS identification and version (main [31:16] .sub [15:0])

#define osKernelSystemId "RTX V4.78"   ///< RTOS identification string


#define osFeature_MainThread   1       ///< main can be thread
#define osFeature_Pool         1       ///< Memory Pools available
#define osFeature_MailQ        1       ///< Mail Queues available
#define osFeature_MessageQ     1       ///< Message Queues available
#define osFeature_Signals      16      ///< 16 Signal Flags available per thread
#define osFeature_Semaphore    65535   ///< Maximum count for \ref osSemaphoreCreate function
#define osFeature_Wait         0       ///< osWait not available
#define osFeature_SysTick      1       ///< osKernelSysTick functions available

#if defined (__CC_ARM)
#define os_InRegs __value_in_regs      // Compiler specific: force struct in registers
#else
#define os_InRegs
#endif

#include <stdint.h>
#include <stddef.h>

#ifdef  __cplusplus
extern "C"
{
#endif


// ==== Enumeration, structures, defines ====

/// Priority used for thread control.
typedef enum  {
  osPriorityIdle          = -3,          ///< priority: idle (lowest)
  osPriorityLow           = -2,          ///< priority: low
  osPriorityBelowNormal   = -1,          ///< priority: below normal
  osPriorityNormal        =  0,          ///< priority: normal (default)
  osPriorityAboveNormal   = +1,          ///< priority: above normal
  osPriorityHigh          = +2,          ///< priority: high
  osPriorityRealtime      = +3,          ///< priority: realtime (highest)
  osPriorityError         =  0x84        ///< system cannot determine priority or thread has illegal priority
} osPriority;

/// Timeout value.
#define osWaitForever     0xFFFFFFFF     ///< wait forever timeout value

/// Status code values returned by TOPPERS-RTOS functions.
typedef enum  {
  osOK                    =     0,       ///< function completed; no error or event occurred.
  osEventSignal           =  0x08,       ///< function completed; signal event occurred.
  osEventMessage          =  0x10,       ///< function completed; message event occurred.
  osEventMail             =  0x20,       ///< function completed; mail event occurred.
  osEventTimeout          =  0x40,       ///< function completed; timeout occurred.
  osErrorParameter        =  0x80,       ///< parameter error: a mandatory parameter was missing or specified an incorrect object.
  osErrorResource         =  0x81,       ///< resource not available: a specified resource was not available.
  osErrorTimeoutResource  =  0xC1,       ///< resource not available within given time: a specified resource was not available within the timeout period.
  osErrorISR              =  0x82,       ///< not allowed in ISR context: the function cannot be called from interrupt service routines.
  osErrorISRRecursive     =  0x83,       ///< function called multiple times from ISR with same object.
  osErrorPriority         =  0x84,       ///< system cannot determine priority or thread has illegal priority.
  osErrorNoMemory         =  0x85,       ///< system is out of memory: it was impossible to allocate or reserve memory for the operation.
  osErrorValue            =  0x86,       ///< value of a parameter is out of range.
  osErrorOS               =  0xFF,       ///< unspecified RTOS error: run-time error but no other error message fits.
  os_status_reserved      =  0x7FFFFFFF  ///< prevent from enum down-size compiler optimization.
} osStatus;


/// Timer type value for the timer definition.
typedef enum  {
  osTimerOnce             =     0,       ///< one-shot timer
  osTimerPeriodic         =     1        ///< repeating timer
} os_timer_type;

/// Entry point of a thread.
typedef void (*os_pthread) (void const *argument);

/// Entry point of a timer call back function.
typedef void (*os_ptimer) (void const *argument);

// >>> the following data type definitions may shall adapted towards a specific RTOS

/// Thread ID identifies the thread (pointer to a thread control block).
typedef struct os_thread_cb *osThreadId;

/// Timer ID identifies the timer (pointer to a timer control block).
typedef struct os_timer_cb *osTimerId;

/// Mutex ID identifies the mutex (pointer to a mutex control block).
typedef struct os_mutex_cb *osMutexId;

/// Semaphore ID identifies the semaphore (pointer to a semaphore control block).
typedef struct os_semaphore_cb *osSemaphoreId;

/// Pool ID identifies the memory pool (pointer to a memory pool control block).
typedef struct os_pool_cb *osPoolId;

/// Message ID identifies the message queue (pointer to a message queue control block).
typedef struct os_messageQ_cb *osMessageQId;

/// Mail ID identifies the mail queue (pointer to a mail queue control block).
typedef struct os_mailQ_cb *osMailQId;


/// Thread Definition structure contains startup information of a thread.
typedef struct os_thread_def  {
  os_pthread               pthread;    ///< start address of thread function
  osPriority             tpriority;    ///< initial thread priority
  uint32_t               instances;    ///< maximum number of instances of that thread function
  uint32_t               stacksize;    ///< stack size requirements in bytes; 0 is default stack size
} osThreadDef_t;

/// Timer Definition structure contains timer parameters.
typedef struct os_timer_def  {
  os_ptimer                 ptimer;    ///< start address of a timer function
  void                      *timer;    ///< pointer to internal data
} osTimerDef_t;

/// Mutex Definition structure contains setup information for a mutex.
typedef struct os_mutex_def  {
  void                      *mutex;    ///< pointer to internal data
} osMutexDef_t;

/// Semaphore Definition structure contains setup information for a semaphore.
typedef struct os_semaphore_def  {
  void                  *semaphore;    ///< pointer to internal data
} osSemaphoreDef_t;

/// Definition structure for memory block allocation.
typedef struct os_pool_def  {
  uint32_t                 pool_sz;    ///< number of items (elements) in the pool
  uint32_t                 item_sz;    ///< size of an item
  void                       *pool;    ///< pointer to memory for pool
} osPoolDef_t;

/// Definition structure for message queue.
typedef struct os_messageQ_def  {
  uint32_t                queue_sz;    ///< number of elements in the queue
  void                       *pool;    ///< memory array for messages
} osMessageQDef_t;

/// Definition structure for mail queue.
typedef struct os_mailQ_def  {
  uint32_t                queue_sz;    ///< number of elements in the queue
  uint32_t                 item_sz;    ///< size of an item
  void                       *pool;    ///< memory array for mail
} osMailQDef_t;

/// Event structure contains detailed information about an event.
typedef struct  {
  osStatus                 status;     ///< status code: event or error information
  union  {
    uint32_t                    v;     ///< message as 32-bit value
    void                       *p;     ///< message or mail as void pointer
    int32_t               signals;     ///< signal flags
  } value;                             ///< event value
  union  {
    osMailQId             mail_id;     ///< mail id obtained by \ref osMailCreate
    osMessageQId       message_id;     ///< message id obtained by \ref osMessageCreate
  } def;                               ///< event definition
} osEvent;


//  ==== Kernel Control Functions ====
//  ==== Thread Management ====
//  ==== Generic Wait Functions ====
//  ==== Timer Management Functions ====
//  ==== Signal Management ====
//  ==== Mutex Management ====
//  ==== Semaphore Management Functions ====
//  ==== Memory Pool Management Functions ====
//  ==== Message Queue Management Functions ====
//  ==== Mail Queue Management Functions ====


#ifdef  __cplusplus
}
#endif

#endif  // _TOPPERS_OS_H
