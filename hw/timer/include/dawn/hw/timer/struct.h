
#ifndef DAWN_HW_TIMER_STRUCT_H_
#define DAWN_HW_TIMER_STRUCT_H_

#include <stdint.h>

#include <dawn/hw/iobase.h>


struct timer_hw {
	union {
		struct {
			uint16_t cnt_l; // counter/reload
			uint16_t cnt_h; // control
		};
		uint32_t cnt;
	};
};

#define REG_TIMER_HW ((volatile struct timer_hw*)IO_TIMER_BASE)

#endif

