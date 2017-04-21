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
//  Copyright (c) Microsoft Corporation.  All rights reserved.
//  Portions Copyright (c) Kentaro Sekimoto All rights reserved.
//
////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>

// for TouchPanel PAL driver
#define TOUCH_POINT_BUFFER_SIZE            200
#define TOUCH_POINT_RUNNINGAVG_BUFFER_SIZE 4

TouchPoint g_PAL_TouchPointBuffer[TOUCH_POINT_BUFFER_SIZE];
UINT32     g_PAL_TouchPointBufferSize = TOUCH_POINT_BUFFER_SIZE;
TOUCH_PANEL_Point g_PAL_RunningAvg_Buffer[TOUCH_POINT_RUNNINGAVG_BUFFER_SIZE];
UINT32     g_PAL_RunningAvg_Buffer_Size = TOUCH_POINT_RUNNINGAVG_BUFFER_SIZE;

TOUCH_PANEL_CalibrationData g_TouchPanel_Calibration_Config = {-192, -256, 131712, 132800, -2056, -2090};
TOUCH_PANEL_SamplingSettings g_TouchPanel_Sampling_Settings = {1, 2, 400, FALSE, {50, 200, 150, TOUCH_PANEL_SAMPLE_MS_TO_TICKS(50)}};
