
#ifndef DAWN_HW_SIO_STRUCT_H_
#define DAWN_HW_SIO_STRUCT_H_

#include <stdint.h>

#include <dawn/hw/iobase.h>

#ifndef ARM7
#error "SIO is exclusive to the ARM7!"
#endif


struct sio_hw {
	uint8_t rtc;
};


#define REG_SIO_HW (*(volatile struct rtc_hw*)IO_SIO_BASE)

#endif

