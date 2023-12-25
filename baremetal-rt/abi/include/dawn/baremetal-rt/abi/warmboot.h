
#ifndef DAWN_BAREMETALRT_ABI_WARMBOOT_H_
#define DAWN_BAREMETALRT_ABI_WARMBOOT_H_

#include <stddef.h>
#include <stdint.h>
#include <assert.h>

#include <dawn/baremetal-rt/abi/titlelist.h>


struct __attribute__((__packed__)) warmboot_autoparam {
	struct title_id tid_old;
	uint8_t _unknown_0;
	uint8_t flags;
	uint8_t makercode_old[2];
	uint16_t _unknown_1, _unknown_2;
	uint16_t crc16;
	uint16_t _unknown_3;
	uint8_t unknown_4[0x2ec];
};
static_assert(sizeof(struct warmboot_autoparam) == 0x300);


enum autoload_flags {
	autoload_flag_valid = 1<<0,
	autoload_flag_loadcompl = 1<<6,
	autoload_boottype_cartridge = 1<<1,
	autoload_boottype_landing   = 2<<1,
	autoload_boottype_dsiware   = 3<<1,
};

struct __attribute__((__packed__)) warmboot_autoload {
	uint32_t id;
	uint8_t _unknown_0;
	uint8_t data_len;
	uint16_t data_crc16;
	struct title_id tid_old;
	struct title_id tid_new;
	uint32_t flags;
	uint32_t _unkown_1;
	uint8_t unused[0xe0];
};
static_assert(sizeof(struct warmboot_autoload) == 0x100);


enum unlaunch_autoload_flags {
	unlaunch_al_do_load    = 1<<0,
	unlaunch_al_use_colors = 1<<1,
};

struct __attribute__((__packed__)) warmboot_unlaunch {
	uint8_t magic[12];
	uint16_t crc16_len;
	uint16_t crc16;
	uint32_t flags;
	uint16_t bgmain_color;
	uint16_t bgsub_color;
	uint8_t _reserved_0[32];
	uint16_t launch_path[0x104];
	uint8_t _reserved_1[0x1c0];
};
static_assert(sizeof(struct warmboot_unlaunch) == 0x400);


#define ABI_WARMBOOT_AUTOPARAM ((struct warmboot_autoparam*)0x02000000)
#define ABI_WARMBOOT_AUTOLOAD  ((struct warmboot_autoload *)0x02000300)
#define ABI_WARMBOOT_UNLAUNCH  ((struct warmboot_unlaunch *)0x02000800)


#endif

