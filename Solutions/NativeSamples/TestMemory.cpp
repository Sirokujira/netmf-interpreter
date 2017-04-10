////////////////////////////////////////////////////////////////////////////
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
//  Copyright (c) Kentaro Sekimoto All rights reserved.
//
////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>

#ifdef TEST_MEMORY

#define TEST_MEMORY_COUNT   3
#if defined(PLATFORM_RX62N_CQ_FRK_RX62N)
#define TEST_MEMORY_TOP     0x60000000      // CS0
#define TEST_MEMORY_SIZE    0x00080000      // 512KB
#elif defined(PLATFORM_RX62N_RXMEGA)
#define TEST_MEMORY_TOP     0x08000000      // SDRAM
#define TEST_MEMORY_SIZE    0x01000000      // 16MB
#else
#error "Platform information not specified!"
#endif

void memory_dump(unsigned long addr, int len);

void memory_fill(unsigned long addr, char c, int len)
{
    int i;
    char *p = (char *)addr;
    for (i = 0; i < len; i++) {
        *p++ = c;
    }
}

void memory_fill_order(unsigned long addr, int len)
{
    int i;
    char *p = (char *)addr;
    for (i = 0; i < len; i++) {
        *p++ = (char)(i & 0xff);
    }
}

int memory_compare(unsigned long addr, char c, int len)
{
    int i;
    char *p = (char *)addr;
    for (i = 0; i < len; i++) {
        if (*p++ != c)
            return 0;
    }
    return 1;
}

int memory_compare_order(unsigned long addr, int len, unsigned long *err_addr)
{
    int i;
    char *p = (char *)addr;
    for (i = 0; i < len; i++) {
        if (*p != (char)(i & 0xff)) {
            *err_addr = (unsigned long)p;
            return 0;
        }
        p++;
    }
    return 1;
}

int memory_check(unsigned long addr, char c, int len)
{
    memory_fill(addr, c, len);
    if (!memory_compare(addr, c, len)) {
        debug_printf("memory NG\r\n");
        memory_dump(addr, len);
        return 0;
    }
    return 1;
}

int memory_check_order(unsigned long addr, int len)
{
    unsigned long err_addr;
    memory_fill_order(addr, len);
    if (!memory_compare_order(addr, len, &err_addr)) {
        debug_printf("memory NG at %08x\r\n", err_addr);
        memory_dump((err_addr & 0xffffff00), 256);
        return 0;
    }
    return 1;
}

void TestMemory(void)
{
    int i;
    int flag;
    for (i = 0; i < TEST_MEMORY_COUNT; i++) {
        flag = memory_check_order(TEST_MEMORY_TOP, TEST_MEMORY_SIZE);
        flag &= memory_check(TEST_MEMORY_TOP, 0x00, 256);
        flag &= memory_check(TEST_MEMORY_TOP+256, 0x55, 256);
        flag &= memory_check(TEST_MEMORY_TOP+512, 0xaa, 256);
        flag &= memory_check(TEST_MEMORY_TOP+768, 0xff, 256);
        if (flag)
            debug_printf("%3d memory OK\r\n", i);
        else
            debug_printf("%3d memory NG\r\n", i);
    }
}
#endif
