/**************************************************************************//**
 * @file     system_ARMCM7.c
 * @brief    CMSIS Device System Source File for
 *           ARMCM7 Device
 * @version  V2.0.0
 * @date     06. April 2023
 ******************************************************************************/
/*
 * Copyright (c) 2009-2023 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#if defined (ARM9)
  #include "ARM946E-S.h"
#else
  #error device not specified!
#endif

#include <dawn/hw/scfg/struct.h>

#define  SYSTEM_CLOCK_(clk)   ((2+2*((clk) & 1))*0x1FF61FEu)
#define  SYSTEM_CLOCK         SYSTEM_CLOCK_(REG_SCFG_HW.clk)

/*----------------------------------------------------------------------------
  System Core Clock Variable
 *----------------------------------------------------------------------------*/
uint32_t SystemCoreClock = SYSTEM_CLOCK_(0);  /* System Core Clock Frequency */


/*----------------------------------------------------------------------------
  System Core Clock update function
 *----------------------------------------------------------------------------*/
void SystemCoreClockUpdate (void)
{
  SystemCoreClock = SYSTEM_CLOCK;
}

/*----------------------------------------------------------------------------
  System initialization function
 *----------------------------------------------------------------------------*/
void SystemInit (void)
{
  SystemCoreClock = SYSTEM_CLOCK;
}
