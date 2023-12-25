
#include <dawn/hw/arm.h>
#include <dawn/hw/i2c/regs.h>
#include <dawn/hw/i2c/struct.h>

#include <dawn/hw/i2c.h>


inline static void wait_busy(void) {
	while (REG_I2C_HW.cnt & REG_I2CCNT_BUSY_Msk) ;
}
inline static bool get_ack(void) {
	wait_busy();
	return REG_I2C_HW.cnt & REG_I2CCNT_ACK_Msk;
}
inline static void delay(int del) {
	for (int i = 0; i < del; ++i) {
		COMPILER_BARRIER();
	}
}


bool i2c_read_blocking_raw(bool start, bool stop, int del, size_t n, uint8_t* data) {
	wait_busy();

	for (size_t i = 0; i < n; ++i) {
		uint8_t cnt = REG_I2CCNT_IE_Msk;
		if (i == 0) {
			if (start) cnt |= REG_I2CCNT_START_Msk;
		} else if (i == n - 1) {
			if (stop) cnt |= REG_I2CCNT_STOP_Msk;
		}

		if (i == n - 1) {
			cnt &= ~REG_I2CCNT_ACK_Msk; // don't send ack
			cnt |=  REG_I2CCNT_ERROR_Msk; // send nak
		} else {
			cnt |=  REG_I2CCNT_ACK_Msk; // send ack
			cnt &= ~REG_I2CCNT_ERROR_Msk; // don't send nak
		}

		cnt |= REG_I2CCNT_DIR_Msk; // read
		REG_I2C_HW.cnt = cnt;

		delay(del);

		REG_I2C_HW.cnt |= REG_I2CCNT_BUSY_Msk; // do xfer 1 byte

		wait_busy();

		data[i] = REG_I2C_HW.data;
	}

	return true;
}
bool i2c_write_blocking_raw(bool start, bool stop, int del, size_t n, const uint8_t* data) {
	wait_busy();

	for (size_t i = 0; i < n; ++i) {
		REG_I2C_HW.data = data[i]; // prepare data to send out

		uint8_t cnt = REG_I2CCNT_IE_Msk;
		if (i == 0) {
			if (start) cnt |= REG_I2CCNT_START_Msk;
		} else if (i == n - 1) {
			if (stop) cnt |= REG_I2CCNT_STOP_Msk;
		}
		//cnt &= ~REG_I2CCNT_DIR_Msk; // write
		REG_I2C_HW.cnt = cnt;

		delay(del);

		REG_I2C_HW.cnt |= REG_I2CCNT_BUSY_Msk; // do xfer 1 byte

		if (!get_ack()) return false; // check for ack
	}

	return true;
}

bool i2c_read_blocking(uint8_t addr, uint8_t reg, size_t n, uint8_t* data) {
	int del = (addr == 0x25) ? 180 : 0;

	uint8_t pre[2];

	pre[0] = (addr << 1) | 1;
	pre[1] = reg;

	if (!i2c_write_blocking_raw(true, false, del, 2, pre)) return false;

	return i2c_read_blocking_raw(true/*restart!*/, true, del, n, data);
}
bool i2c_write_blocking(uint8_t addr, uint8_t reg, size_t n, const uint8_t* data) {
	int del = (addr == 0x25) ? 180 : 0;

	uint8_t pre[2];

	pre[0] = (addr << 1) | 0;
	pre[1] = reg;

	if (!i2c_write_blocking_raw(true, false, del, 2, pre)) return false;

	return i2c_write_blocking_raw(false, true, del, n, data);
}

