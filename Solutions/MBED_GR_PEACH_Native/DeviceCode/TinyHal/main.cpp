////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This file is part of the Microsoft .NET Micro Framework Porting Kit Code Samples and is unsupported. 
// Copyright (c) Microsoft Open Technologies, Inc. All rights reserved.
// 
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use these files except in compliance with the License.
// You may obtain a copy of the License at:
// 
// http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing
// permissions and limitations under the License.
// 
#include <tinyhal.h>
// #include "OsHal.h"

int main(void)
{
    // HAL initialization completed.  Interrupts are enabled.  Jump to the Application routine
    ApplicationEntryPoint();

    debug_printf("main exited!!???.  Halting CPU\r\n");
/*
#if defined(BUILD_RTM)
    CPU_Reset();
#else
    CPU_Halt();
#endif
*/
    return -1;
}
