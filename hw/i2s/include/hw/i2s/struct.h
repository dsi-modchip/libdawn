
#ifndef DAWN_HW_I2S_REGS_H_
#define DAWN_HW_I2S_REGS_H_

#ifndef ARM7
#error "I2S is exclusive to the ARM7"
#endif

#include <stdint.h>

struct mic_hw {
	uint16_t cnt;
	uint16_t _pad;
	uint32_t data;
};

struct sndex_hw {
	uint16_t cnt;
};

#define REG_MIC_HW   (*(volatile struct mic_hw  *)IO_MIC_BASE)
#define REG_SNDEX_HW (*(volatile struct sndex_hw*)IO_SNDEX_BASE)

#endif

