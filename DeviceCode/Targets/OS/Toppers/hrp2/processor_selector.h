////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// #if !defined(PLATFORM_ARM_LINUX) || !defined(PLATFORM_ARM_OS_PORT)
// ERROR - WE SHOULD NOT INCLUDE THIS HEADER IF NOT BUILDING A LINUX PLATFORM
// #endif

/////////////////////////////////////////////////////////
//
// processor and features
#ifndef _PLATFORM_TOPPERSHRP2ONEV3_SELECTOR_H_
#define _PLATFORM_TOPPERSHRP2ONEV3_SELECTOR_H_ 1

#define PLATFORM_ToppersHRP2ONEV3_DEFINED

/////////////////////////////////////////////////////////
//
// macros
//

#ifndef GLOBAL_LOCK
#define GLOBAL_LOCK(x)             SmartPtr_IRQ x
#define DISABLE_INTERRUPTS()       SmartPtr_IRQ::ForceDisabled()
#define ENABLE_INTERRUPTS()        SmartPtr_IRQ::ForceEnabled()
#define INTERRUPTS_ENABLED_STATE() SmartPtr_IRQ::GetState()
#endif

#ifndef GLOBAL_LOCK_SOCKETS
#define GLOBAL_LOCK_SOCKETS(x)     SmartPtr_IRQ x
#endif

#ifndef ASSERT_IRQ_MUST_BE_OFF
#if defined(_DEBUG)
#define ASSERT_IRQ_MUST_BE_OFF()   ASSERT(!SmartPtr_IRQ::GetState())
#define ASSERT_IRQ_MUST_BE_ON()    ASSERT( SmartPtr_IRQ::GetState())
#else
#define ASSERT_IRQ_MUST_BE_OFF()
#define ASSERT_IRQ_MUST_BE_ON()
#endif
#endif

void SystemState_SetNoLock  ( SYSTEM_STATE State );
void SystemState_ClearNoLock( SYSTEM_STATE State );
BOOL SystemState_QueryNoLock( SYSTEM_STATE State );


//
// macros
//
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//
// constants
//

#if !defined(USART_TX_XOFF_TIMEOUT_INFINITE)
#define USART_TX_XOFF_TIMEOUT_INFINITE   0xFFFFFFFF
#endif

// USART_TX_XOFF_TIMEOUT_TICKS = the number of ticks to leave TX in the XOFF state.  The 
// timeout is a failsafe so that if the XON is lost or an spurious XOFF is received the 
// TX won't be off indefinitely.
//
// The platform selector file should override this value, default to 1min
#if !defined(USART_TX_XOFF_TIMEOUT_TICKS) 
#define USART_TX_XOFF_TIMEOUT_TICKS      (CPU_TicksPerSecond() * 60)
#endif

//
// constants
//
/////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////
//
// macros
//    
#define UNUSED_GPIO_PULLDOWN(x) {  }
#define UNUSED_GPIO_PULLUP(x)   {  }
#define UNUSED_GPIO_DISABLED(x) {  }
//
// macros
//
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//
// global functions
//

//
// global functions
//
/////////////////////////////////////////////////////////

#endif // _PLATFORM_TOPPERSHRP2ONEV3_SELECTOR_H_ 1
//
