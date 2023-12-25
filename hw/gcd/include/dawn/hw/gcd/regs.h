
#ifndef DAWN_HW_GCD_REGS_H_
#define DAWN_HW_GCD_REGS_H_

#include <dawn/hw/iobase.h>
#include <dawn/hw/spi/regs.h> /* defines for AUXSPI stuff */


#define REG_ROMCTRL_ADDR (IO_GCD_BASE + 4)
#define REG_ROMCMD_ADDR (IO_GCD_BASE + 8)
#define REG_KEY2SEED0L_ADDR (IO_GCD_BASE + 0x10)
#define REG_KEY2SEED1L_ADDR (IO_GCD_BASE + 0x14)
#define REG_KEY2SEED0H_ADDR (IO_GCD_BASE + 0x18)
#define REG_KEY2SEED1H_ADDR (IO_GCD_BASE + 0x1c)
#define REG_ROMRESP_ADDR (IO_BASE + 0x00100010)

#define REG_ROMCTRL2_ADDR (IO_GCD2_BASE + 4)
#define REG_ROMCMD2_ADDR (IO_GCD2_BASE + 8)
#define REG_KEY2SEED0L2_ADDR (IO_GCD2_BASE + 0x10)
#define REG_KEY2SEED1L2_ADDR (IO_GCD2_BASE + 0x14)
#define REG_KEY2SEED0H2_ADDR (IO_GCD2_BASE + 0x18)
#define REG_KEY2SEED1H2_ADDR (IO_GCD2_BASE + 0x1a)
#define REG_ROMRESP2_ADDR (IO_BASE + 0x00102010)

#define REG_ROMCTRL (*(volatile uint32_t*)REG_ROMCTRL_ADDR)
#define REG_ROMCMD (*(volatile uint64_t*)REG_ROMCMD_ADDR)
#define REG_KEY2SEED0L (*(volatile uint32_t*)REG_KEY2SEED0L_ADDR)
#define REG_KEY2SEED1L (*(volatile uint32_t*)REG_KEY2SEED1L_ADDR)
#define REG_KEY2SEED0H (*(volatile uint16_t*)REG_KEY2SEED0H_ADDR)
#define REG_KEY2SEED1H (*(volatile uint16_t*)REG_KEY2SEED1H_ADDR)
#define REG_ROMRESP (*(volatile uint32_t*)REG_ROMRESP_ADDR)

#define REG_ROMCTRL2 (*(volatile uint32_t*)REG_ROMCTRL2_ADDR)
#define REG_ROMCMD2 (*(volatile uint64_t*)REG_ROMCMD2_ADDR)
#define REG_KEY2SEED0L2 (*(volatile uint32_t*)REG_KEY2SEED0L2_ADDR)
#define REG_KEY2SEED1L2 (*(volatile uint32_t*)REG_KEY2SEED1L2_ADDR)
#define REG_KEY2SEED0H2 (*(volatile uint16_t*)REG_KEY2SEED0H2_ADDR)
#define REG_KEY2SEED1H2 (*(volatile uint16_t*)REG_KEY2SEED1H2_ADDR)
#define REG_ROMRESP2 (*(volatile uint32_t*)REG_ROMRESP2_ADDR)


#define REG_ROMCTRL_KEY1_GAP1LEN_Lsb  0
#define REG_ROMCTRL_KEY2_ENABLE_Lsb  13
#define REG_ROMCTRL_SE_Lsb           14
#define REG_ROMCTRL_KEY2_APPSEED_Lsb 15
#define REG_ROMCTRL_KEY1_GAP2LEN_Lsb 16
#define REG_ROMCTRL_KEY2_ENCCMD_Lsb  22
#define REG_ROMCTRL_DATA_STAT_Lsb    23
#define REG_ROMCTRL_BLOCKSIZE_Lsb    24
#define REG_ROMCTRL_CLKDIV_Lsb       27
#define REG_ROMCTRL_KEY1DUMMYCLK_Lsb 28
#define REG_ROMCTRL_NRESET_Lsb       29
#define REG_ROMCTRL_DATADIRWR_Lsb    30
#define REG_ROMCTRL_BLOCK_STAT_Lsb   31

#define REG_ROMCTRL_KEY1_GAP1LEN_Msk (0x1fff<<REG_ROMCTRL_KEY1_GAP1LEN_Lsb)
#define REG_ROMCTRL_KEY2_ENABLE_Msk  (1<<REG_ROMCTRL_KEY2_ENABLE_Lsb)
#define REG_ROMCTRL_SE_Msk           (1<<REG_ROMCTRL_SE_Lsb)
#define REG_ROMCTRL_KEY2_APPSEED_Msk (1<<REG_ROMCTRL_KEY2_APPSEED_Lsb)
#define REG_ROMCTRL_KEY1_GAP2LEN_Msk (0x3f<<REG_ROMCTRL_KEY1_GAP2LEN_Lsb)
#define REG_ROMCTRL_KEY2_ENCCMD_Msk  (1<<REG_ROMCTRL_KEY2_ENCCMD_Lsb)
#define REG_ROMCTRL_DATA_STAT_Msk    (1<<REG_ROMCTRL_DATA_STAT_Lsb)
#define REG_ROMCTRL_BLOCKSIZE_Msk    (7<<REG_ROMCTRL_BLOCKSIZE_Lsb)
#define REG_ROMCTRL_CLKDIV_Msk       (1<<REG_ROMCTRL_CLKDIV_Lsb)
#define REG_ROMCTRL_KEY1DUMMYCLK_Msk (1<<REG_ROMCTRL_KEY1DUMMYCLK_Lsb)
#define REG_ROMCTRL_NRESET_Msk       (1<<REG_ROMCTRL_NRESET_Lsb)
#define REG_ROMCTRL_DATADIRWR_Msk    (1<<REG_ROMCTRL_DATADIRWR_Lsb)
#define REG_ROMCTRL_BLOCK_STAT_Msk   (1<<REG_ROMCTRL_BLOCK_STAT_Lsb)

#endif

