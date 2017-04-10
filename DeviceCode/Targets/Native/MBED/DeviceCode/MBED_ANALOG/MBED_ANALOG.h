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

#ifndef RZA1_ANALOG_H_
#define RZA1_ANALOG_H_

struct RZA1_AD_Driver
{
    static const UINT32 c_Channels = 8;
    static const UINT32 c10bits_Pins[c_Channels];
    static const UINT32 c12bits_Pins[c_Channels];
    INT32 m_Precision;
};

#endif /* RZA1_ANALOG_H_ */
