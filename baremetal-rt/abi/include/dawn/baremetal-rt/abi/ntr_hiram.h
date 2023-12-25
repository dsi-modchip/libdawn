
#ifndef DAWN_BAREMETALRT_ABI_NTR_HIRAM_H_
#define DAWN_BAREMETALRT_ABI_NTR_HIRAM_H_

#include <stddef.h>
#include <stdint.h>
#include <assert.h>

#include <dawn/util/macro.h>

#include <dawn/baremetal-rt/abi/cart.h>
#include <dawn/baremetal-rt/abi/twlcfg.h>
#include <dawn/baremetal-rt/abi/user_settings.h>


struct __attribute__((__packed__)) ntr_hiram {
	uint32_t gcd_id1;
	uint32_t gcd_id2;
	uint16_t gcd_crc16;
	uint16_t secarea_crc16;
	uint16_t gcdcrc_stat;
	uint16_t secareacrc_stat;
	uint16_t ntr7rom_crc16;
	uint16_t sec_disable;
	uint16_t sio_has_conn;
	uint8_t rtc_stat;
	uint8_t _reserved_0[0x19+6];
	uint8_t agb_makercode[2];
	uint8_t agb_gamecode[4];
	uint32_t framecounter;
	uint16_t boot_indicator; /**< 1=gcd, 2=wifi, 3=sdmmc */
	uint8_t _reserved_1[0x3c+2];
	struct user_settings user_settings;
	uint32_t _reserved_2;
	uint8_t wifi_mac[6];
	uint16_t wifi_channel_flags;
	uint32_t _zero_0;
	uint8_t nds9_abrt_stack[0x9c];
	uint32_t nds9_abrt_vector;
	uint8_t _reserved_3[0x0e8-0xa0];
	uint32_t rtc_boot_date;
	uint32_t rtc_boot_time;
	uint32_t scfg_ext7_initial;
	uint16_t scfg_arm7_initial;
	uint16_t _zero_1[2];
	uint8_t warmboot_flag;
	uint8_t _one_0;
	struct twlcfg_settings* twlcfg;
	struct cartridge_ntr header_ntr; /**< ABI_HB_ARGV lives here */
	uint8_t _reserved_4[0xf8-0x70];
	uint16_t swi9_isdbg_scratch;
	uint16_t swi7_isdbg_scratch;
	uint16_t _reserved_5;
	uint16_t psram_control;
};
static_assert(offsetof(struct ntr_hiram, rtc_stat) == 0x016);
static_assert(offsetof(struct ntr_hiram, user_settings) == 0x080);
static_assert(offsetof(struct ntr_hiram, nds9_abrt_stack) == 0x100);
static_assert(offsetof(struct ntr_hiram, rtc_boot_date) == 0x1e8);
static_assert(offsetof(struct ntr_hiram, scfg_ext7_initial) == 0x1f0);
static_assert(offsetof(struct ntr_hiram, warmboot_flag) == 0x1fa);
static_assert(offsetof(struct ntr_hiram, twlcfg) == 0x1fc);
static_assert(sizeof(struct ntr_hiram) == 0x400);

#define ABI_NTR_HIRAM ((volatile struct ntr_hiram*)0x02fffc00)

#endif

