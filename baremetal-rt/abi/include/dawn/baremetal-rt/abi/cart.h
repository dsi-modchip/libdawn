
#ifndef DAWN_BAREMETALRT_ABI_CART_H_
#define DAWN_BAREMETALRT_ABI_CART_H_

#include <stddef.h>
#include <stdint.h>
#include <assert.h>

#include <dawn/util/macro.h>

#include <dawn/baremetal-rt/abi/titlelist.h>

/** NDS and DSi cartridge header formats */

enum cart_unitcode {
	cart_unitcode_ntr = 0,
	cart_unitcode_ntrtwl = 2,
	cart_unitcode_twl = 3,
};
enum cart_region {
	cart_region_world = 0x00,
	cart_region_korea = 0x40,
	cart_region_china = 0x80,
};
enum cart_flags_twl {
	cart_flag_twl_jmpable   = 1<<0,
	cart_flag_twl_modcrypt  = 1<<1,
	cart_flag_twl_mc_keysel = 1<<2,
	cart_flag_twl_nodebug   = 1<<3,
};
enum cart_twl_region {
	cart_twl_region_jp = 1<<0,
	cart_twl_region_us = 1<<1,
	cart_twl_region_eu = 1<<2,
	cart_twl_region_au = 1<<3,
	cart_twl_region_cn = 1<<4,
	cart_twl_region_ko = 1<<5,
};
enum cart_twl_access_ctrl {
	cart_twl_access_commonkey = 1<< 0,
	cart_twl_access_aes_slotb = 1<< 1,
	cart_twl_access_aes_slotc = 1<< 2,
	cart_twl_access_sdcard    = 1<< 3,
	cart_twl_access_emmc      = 1<< 4,
	cart_twl_access_scfg_mc   = 1<< 5,
	cart_twl_access_shared2   = 1<< 6,
	cart_twl_access_signjpeg_l= 1<< 7,
	cart_twl_access_gcd_ntr   = 1<< 8,
	cart_twl_access_signjpeg_u= 1<< 9,
	cart_twl_access_ssl_cert_c= 1<< 9,
	cart_twl_access_photo_r   = 1<<11,
	cart_twl_access_photo_w   = 1<<12,
	cart_twl_access_sdcard_r  = 1<<13,
	cart_twl_access_sdcard_w  = 1<<14,
	cart_twl_access_auxspi_r  = 1<<15,
	cart_twl_access_auxspi_w  = 1<<16,
	cart_twl_access_dbg_ckey  = 1<<31,
};
enum cart_twl_support_flags {
	cart_twl_support_twltsc = 1<<0,
	cart_twl_support_eula   = 1<<1,
	cart_twl_support_banner = 1<<2,
	cart_twl_support_wifi   = 1<<3,
	cart_twl_support_wireless=1<<4,
	cart_twl_support_iconsha1=1<<5,
	cart_twl_support_rsasig = 1<<6,
	cart_twl_support_devmode= 1<<7,
};
enum cart_twl_filetype {
	cart_twl_filetype_gamecart = 0,
	cart_twl_filetype_dsiware  = 4,
	cart_twl_filetype_sys_fun  = 5,
	cart_twl_filetype_sys_tool = 0x15,
	cart_twl_filetype_sys_menu = 0x17
};

struct __attribute__((__packed__)) cart_load_info {
	uint32_t rom_off;
	uint32_t entrypoint; /**< in cartridge_twl.arm7i: sd/mmc device list arm7 ram addr */
	uint32_t load_addr;
	uint32_t size;
};
static_assert(sizeof(struct cart_load_info) == 16);

struct __attribute__((__packed__)) cart_off_size {
	uint32_t offset;
	uint32_t size;
};
static_assert(sizeof(struct cart_off_size) == 8);

struct __attribute__((__packed__)) mbk_info_global {
	uint32_t mbk1;
	uint32_t mbk2;
	uint32_t mbk3;
	uint32_t mbk4;
	uint32_t mbk5;
};
static_assert(sizeof(struct mbk_info_global) == 20);

struct __attribute__((__packed__)) mbk_info_local {
	uint32_t mbk6;
	uint32_t mbk7;
	uint32_t mbk8;
};
static_assert(sizeof(struct mbk_info_local) == 12);

struct __attribute__((__packed__)) cart_memory_info {
	struct mbk_info_global mbk15;
	struct mbk_info_local mbk68_a9;
	struct mbk_info_local mbk68_a7;
	uint24_t mbk9;
	uint8_t wramcnt;
};
static_assert(sizeof(struct cart_memory_info) == 0x30);

struct __attribute__((__packed__)) parental_ctrl_ratings {
	uint8_t cero;
	uint8_t esrb;
	uint8_t _reserved_0;
	uint8_t usk;
	uint8_t pegi_eu;
	uint8_t _reserved_1;
	uint8_t pegi_pt;
	uint8_t bbfc;
	uint8_t agcb;
	uint8_t grb;
	uint8_t _reserved_2[6];
};
static_assert(sizeof(struct parental_ctrl_ratings) == 16);

