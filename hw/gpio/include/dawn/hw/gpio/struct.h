
#ifndef DAWN_HW_GPIO_STRUCT_H_
#define DAWN_HW_GPIO_STRUCT_H_

#include <stdint.h>

#include <dawn/hw/iobase.h>

#ifndef ARM7
#error "GPIO is exclusive to the ARM7!"
#endif

struct gpio_hw {
	uint8_t data;
	uint8_t dir;
	uint8_t iedge;
	uint8_t ie;
	uint16_t wifi;
};

#define REG_GPIO_HW (*(volatile struct gpio_hw*)IO_GPIO_BASE)

#endif

