
#ifndef DAWN_BAREMETALRT_ABI_TWL_LORAM_H_
#define DAWN_BAREMETALRT_ABI_TWL_LORAM_H_

#include <dawn/baremetal-rt/abi/twlcfg.h>
#include <dawn/baremetal-rt/abi/warmboot.h>


struct __attribute__((__packed__)) twl_loram {
	struct warmboot_autoparam autoparam;
	struct warmboot_autoload  autoload ;
	struct twlcfg_settings    twlcfg   ;
	uint8_t _reserved_0[0x5e0-0x528];
	struct twlcfg_athfirm     athfirm  ;
	struct hwinfo_n_settings  hwinfo_n ;
	uint8_t _reserved_1[0x800-0x614];
	struct warmboot_unlaunch  unlaunch ;
};
static_assert(offsetof(struct twl_loram, autoload) == 0x300);
static_assert(offsetof(struct twl_loram, twlcfg  ) == 0x400);
static_assert(offsetof(struct twl_loram, athfirm ) == 0x5e0);
static_assert(offsetof(struct twl_loram, hwinfo_n) == 0x600);
static_assert(offsetof(struct twl_loram, unlaunch) == 0x800);

#define ABI_TWL_LORAM ((volatile struct twl_loram*)0x02000000)

#endif

