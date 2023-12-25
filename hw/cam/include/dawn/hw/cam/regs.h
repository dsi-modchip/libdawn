
#ifndef DAWN_HW_CAM_REGS_H_
#define DAWN_HW_CAM_REGS_H_

#include <dawn/hw/iobase.h>

#if ARM9

#define REG_CAM_MCNT_ADDR (IO_CAM_BASE + 0)
#define REG_CAM_CNT_ADDR  (IO_CAM_BASE + 2)
#define REG_CAM_DATA_ADDR (IO_CAM_BASE + 4)
#define REG_CAM_SOFS_ADDR (IO_CAM_BASE +16)
#define REG_CAM_EOFS_ADDR (IO_CAM_BASE +20)

#define REG_CAM_MCNT (*(volatile uint16_t*)REG_CAM_MCNT_ADDR)
#define REG_CAM_CNT  (*(volatile uint16_t*)REG_CAM_CNT_ADDR)
#define REG_CAM_DATA (*(volatile uint32_t*)REG_CAM_DATA_ADDR)
#define REG_CAM_SOFS (*(volatile uint32_t*)REG_CAM_SOFS_ADDR)
#define REG_CAM_EOFS (*(volatile uint32_t*)REG_CAM_EOFS_ADDR)

#define REG_CAM_MCNT_STDBY_Lsb 0
#define REG_CAM_MCNT_RST_Lsb   1
#define REG_CAM_MCNT_SYNC_Lsb  2
#define REG_CAM_MCNT_IRCLK_Lsb 3
#define REG_CAM_MCNT_V18_Lsb   4
#define REG_CAM_MCNT_VIO_Lsb   5
#define REG_CAM_MCNT_V28_Lsb   6
#define REG_CAM_MCNT_INI_Lsb   7

#define REG_CAM_CNT_NLINES_Lsb   0
#define REG_CAM_CNT_FIFOERR_Lsb  4
#define REG_CAM_CNT_FLUSH_Lsb    5
#define REG_CAM_CNT_IREQVS_Lsb   8
#define REG_CAM_CNT_IREQBE_Lsb  10
#define REG_CAM_CNT_IE_Lsb      11
#define REG_CAM_CNT_YUV2RGB_Lsb 13
#define REG_CAM_CNT_TRIMEN_Lsb  14
#define REG_CAM_CNT_XFEREN_Lsb  15

#define REG_CAM_MCNT_STDBY_Msk (1<<REG_CAM_MCNT_STDBY_Lsb)
#define REG_CAM_MCNT_RST_Msk   (1<<REG_CAM_MCNT_RST_Lsb)
#define REG_CAM_MCNT_SYNC_Msk  (1<<REG_CAM_MCNT_SYNC_Lsb)
#define REG_CAM_MCNT_IRCLK_Msk (1<<REG_CAM_MCNT_IRCLK_Lsb)
#define REG_CAM_MCNT_V18_Msk   (1<<REG_CAM_MCNT_V18_Lsb)
#define REG_CAM_MCNT_VIO_Msk   (1<<REG_CAM_MCNT_VIO_Lsb)
#define REG_CAM_MCNT_V28_Msk   (1<<REG_CAM_MCNT_V28_Lsb)
#define REG_CAM_MCNT_INI_Msk   (1<<REG_CAM_MCNT_INI_Lsb)

#define REG_CAM_CNT_NLINES_Msk  (15<<REG_CAM_CNT_NLINES_Lsb)
#define REG_CAM_CNT_FIFOERR_Msk (1<<REG_CAM_CNT_FIFOERR_Lsb)
#define REG_CAM_CNT_FLUSH_Msk   (1<<REG_CAM_CNT_FLUSH_Lsb)
#define REG_CAM_CNT_IREQVS_Msk  (3<<REG_CAM_CNT_IREQVS_Lsb)
#define REG_CAM_CNT_IREQBE_Msk  (1<<REG_CAM_CNT_IREQBE_Lsb)
#define REG_CAM_CNT_IE_Msk      (1<<REG_CAM_CNT_IE_Lsb)
#define REG_CAM_CNT_YUV2RGB_Msk (1<<REG_CAM_CNT_YUV2RGB_Lsb)
#define REG_CAM_CNT_TRIMEN_Msk  (1<<REG_CAM_CNT_TRIMEN_Lsb)
#define REG_CAM_CNT_XFEREN_Msk  (1<<REG_CAM_CNT_XFEREN_Lsb)

#endif

#endif

