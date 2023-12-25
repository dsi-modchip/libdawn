
#ifndef DAWN_HW_IOBASE_H_
#define DAWN_HW_IOBASE_H_

#include <dawn/hw/addrspace.h>

/* NOTE: this file needs to be includable from assembly sources */

#if ARM9
#define IO_PPUA_BASE   (IO_BASE + 0x0000)
#define IO_DMA_BASE    (IO_BASE + 0x00b0)
#define IO_TIMER_BASE  (IO_BASE + 0x0100)
#define IO_INPUT_BASE  (IO_BASE + 0x0130)
#define IO_PXI_BASE    (IO_BASE + 0x0180)
#define IO_GCD_BASE    (IO_BASE + 0x01a0)
#define IO_SPI_BASE    (IO_BASE + 0x01c0)
#define IO_IRQ_BASE    (IO_BASE + 0x0200)
#define IO_MEMORY_BASE (IO_BASE + 0x0200)
#define IO_VIDEO_BASE  (IO_BASE + 0x0240)
#define IO_MATH_BASE   (IO_BASE + 0x0280)
#define IO_POWER_BASE  (IO_BASE + 0x0300)
#define IO_GPU_BASE    (IO_BASE + 0x0320)
#define IO_PPUB_BASE   (IO_BASE + 0x1000)
#define IO_USG_BASE    (IO_BASE + 0x1080)

#define IO_GCD2_BASE   (IO_BASE + 0x21a0)

#define IO_SCFG_BASE   (IO_BASE + 0x4000)
#define IO_NWRAM_BASE  (IO_BASE + 0x4040)
#define IO_NDMA_BASE   (IO_BASE + 0x4100)
#define IO_CAM_BASE    (IO_BASE + 0x4200)
#define IO_DSP_BASE    (IO_BASE + 0x4300)
#endif

#if ARM7
#define IO_PPUA_BASE   (IO_BASE + 0x0000)
#define IO_DMA_BASE    (IO_BASE + 0x00b0)
#define IO_TIMER_BASE  (IO_BASE + 0x0100)
#define IO_INPUT_BASE  (IO_BASE + 0x0130)
#define IO_RTC_BASE    (IO_BASE + 0x0138)
#define IO_PXI_BASE    (IO_BASE + 0x0180)
#define IO_CART_BASE   (IO_BASE + 0x01a0)
#define IO_SPI_BASE    (IO_BASE + 0x01c0)
#define IO_IRQ_BASE    (IO_BASE + 0x0200)
#define IO_MEMORY_BASE (IO_BASE + 0x0200)
#define IO_VIDEO_BASE  (IO_BASE + 0x0240)
#define IO_POWER_BASE  (IO_BASE + 0x0300)
#define IO_SOUND_BASE  (IO_BASE + 0x0400)

#define IO_GCD2_BASE   (IO_BASE + 0x21a0)

#define IO_SCFG_BASE   (IO_BASE + 0x4000)
#define IO_NWRAM_BASE  (IO_BASE + 0x4040)
#define IO_NDMA_BASE   (IO_BASE + 0x4100)
#define IO_AES_BASE    (IO_BASE + 0x4400)
#define IO_I2C_BASE    (IO_BASE + 0x4500)
#define IO_MIC_BASE    (IO_BASE + 0x4600)
#define IO_SNDEX_BASE  (IO_BASE + 0x4700)
#define IO_SDMC_BASE   (IO_BASE + 0x4800)
#define IO_SDIO_BASE   (IO_BASE + 0x4a00)
#define IO_GPIO_BASE   (IO_BASE + 0x4c00)
#define IO_FUSE_BASE   (IO_BASE + 0x4d00)
#endif

#define IO_DBG_NOCASH_BASE (IO_BASE + 0x00fffa00)

#endif

