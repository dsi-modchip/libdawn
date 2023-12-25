
#ifndef DAWN_HW_I2C_H_
#define DAWN_HW_I2C_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <dawn/hw/i2c/regs.h>
#include <dawn/hw/i2c/struct.h>

bool i2c_read_blocking_raw(bool start, bool stop, int delay, size_t n, uint8_t* data);
bool i2c_write_blocking_raw(bool start, bool stop, int delay, size_t n, const uint8_t* data);

bool i2c_read_blocking(uint8_t addr, uint8_t reg, size_t n, uint8_t* data);
bool i2c_write_blocking(uint8_t addr, uint8_t reg, size_t n, const uint8_t* data);

#endif

