
#ifndef DAWN_HW_DSP_REGS_H_
#define DAWN_HW_DSP_REGS_H_

#ifndef ARM9
#error "The DSP is exclusive to the ARM9"
#endif

#include <dawn/hw/iobase.h>

#define REG_DSP_PDATA_ADDR  (IO_DSP_BASE + 0x00)
#define REG_DSP_PADR_ADDR   (IO_DSP_BASE + 0x04)
#define REG_DSP_PCFG_ADDR   (IO_DSP_BASE + 0x08)
#define REG_DSP_PSTS_ADDR   (IO_DSP_BASE + 0x0c)
#define REG_DSP_PSEM_ADDR   (IO_DSP_BASE + 0x10)
#define REG_DSP_PMASK_ADDR  (IO_DSP_BASE + 0x14)
#define REG_DSP_PCLEAR_ADDR (IO_DSP_BASE + 0x18)
#define REG_DSP_SEM_ADDR    (IO_DSP_BASE + 0x1c)

#define REG_DSP_CMD0_ADDR (IO_DSP_BASE + 0x20)
#define REG_DSP_REP0_ADDR (IO_DSP_BASE + 0x24)
#define REG_DSP_CMD1_ADDR (IO_DSP_BASE + 0x28)
#define REG_DSP_REP1_ADDR (IO_DSP_BASE + 0x2c)
#define REG_DSP_CMD2_ADDR (IO_DSP_BASE + 0x30)
#define REG_DSP_REP2_ADDR (IO_DSP_BASE + 0x34)


#define REG_DSP_PDATA  (*(volatile uint16_t*)REG_DSP_PDATA_ADDR)
#define REG_DSP_PADR   (*(volatile uint16_t*)REG_DSP_PADR_ADDR)
#define REG_DSP_PCFG   (*(volatile uint16_t*)REG_DSP_PCFG_ADDR)
#define REG_DSP_PSTS   (*(volatile uint16_t*)REG_DSP_PSTS_ADDR)
#define REG_DSP_PSEM   (*(volatile uint16_t*)REG_DSP_PSEM_ADDR)
#define REG_DSP_PMASK  (*(volatile uint16_t*)REG_DSP_PMASK_ADDR)
#define REG_DSP_PCLEAR (*(volatile uint16_t*)REG_DSP_PCLEAR_ADDR)
#define REG_DSP_SEM    (*(volatile uint16_t*)REG_DSP_SEM_ADDR)

#define REG_DSP_CMD0 (*(volatile uint16_t*)REG_DSP_CMD0_ADDR)
#define REG_DSP_REP0 (*(volatile uint16_t*)REG_DSP_REP0_ADDR)
#define REG_DSP_CMD1 (*(volatile uint16_t*)REG_DSP_CMD1_ADDR)
#define REG_DSP_REP1 (*(volatile uint16_t*)REG_DSP_REP1_ADDR)
#define REG_DSP_CMD2 (*(volatile uint16_t*)REG_DSP_CMD2_ADDR)
#define REG_DSP_REP2 (*(volatile uint16_t*)REG_DSP_REP2_ADDR)


#define REG_DSP_PCFG_RST_Lsb            0
#define REG_DSP_PCFG_XFER_ADDRINC_Lsb   1
#define REG_DSP_PCFG_XFER_DATALEN_Lsb   2
#define REG_DSP_PCFG_XFER_START_Lsb     4
#define REG_DSP_PCFG_IE_RDFIFO_FULL_Lsb 5
#define REG_DSP_PCFG_IE_RDFIFO_NEMP_Lsb 6
#define REG_DSP_PCFG_IE_WRFIFO_FULL_Lsb 7
#define REG_DSP_PCFG_IE_WRFIFO_NEMP_Lsb 8
#define REG_DSP_PCFG_IE_REP0_Lsb        9
#define REG_DSP_PCFG_IE_REP1_Lsb       10
#define REG_DSP_PCFG_IE_REP2_Lsb       11
#define REG_DSP_PCFG_XFER_MODE_Lsb     12

