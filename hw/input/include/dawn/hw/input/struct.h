
#ifndef DAWN_HW_INPUT_STRUCT_H_
#define DAWN_HW_INPUT_STRUCT_H_

#include <stdint.h>

#include <dawn/hw/iobase.h>


struct input_hw {
	uint16_t keyinput;
	uint16_t keycnt;
#ifdef ARM7
	uint16_t _pad;
	uint16_t extkeyin;
#endif
};


#define REG_KEY_HW (*(volatile struct input_hw*)IO_INPUT_BASE)

#endif

