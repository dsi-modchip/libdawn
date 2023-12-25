
#ifndef DAWN_HW_AES_STRUCT_H_
#define DAWN_HW_AES_STRUCT_H_

#include <stdint.h>

#include <dawn/hw/iobase.h>

#if ARM7

struct aes_keyslot_hw {
	uint8_t normal_key[16];
	uint8_t key_x[16];
	uint8_t key_y[16];
};

struct aes_hw {
	uint32_t cnt;
	union {
		uint32_t blkcnt;
		struct {
			uint16_t adcnt;
			uint16_t ptcnt;
		} blk;
	};
	uint32_t wrfifo;
	uint32_t rdfifo;
	uint8_t _pad[16];
	uint8_t iv[16];
	uint8_t mac[16];
	struct aes_keyslot_hw key[4];
};

#define REG_AES_HW (*(volatile struct aes_hw*)IO_AES_BASE)

#endif

#endif

