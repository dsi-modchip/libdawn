
#ifndef DAWN_HW_SPI_REGS_H_
#define DAWN_HW_SPI_REGS_H_

#include <dawn/hw/iobase.h>

#define REG_AUXSPICNT_ADDR  (IO_GCD_BASE + 0)
#define REG_AUXSPIDATA_ADDR (IO_GCD_BASE + 2)

#define REG_AUXSPI2CNT_ADDR  (IO_GCD2_BASE + 0)
#define REG_AUXSPI2DATA_ADDR (IO_GCD2_BASE + 2)

#define REG_AUXSPICNT  (*(volatile uint16_t*)REG_AUXSPICNT_ADDR)
#define REG_AUXSPIDATA (*(volatile uint8_t*)REG_AUXSPIDATA_ADDR)

#define REG_AUXSPI2CNT  (*(volatile uint16_t*)REG_AUXSPI2CNT_ADDR)
#define REG_AUXSPI2DATA (*(volatile uint8_t*)REG_AUXSPI2DATA_ADDR)

#ifdef ARM7
#define REG_SPICNT_ADDR  (IO_SPI_BASE + 0)
#define REG_SPIDATA_ADDR (IO_SPI_BASE + 2)

#define REG_SPICNT  (*(volatile uint16_t*)REG_SPICNT_ADDR)
#define REG_SPIDATA (*(volatile uint8_t*)REG_SPIDATA_ADDR)
#endif

#define REG_AUXSPICNT_BAUDRATE_Msk 3
#define REG_AUXSPICNT_BAUDRATE_Lsb 0

#define REG_AUXSPICNT_CSHOLD_Msk 0x40
#define REG_AUXSPICNT_CSHOLD_Lsb 6

#define REG_AUXSPICNT_BUSY_Msk 0x80
#define REG_AUXSPICNT_BUSY_Lsb 7

/* 0=parallellROM 1=SPI */
#define REG_AUXSPICNT_CHIPSEL_Msk 0x2000
#define REG_AUXSPICNT_CHIPSEL_Lsb 13

#define REG_AUXSPICNT_IE_Msk 0x4000
#define REG_AUXSPICNT_IE_Lsb 14

#define REG_AUXSPICNT_ENABLE_Msk 0x8000
#define REG_AUXSPICNT_ENABLE_Lsb 15

#ifdef ARM7
#define REG_SPICNT_BAUDRATE_Msk 7
#define REG_SPICNT_BAUDRATE_Lsb 0

#define REG_SPICNT_BUSY_Msk 0x80
#define REG_SPICNT_BUSY_Lsb 7

/* 0=pmic, 1=fwflash, 2=tsc/codec, 3=N/A */
#define REG_SPICNT_CHIPSEL_Msk 3
#define REG_SPICNT_CHIPSEL_Lsb 8

#define REG_SPICNT_XFERSIZE_Msk 0x400
#define REG_SPICNT_XFERSIZE_Lsb 10

#define REG_SPICNT_CSHOLD_Msk 0x800
#define REG_SPICNT_CSHOLD_Lsb 11

#define REG_SPICNT_IE_Msk 0x4000
#define REG_SPICNT_IE_Lsb 14

#define REG_SPICNT_ENABLE_Msk 0x8000
#define REG_SPICNT_ENABLE_Lsb 15
#endif

#endif

