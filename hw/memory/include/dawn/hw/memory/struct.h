
#ifndef DAWN_HW_MEMORY_STRUCT_H_
#define DAWN_HW_MEMORY_STRUCT_H_

#include <stdint.h>

#include <dawn/hw/memory/regs.h>

#ifdef ARM7

struct memory_hw {
	uint32_t _pad0;
	union {
		uint16_t exmemstat;
		uint16_t exmemcnt;
	};
	uint16_t wifiwaitcnt;
	uint8_t _pad1[0x40-8];
	uint8_t vramstat;
	uint8_t wramstat;
};

#elif defined(ARM9)

/** hot tip: DO NOT EVER ACCESS VRAMCNT REGS LIKE this: (&VRAMCNT_A)[index].
 *  WRAMCNT is in the middle there so that WILL make things mess up.
 */
struct memory_hw {
	uint32_t _pad0;
	uint16_t exmemcnt;
	uint8_t _pad1[0x40-6];
	uint8_t vramcnt_a;
	uint8_t vramcnt_b;
	uint8_t vramcnt_c;
	uint8_t vramcnt_d;
	uint8_t vramcnt_e;
	uint8_t vramcnt_f;
	uint8_t vramcnt_g;
	uint8_t wramcnt;
	uint8_t vramcnt_h;
	uint8_t vramcnt_i;
};

#endif

#define REG_MEMORY_HW (*(volatile struct memory_hw*)IO_MEMORY_BASE)

#endif

