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

#ifndef MBED_I2C_H_
#define MBED_I2C_H_

#define REG(N) \
    RIIC[obj->i2c]->RIICn##N

/* RIICnCR1 */
#define CR1_SDAI  (1 << 0)
#define CR1_SCLI  (1 << 1)
#define CR1_SDAO  (1 << 2)
#define CR1_SCLO  (1 << 3)
#define CR1_SOWP  (1 << 4)
#define CR1_CLO   (1 << 5)
#define CR1_RST   (1 << 6)
#define CR1_ICE   (1 << 7)

/* RIICnCR2 */
#define CR2_ST    (1 << 1)
#define CR2_RS    (1 << 2)
#define CR2_SP    (1 << 3)
#define CR2_NACKF (1 << 4)
#define CR2_TRS   (1 << 5)
#define CR2_MST   (1 << 6)
#define CR2_BBSY  (1 << 7)

/* RIICnMR3 */
#define MR3_ACKBT (1 << 3)
#define MR3_ACKWP (1 << 4)
#define MR3_WAIT  (1 << 6)

/* RIICnSR2 */
#define SR2_TMOF  (1 << 0)
#define SR2_AL    (1 << 1)
#define SR2_START (1 << 2)
#define SR2_STOP  (1 << 3)
#define SR2_NACKF (1 << 4)
#define SR2_RDRF  (1 << 5)
#define SR2_TEND  (1 << 6)
#define SR2_TDRE  (1 << 7)

#define IER_TMOIE   (1 << 0)
#define IER_ALIE    (1 << 1)
#define IER_STIE    (1 << 2)
#define IER_SPIE    (1 << 3)
#define IER_NAKIE   (1 << 4)
#define IER_RIE     (1 << 5)
#define IER_TEIE    (1 << 6)
#define IER_TIE     (1 << 7)

#define FER_MALE    (1 << 2)

#define TIMEOUT_1S    (3600000)  /* Loop counter : Time-out is about 1s. By 3600000 loops, measured value is 969ms. */

void INT_Excep_I2C_TEI0(void);
void INT_Excep_I2C_RI0(void);
void INT_Excep_I2C_TI0(void);
void INT_Excep_I2C_SPI0(void);
void INT_Excep_I2C_STI0(void);
void INT_Excep_I2C_NAKI0(void);
void INT_Excep_I2C_ALI0(void);
void INT_Excep_I2C_TMOI0(void);
void INT_Excep_I2C_TEI1(void);
void INT_Excep_I2C_RI1(void);
void INT_Excep_I2C_TI1(void);
void INT_Excep_I2C_SPI1(void);
void INT_Excep_I2C_STI1(void);
void INT_Excep_I2C_NAKI1(void);
void INT_Excep_I2C_ALI1(void);
void INT_Excep_I2C_TMOI1(void);
void INT_Excep_I2C_TEI2(void);
void INT_Excep_I2C_RI2(void);
void INT_Excep_I2C_TI2(void);
void INT_Excep_I2C_SPI2(void);
void INT_Excep_I2C_STI2(void);
void INT_Excep_I2C_NAKI2(void);
void INT_Excep_I2C_ALI2(void);
void INT_Excep_I2C_TMOI2(void);

#endif /* MBED_I2C_H_ */