struct __attribute__((__packed__)) cartridge_ntr {
	char gametitle[12];
	char gamecode[4];
	char makercode[2];
	uint8_t unitcode;
	uint8_t encseed_sel;
	uint8_t capacity; // 128 KiB << capacity
	uint8_t _reserved_0[7];
	uint8_t twl_flags;
	uint8_t region;
	uint8_t romver;
	uint8_t autostart;
	struct cart_load_info arm9;
	struct cart_load_info arm7;
	struct cart_off_size fnt;
	struct cart_off_size fat;
	struct cart_off_size ovl_a9;
	struct cart_off_size ovl_a7;
	uint32_t romctrl_normal;
	uint32_t romctrl_key1;
	uint32_t icon_title_off;
	uint16_t secarea_crc16;
	uint16_t secarea_delay;
	uint32_t autoload_a9_addr;
	uint32_t autoload_a7_addr;
	uint64_t secarea_disable;
	uint32_t used_size; /**< excluding twl area */
	uint32_t header_size;
	uint32_t twl_paramtbl_a9_off;
	uint32_t twl_paramtbl_a7_off;
	uint16_t twl_romregion_ntr_end;
	uint16_t twl_romregion_twl_start;
	uint16_t nand_ro_end;
	uint16_t nand_rw_start;
	uint8_t _reserved_2[0x18];
	char ul_fastboot[0x10];
	uint8_t nintendo_logo[0x9c];
	uint16_t logo_crc16;
	uint16_t header_crc16;
	uint32_t debug_rom_off;
	uint32_t debug_size;
	uint32_t debug_load_addr;
	uint32_t _reserved_3;
};

static_assert(offsetof(struct cartridge_ntr, arm9) == 0x20);
static_assert(offsetof(struct cartridge_ntr, fnt) == 0x40);
static_assert(offsetof(struct cartridge_ntr, ovl_a9) == 0x50);
static_assert(offsetof(struct cartridge_ntr, romctrl_normal) == 0x60);
static_assert(offsetof(struct cartridge_ntr, autoload_a9_addr) == 0x70);
static_assert(offsetof(struct cartridge_ntr, used_size) == 0x80);
static_assert(offsetof(struct cartridge_ntr, twl_romregion_ntr_end) == 0x90);
static_assert(offsetof(struct cartridge_ntr, nand_rw_start) == 0x96);
static_assert(offsetof(struct cartridge_ntr, nintendo_logo) == 0xc0);
static_assert(sizeof(struct cartridge_ntr) == 0x170);

struct __attribute__((__packed__)) cartridge_twl {
	struct cartridge_ntr ntr;
	uint8_t _padding_pre[0x10];
	struct cart_memory_info meminfo;
	uint32_t region_flags;
	uint32_t access_ctrl_aes;
	uint32_t scfg_ext7;
	uint8_t _reserved_0[3];
	uint8_t support_flags;
	struct cart_load_info arm9i;
	struct cart_load_info arm7i;
	struct cart_off_size ntr_digest;
	struct cart_off_size twl_digest;
	struct cart_off_size sector_tbl;
	struct cart_off_size block_tbl;
	uint32_t sector_size;
	uint32_t sectors_per_block;
	uint32_t banner_size;
	uint8_t shared2_0_size; /**< in 32 (or 16?) KiB units */
	uint8_t shared2_1_size; /**< in 32 (or 16?) KiB units */
	uint8_t eula_version;
	uint8_t use_ratings;
	uint32_t used_size_twl; /**< including twl area */
	uint8_t shared2_2_size; /**< in 32 (or 16?) KiB units */
	uint8_t shared2_3_size; /**< in 32 (or 16?) KiB units */
	uint8_t shared2_4_size; /**< in 32 (or 16?) KiB units */
	uint8_t shared2_5_size; /**< in 32 (or 16?) KiB units */
	uint32_t paramtbl_a9i_off;
	uint32_t paramtbl_a7i_off;
	struct cart_off_size modcrypt_1;
	struct cart_off_size modcrypt_2;
	struct title_id title_id;
	uint32_t public_sav_size;
	uint32_t private_sav_size;
	uint8_t _reserved_1[176];
	struct parental_ctrl_ratings parental_ctrl_ratings;
	uint8_t sha1_hmac_a9[20];
	uint8_t sha1_hmac_a7[20];
	uint8_t sha1_hmac_main_digest[20];
	uint8_t sha1_hmac_banner[20];
	uint8_t sha1_hmac_a9i[20];
	uint8_t sha1_hmac_a7i[20];
	uint8_t sha1_hmac_reserved_0[20];
	uint8_t sha1_hmac_reserved_1[20];
	uint8_t sha1_hmac_a9_nosec[20];
	uint8_t _padding[2636+0x180];
	uint8_t sig_rsa[128];
};

static_assert(offsetof(struct cartridge_twl, region_flags) == 0x1b0);
static_assert(offsetof(struct cartridge_twl, arm9i) == 0x1c0);
static_assert(offsetof(struct cartridge_twl, sector_size) == 0x200);
static_assert(offsetof(struct cartridge_twl, modcrypt_1) == 0x220);
static_assert(offsetof(struct cartridge_twl, _reserved_1) == 0x240);
static_assert(offsetof(struct cartridge_twl, parental_ctrl_ratings) == 0x2f0);
static_assert(offsetof(struct cartridge_twl, sha1_hmac_a9_nosec) == 0x3a0);
static_assert(sizeof(struct cartridge_twl) == 0x1000);

#endif

