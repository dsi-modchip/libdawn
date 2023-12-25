
#ifndef DAWN_HW_DSP_STRUCT_H_
#define DAWN_HW_DSP_STRUCT_H_

#ifndef ARM9
#error "The DSP is exclusive to the ARM9"
#endif

#include <stdint.h>

#include <dawn/hw/iobase.h>

struct dsp_hw {
	uint16_t pdata;
	uint16_t _pad0;
	uint16_t padr;
	uint16_t _pad1;
	uint16_t pcfg;
	uint16_t _pad2;
	uint16_t psts;
	uint16_t _pad3;
	uint16_t psem;
	uint16_t _pad4;
	uint16_t pmask;
	uint16_t _pad5;
	uint16_t pclear;
	uint16_t _pad6;
	uint16_t sem;
	uint16_t _pad7;
	uint16_t cmd0;
	uint16_t _pad8;
	uint16_t rep0;
	uint16_t _pad9;
	uint16_t cmd1;
	uint16_t _pada;
	uint16_t rep1;
	uint16_t _padb;
	uint16_t cmd2;
	uint16_t _padc;
	uint16_t rep2;
	uint16_t _padd;
};

#define REG_DSP_HW (*(volatile struct dsp_hw*)IO_DSP_BASE)

#endif

