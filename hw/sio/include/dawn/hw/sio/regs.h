
#ifndef DAWN_HW_SIO_REGS_H_
#define DAWN_HW_SIO_REGS_H_

#include <dawn/hw/iobase.h>

#ifndef ARM7
#error "SIO is exclusive to the ARM7!"
#endif


#define REG_SIO_ADDR (IO_RTC_BASE)
#define REG_SIO (*(volatile uint8_t*)REG_SIO_ADDR)


#define REG_SIO_DATA_R8_Lsb 0
#define REG_SIO_DATA_R9_Lsb 1
#define REG_SIO_DATA_RA_Lsb 2
#define REG_SIO_DIR_R8_Lsb  4
#define REG_SIO_DIR_R9_Lsb  5
#define REG_SIO_DIR_RA_Lsb  6

#define REG_SIO_DATA_IO_Lsb  0
#define REG_SIO_DATA_CLK_Lsb 1
#define REG_SIO_DATA_CS_Lsb  2
#define REG_SIO_DIR_IO_Lsb   4
#define REG_SIO_DIR_CLK_Lsb  5
#define REG_SIO_DIR_CS_Lsb   6

#define REG_SIO_DATA_R8_Msk (1<<REG_SIO_DATA_R8_Lsb)
#define REG_SIO_DATA_R9_Msk (1<<REG_SIO_DATA_R9_Lsb)
#define REG_SIO_DATA_RA_Msk (1<<REG_SIO_DATA_RA_Lsb)
#define REG_SIO_DIR_R8_Msk (1<<REG_SIO_DIR_R8_Lsb)
#define REG_SIO_DIR_R9_Msk (1<<REG_SIO_DIR_R9_Lsb)
#define REG_SIO_DIR_RA_Msk (1<<REG_SIO_DIR_RA_Lsb)


#define REG_SIO_DATA_IO_Msk (1<<REG_SIO_DATA_IO_Lsb)
#define REG_SIO_DATA_CLK_Msk (1<<REG_SIO_DATA_CLK_Lsb)
#define REG_SIO_DATA_CS_Msk (1<<REG_SIO_DATA_CS_Lsb)
#define REG_SIO_DIR_IO_Msk (1<<REG_SIO_DIR_IO_Lsb)
#define REG_SIO_DIR_CLK_Msk (1<<REG_SIO_DIR_CLK_Lsb)
#define REG_SIO_DIR_CS_Msk (1<<REG_SIO_DIR_CS_Lsb)

#define REG_SIO_DATA_Msk (7<<REG_SIO_DATA_R8_Lsb)
#define REG_SIO_DIR_Msk  (7<<REG_SIO_DIR_R8_Lsb)

#endif