#define REG_DSP_PCFG_RST_Msk            (1<<REG_DSP_PCFG_RST_Lsb)
#define REG_DSP_PCFG_XFER_ADDRINC_Msk   (1<<REG_DSP_PCFG_XFER_ADDRINC_Lsb)
#define REG_DSP_PCFG_XFER_DATALEN_Msk   (3<<REG_DSP_PCFG_XFER_DATALEN_Lsb)
#define REG_DSP_PCFG_XFER_START_Msk     (1<<REG_DSP_PCFG_XFER_START_Lsb)
#define REG_DSP_PCFG_IE_RDFIFO_FULL_Msk (1<<REG_DSP_PCFG_IE_RDFIFO_FULL_Lsb)
#define REG_DSP_PCFG_IE_RDFIFO_NEMP_Msk (1<<REG_DSP_PCFG_IE_RDFIFO_NEMP_Lsb)
#define REG_DSP_PCFG_IE_WRFIFO_FULL_Msk (1<<REG_DSP_PCFG_IE_WRFIFO_FULL_Lsb)
#define REG_DSP_PCFG_IE_WRFIFO_NEMP_Msk (1<<REG_DSP_PCFG_IE_WRFIFO_NEMP_Lsb)
#define REG_DSP_PCFG_IE_REP0_Msk        (1<<REG_DSP_PCFG_IE_REP0_Lsb)
#define REG_DSP_PCFG_IE_REP1_Msk        (1<<REG_DSP_PCFG_IE_REP1_Lsb)
#define REG_DSP_PCFG_IE_REP2_Msk        (1<<REG_DSP_PCFG_IE_REP2_Lsb)
#define REG_DSP_PCFG_XFER_MODE_Msk      (15<<REG_DSP_PCFG_XFER_MODE_Lsb)


#define REG_DSP_PSTS_RDBUSY_Lsb      0
#define REG_DSP_PSTS_WRBUSY_Lsb      1
#define REG_DSP_PSTS_PRST_Lsb        2
#define REG_DSP_PSTS_RDFIFO_FULL_Lsb 5
#define REG_DSP_PSTS_RDFIFO_NEMP_Lsb 6
#define REG_DSP_PSTS_WRFIFO_FULL_Lsb 7
#define REG_DSP_PSTS_WRFIFO_NEMP_Lsb 8
#define REG_DSP_PSTS_SEMIRQ_Lsb      9
#define REG_DSP_PSTS_REP0_UPD_Lsb   10 /**< GBATEK says 0=updated but it's actually 1=updated */
#define REG_DSP_PSTS_REP1_UPD_Lsb   11 /**< GBATEK says 0=updated but it's actually 1=updated */
#define REG_DSP_PSTS_REP2_UPD_Lsb   12 /**< GBATEK says 0=updated but it's actually 1=updated */
#define REG_DSP_PSTS_CMD0_ACK_Lsb   13
#define REG_DSP_PSTS_CMD1_ACK_Lsb   14
#define REG_DSP_PSTS_CMD2_ACK_Lsb   15

#define REG_DSP_PSTS_RDBUSY_Msk      (1<<REG_DSP_PSTS_RDBUSY_Lsb)
#define REG_DSP_PSTS_WRBUSY_Msk      (1<<REG_DSP_PSTS_WRBUSY_Lsb)
#define REG_DSP_PSTS_PRST_Msk        (1<<REG_DSP_PSTS_PRST_Lsb)
#define REG_DSP_PSTS_RDFIFO_FULL_Msk (1<<REG_DSP_PSTS_RDFIFO_FULL_Lsb)
#define REG_DSP_PSTS_RDFIFO_NEMP_Msk (1<<REG_DSP_PSTS_RDFIFO_NEMP_Lsb)
#define REG_DSP_PSTS_WRFIFO_FULL_Msk (1<<REG_DSP_PSTS_WRFIFO_FULL_Lsb)
#define REG_DSP_PSTS_WRFIFO_NEMP_Msk (1<<REG_DSP_PSTS_WRFIFO_NEMP_Lsb)
#define REG_DSP_PSTS_SEMIRQ_Msk      (1<<REG_DSP_PSTS_SEMIRQ_Lsb)
#define REG_DSP_PSTS_REP0_UPD_Msk    (1<<REG_DSP_PSTS_REP0_UPD_Lsb)
#define REG_DSP_PSTS_REP1_UPD_Msk    (1<<REG_DSP_PSTS_REP1_UPD_Lsb)
#define REG_DSP_PSTS_REP2_UPD_Msk    (1<<REG_DSP_PSTS_REP2_UPD_Lsb)
#define REG_DSP_PSTS_CMD0_ACK_Msk    (1<<REG_DSP_PSTS_CMD0_ACK_Lsb)
#define REG_DSP_PSTS_CMD1_ACK_Msk    (1<<REG_DSP_PSTS_CMD1_ACK_Lsb)
#define REG_DSP_PSTS_CMD2_ACK_Msk    (1<<REG_DSP_PSTS_CMD2_ACK_Lsb)

#endif

