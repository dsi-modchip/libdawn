
#ifndef DAWN_HW_I2C_REGS_H_
#define DAWN_HW_I2C_REGS_H_

#include <dawn/hw/iobase.h>

#ifndef ARM7
#error "I2C is exclusive to the ARM7!"
#endif

#define REG_I2CDATA_ADDR (IO_I2C_BASE + 0)
#define REG_I2CCNT_ADDR  (IO_I2C_BASE + 1)

#define REG_I2CDATA (*(volatile uint8_t*)REG_I2CDATA_ADDR)
#define REG_I2CCNT  (*(volatile uint8_t*)REG_I2CCNT_ADDR)

#define REG_I2CCNT_STOP_Lsb (0)
#define REG_I2CCNT_STOP_Msk (1<<REG_I2CCNT_STOP_Lsb)

#define REG_I2CCNT_START_Lsb (1)
#define REG_I2CCNT_START_Msk (1<<REG_I2CCNT_START_Lsb)

#define REG_I2CCNT_ERROR_Lsb (2)
#define REG_I2CCNT_ERROR_Msk (1<<REG_I2CCNT_ERROR_Lsb)

#define REG_I2CCNT_CNT_Lsb (3)
#define REG_I2CCNT_CNT_Msk (1<<REG_I2CCNT_CNT_Lsb)

#define REG_I2CCNT_ACK_Lsb (4)
#define REG_I2CCNT_ACK_Msk (1<<REG_I2CCNT_ACK_Lsb)

#define REG_I2CCNT_DIR_Lsb (5)
#define REG_I2CCNT_DIR_Msk (1<<REG_I2CCNT_DIR_Lsb)

#define REG_I2CCNT_IE_Lsb (6)
#define REG_I2CCNT_IE_Msk (1<<REG_I2CCNT_IE_Lsb)

#define REG_I2CCNT_BUSY_Lsb (7)
#define REG_I2CCNT_BUSY_Msk (1<<REG_I2CCNT_BUSY_Lsb)

#endif

