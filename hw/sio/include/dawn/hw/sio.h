
#ifndef DAWN_HW_SIO_H_
#define DAWN_HW_SIO_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef ARM7
#error "SIO is exclusive to the ARM7!"
#endif

#include <dawn/hw/sio/regs.h>
#include <dawn/hw/sio/struct.h>

inline static void sio_init_io(void) {
	// init clock&cs out; clk high, cs low
	REG_SIO = REG_SIO_DIR_CS_Msk|REG_SIO_DIR_CLK_Msk
	        | REG_SIO_DATA_CLK_Msk;
}

void sio_read_blocking(size_t nbytes, uint8_t* rxbuf, bool cshold);
void sio_write_blocking(size_t nbytes, const uint8_t* txbuf, bool cshold);

#endif

