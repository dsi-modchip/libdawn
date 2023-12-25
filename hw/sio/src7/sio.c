
#include <dawn/hw/arm.h>

#include <dawn/hw/sio.h>


inline static void delay(int del) {
	for (int i = 0; i < del; ++i) {
		COMPILER_BARRIER();
	}
}

#define DELAY_1US 9 /* 4 cycles/loop iteration */
#define DELAY_5US (DELAY_1US*5)

void sio_read_blocking(size_t nbytes, uint8_t* rxbuf, bool cshold) {
	delay(DELAY_1US);
	// CS high, data input dir
	REG_SIO = (REG_SIO | REG_SIO_DATA_CS_Msk) & ~REG_SIO_DIR_IO_Msk;
	delay(DELAY_1US);

	for (size_t i = 0; i < nbytes; ++i) {
		uint8_t v = 0;

		for (size_t j = 0; j < 8; ++j) {
			// clk falling edge
			REG_SIO &= ~REG_SIO_DATA_CLK_Msk;
			// RTC chip now starts driving the IO line
			delay(DELAY_5US);
			// clk rising edge
			bool bit = REG_SIO & REG_SIO_DATA_IO_Msk;
			REG_SIO |= REG_SIO_DATA_CLK_Msk;
			delay(DELAY_5US);

			if (bit) v |= 1<<j;
		}

		rxbuf[i] = v;
	}

	// deselect chip
	if (!cshold) REG_SIO &= ~REG_SIO_DATA_CS_Msk;
}
void sio_write_blocking(size_t nbytes, const uint8_t* txbuf, bool cshold) {
	delay(DELAY_1US);
	// CS high, data output dir
	REG_SIO = (REG_SIO | REG_SIO_DATA_CS_Msk) | REG_SIO_DIR_IO_Msk;
	delay(DELAY_1US);

	for (size_t i = 0; i < nbytes; ++i) {
		uint8_t v = txbuf[i];

		for (size_t j = 0; j < 8; ++j) {
			uint8_t bit = (v >> j) & 1;

			// clk falling edge, IO line must be driven now
			REG_SIO = (REG_SIO & ~REG_SIO_DATA_CLK_Msk) | (bit << REG_SIO_DATA_IO_Lsb);
			delay(DELAY_5US);
			REG_SIO |= REG_SIO_DATA_CLK_Msk;
			delay(DELAY_5US);
		}
	}

	// deselect chip
	if (!cshold) REG_SIO &= ~REG_SIO_DATA_CS_Msk;
}

