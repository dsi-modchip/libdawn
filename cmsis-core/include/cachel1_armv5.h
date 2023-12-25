/******************************************************************************
 * @file     cachel1_armv7.h
 * @brief    CMSIS Level 1 Cache API for Armv7-M and later
 * @version  V1.0.1
 * @date     19. April 2021
 ******************************************************************************/
/*
 * Copyright (c) 2020-2021 Arm Limited. All rights reserved.
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

#if   defined ( __ICCARM__ )
  #pragma system_include         /* treat file as system include file for MISRA check */
#elif defined (__clang__)
  #pragma clang system_header    /* treat file as system include file */
#endif

#ifndef ARM_CACHEL1_ARMV5_H
#define ARM_CACHEL1_ARMV5_H

#include <dawn/hw/cpu/cache.h>

/**
  \ingroup  CMSIS_Core_FunctionInterface
  \defgroup CMSIS_Core_CacheFunctions Cache Functions
  \brief    Functions that configure Instruction and Data cache.
  @{
 */

#ifndef __L1C_DCACHE_LINE_SIZE
#define __L1C_DCACHE_LINE_SIZE  32U /*!< Cortex-M7 cache line size is fixed to 32 bytes (8 words). See also register L1C_CCSIDR */
#endif

#ifndef __L1C_ICACHE_LINE_SIZE
#define __L1C_ICACHE_LINE_SIZE  32U /*!< Cortex-M7 cache line size is fixed to 32 bytes (8 words). See also register L1C_CCSIDR */
#endif

/**
  \brief   Enable I-Cache
  \details Turns on I-Cache
  */
__STATIC_FORCEINLINE void L1C_EnableICache (void)
{
  cache_icache_enable(true);
}


/**
  \brief   Disable I-Cache
  \details Turns off I-Cache
  */
__STATIC_FORCEINLINE void L1C_DisableICache (void)
{
  cache_icache_enable(false);
}


/**
  \brief   Invalidate I-Cache
  \details Invalidates I-Cache
  */
__STATIC_FORCEINLINE void L1C_InvalidateICache (void)
{
  cache_icache_invalidate();
}


/**
  \brief   I-Cache Invalidate by address
  \details Invalidates I-Cache for the given address.
           I-Cache is invalidated starting from a 32 byte aligned address in 32 byte granularity.
           I-Cache memory blocks which are part of given address + given size are invalidated.
  \param[in]   addr    address
  \param[in]   isize   size of memory block (in number of bytes)
*/
__STATIC_FORCEINLINE void L1C_InvalidateICache_by_Addr (volatile void *addr, int32_t isize)
{
  cache_icache_invalidate_range(addr, (size_t)isize);
}


/**
  \brief   Enable D-Cache
  \details Turns on D-Cache
  */
__STATIC_FORCEINLINE void L1C_EnableDCache (void)
{
  cache_dcache_enable(true);
}


/**
  \brief   Disable D-Cache
  \details Turns off D-Cache
  */
__STATIC_FORCEINLINE void L1C_DisableDCache (void)
{
  cache_dcache_enable(false);
}


/**
  \brief   Invalidate D-Cache
  \details Invalidates D-Cache
  */
__STATIC_FORCEINLINE void L1C_InvalidateDCache (void)
{
  cache_dcache_invalidate();
}


/**
  \brief   Clean D-Cache
  \details Cleans D-Cache
  */
__STATIC_FORCEINLINE void L1C_CleanDCache (void)
{
  cache_dcache_flush();
}


/**
  \brief   Clean & Invalidate D-Cache
  \details Cleans and Invalidates D-Cache
  */
__STATIC_FORCEINLINE void L1C_CleanInvalidateDCache (void)
{
  cache_dcache_flush_invalidate();
}


/**
  \brief   D-Cache Invalidate by address
  \details Invalidates D-Cache for the given address.
           D-Cache is invalidated starting from a 32 byte aligned address in 32 byte granularity.
           D-Cache memory blocks which are part of given address + given size are invalidated.
  \param[in]   addr    address
  \param[in]   dsize   size of memory block (in number of bytes)
*/
__STATIC_FORCEINLINE void L1C_InvalidateDCache_by_Addr (volatile void *addr, int32_t dsize)
{
  cache_dcache_invalidate_range(addr, (size_t)dsize);
}


/**
  \brief   D-Cache Clean by address
  \details Cleans D-Cache for the given address
           D-Cache is cleaned starting from a 32 byte aligned address in 32 byte granularity.
           D-Cache memory blocks which are part of given address + given size are cleaned.
  \param[in]   addr    address
  \param[in]   dsize   size of memory block (in number of bytes)
*/
__STATIC_FORCEINLINE void L1C_CleanDCache_by_Addr (volatile void *addr, int32_t dsize)
{
  cache_dcache_flush_range(addr, (size_t)dsize);
}


/**
  \brief   D-Cache Clean and Invalidate by address
  \details Cleans and invalidates D_Cache for the given address
           D-Cache is cleaned and invalidated starting from a 32 byte aligned address in 32 byte granularity.
           D-Cache memory blocks which are part of given address + given size are cleaned and invalidated.
  \param[in]   addr    address (aligned to 32-byte boundary)
  \param[in]   dsize   size of memory block (in number of bytes)
*/
__STATIC_FORCEINLINE void L1C_CleanInvalidateDCache_by_Addr (volatile void *addr, int32_t dsize)
{
  cache_dcache_flush_invalidate_range(addr, (size_t)dsize);
}

/*@} end of CMSIS_Core_CacheFunctions */

#endif /* ARM_CACHEL1_ARMV5_H */
