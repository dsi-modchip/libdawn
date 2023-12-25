
#ifndef DAWN_HW_I2C_STRUCT_H_
#define DAWN_HW_I2C_STRUCT_H_

#include <stdint.h>

#include <dawn/hw/iobase.h>

#ifndef ARM7
#error "I2C is exclusive to the ARM7!"
#endif

struct i2c_hw {
	uint8_t data;
	uint8_t cnt;
};

#define REG_I2C_HW (*(volatile struct i2c_hw*)IO_I2C_BASE)

#endif

