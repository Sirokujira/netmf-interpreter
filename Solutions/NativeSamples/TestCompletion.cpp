////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2012 Kentaro Sekimoto  All rights reserved.
////////////////////////////////////////////////////////////////////////////
/*
 * TestEvent.cpp
 *
 *  Created on: 2011/12/24
 *      Author: Kentaro Sekimoto
 */
#include <tinyhal.h>

#ifdef TEST_COMPLETION

#define TEST_PERIOD 500000
#define TEST_COUNT 100

extern UINT64 g_target_count;

static HAL_COMPLETION  g_Completion;
static volatile UINT32 g_count = 0;

void CompletionEvent(void *arg)
{
    UINT32 *cnt = (UINT32 *)arg;
    if (*cnt <= TEST_COUNT) {
        dbg_printf("t%0x:%016llx\r\n", *cnt, HAL_Time_CurrentTicks());
        dbg_printf("c%0x:%016llx\r\n", *cnt, g_target_count);
        g_Completion.EnqueueDelta64(TEST_PERIOD);
    }
    *cnt += 1;
}

void TestCompletion(void)
{
    int i = 0;
    DebuggerPort_Initialize(COM1);
    g_Completion.InitializeForISR((HAL_CALLBACK_FPN)CompletionEvent, (void *)&g_count);
    g_Completion.EnqueueDelta64(TEST_PERIOD);
    dbg_printf("t*:%016llx\r\n", HAL_Time_CurrentTicks());
    dbg_printf("c*:%016llx\r\n", g_target_count);
    while (true) {
        if (g_count > TEST_COUNT)
            break;
    }
}
#endif
