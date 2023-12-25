
#ifndef DAWN_HW_DMA_REGS_H_
#define DAWN_HW_DMA_REGS_H_

#include <dawn/hw/iobase.h>

#define REG_DMA_SAD_ADDR(x)   (IO_DMA_BASE + (x)*12 + 0)
#define REG_DMA_DAD_ADDR(x)   (IO_DMA_BASE + (x)*12 + 4)
#define REG_DMA_WCNT_ADDR(x)  (IO_DMA_BASE + (x)*12 + 8)
#define REG_DMA_CNT_ADDR(x)   (IO_DMA_BASE + (x)*12 +10)

#define REG_DMA_SAD(x)  (*(volatile uint32_t*)REG_DMA_SAD_ADDR(x))
#define REG_DMA_DAD(x)  (*(volatile uint32_t*)REG_DMA_DAD_ADDR(x))
#define REG_DMA_WCNT(x) (*(volatile uint16_t*)REG_DMA_WCNT_ADDR(x))
#define REG_DMA_CNT(x)  (*(volatile uint16_t*)REG_DMA_CNT_ADDR(x))

#ifdef ARM9
#define REG_DMA_FDATA_ADDR(x) (IO_DMA_BASE + (x)*4  +48)
#define REG_DMA_FDATA(x) (*(volatile uint32_t*)REG_DMA_FDATA_ADDR(x))
#endif

#define REG_DMA_CNT_DSTCTL_Lsb  5
#define REG_DMA_CNT_SRCCTL_Lsb  7
#define REG_DMA_CNT_REPEAT_Lsb  9
#define REG_DMA_CNT_32BIT_Lsb  10
#define REG_DMA_CNT_MODE_Lsb   11
#define REG_DMA_CNT_IE_Lsb     14
#define REG_DMA_CNT_ENABLE_Lsb 15

#define REG_DMA_CNT_DSTCTL_Msk (3<<REG_DMA_CNT_DSTCTL_Lsb)
#define REG_DMA_CNT_SRCCTL_Msk (3<<REG_DMA_CNT_SRCCTL_Lsb)
#define REG_DMA_CNT_REPEAT_Msk (1<<REG_DMA_CNT_REPEAT_Lsb)
#define REG_DMA_CNT_32BIT_Msk  (1<<REG_DMA_CNT_32BIT_Lsb)
#define REG_DMA_CNT_MODE_Msk   (7<<REG_DMA_CNT_MODE_Lsb)
#define REG_DMA_CNT_IE_Msk     (1<<REG_DMA_CNT_IE_Lsb)
#define REG_DMA_CNT_ENABLE_Msk (1<<REG_DMA_CNT_ENABLE_Lsb)

#define REG_DMA_CNT_SRCDST_INC 0
#define REG_DMA_CNT_SRCDST_DEC 1
#define REG_DMA_CNT_SRCDST_FIX 2
#define REG_DMA_CNT_DST_RELOAD 3

#ifdef ARM9
#define REG_DMA_CNT_MODE_IMMEDIATE 0
#define REG_DMA_CNT_MODE_VBLANK    1
#define REG_DMA_CNT_MODE_HBLANK    2
#define REG_DMA_CNT_MODE_DISPSTART 3
#define REG_DMA_CNT_MODE_DRAMDISP  4
#define REG_DMA_CNT_MODE_NTRCART   5
#define REG_DMA_CNT_MODE_AGBCART   6
#define REG_DMA_CNT_MODE_GXFIFO    7
#elif defined(ARM7)
#define REG_DMA_CNT_MODE_IMMEDIATE 0
#define REG_DMA_CNT_MODE_VBLANK    2
#define REG_DMA_CNT_MODE_NTRCART   4
#define REG_DMA_CNT_MODE_NWMIRQ    6 /**< channels 0 and 2 only */
#define REG_DMA_CNT_MODE_AGBCART   6 /**< channels 1 and 3 only */
#endif

#endif

