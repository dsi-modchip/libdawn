
#ifndef DAWN_HW_GCD_STRUCT_H_
#define DAWN_HW_GCD_STRUCT_H_

#include <stdint.h>

#include <dawn/hw/iobase.h>
#include <dawn/hw/spi/struct.h>

struct gcd_hw {
	struct spi_hw auxspi;
	uint32_t romctrl;
	uint64_t romcmd;
	uint32_t key1seed0l;
	uint32_t key1seed1l;
	uint16_t key1seed0h;
	uint16_t key1seed1h;
};

#define REG_GCD_HW  (*(volatile struct gcd_hw*)IO_GCD_BASE)
#define REG_GCD2_HW (*(volatile struct gcd_hw*)IO_GCD2_BASE)

#endif

