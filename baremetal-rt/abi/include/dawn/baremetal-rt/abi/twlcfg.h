
#ifndef DAWN_BAREMETALRT_ABI_TWLCFG_H_
#define DAWN_BAREMETALRT_ABI_TWLCFG_H_

#include <stddef.h>
#include <stdint.h>
#include <assert.h>

#include <dawn/baremetal-rt/abi/titlelist.h>
#include <dawn/baremetal-rt/abi/user_settings.h>


enum twlcfg_flags {
	twlcfg_wifi_enable = 1<<3,
	twlcfg_eula = 1<<24
};

struct __attribute__((__packed__)) twlcfg_settings {
	uint32_t cfg_flags;
	uint8_t _zero_0;
	uint8_t country_code;
	uint8_t language;
	uint8_t rtc_year; /**< epoch is 2000 */
	uint32_t rtc_offset;
	uint32_t _zero_1;
	uint8_t eula_version;
	uint8_t _zero_2[9];
	uint8_t alarm_hour;
	uint8_t alarm_minute;
	uint16_t _zero_3;
	uint8_t alarm_enable;
	uint16_t _zero_8;
	uint8_t sysmenu_slots_used;
	uint8_t sysmenu_slots_free;
	uint8_t _reserved_0, _reserved_1;
	uint8_t _zero_4[3];
	uint64_t last_tid;
	struct tsc_calibration calib;
	uint32_t _reserved_2;
	uint32_t _zero_5;
	uint8_t theme_color;
	uint8_t _zero_9;
	uint8_t birth_month;
	uint8_t birth_day;
	uint16_t name_utf16[10+1];
	uint16_t message_utf16[26+1];
	uint8_t parent_ctrl_flags;
	uint8_t _zero_6[6];
	uint8_t parent_ctrl_region;
	uint8_t parent_ctrl_rating;
	uint8_t parent_ctrl_question;
	uint8_t parent_ctrl_unknown;
	uint16_t _zero_7;
	uint8_t parent_ctrl_pin[4+1];
	uint16_t parent_ctrl_answer[64+1];
};
static_assert(offsetof(struct twlcfg_settings, alarm_hour) == 0x1a);
static_assert(offsetof(struct twlcfg_settings, sysmenu_slots_free) == 0x22);
static_assert(offsetof(struct twlcfg_settings, calib) == 0x30);
static_assert(offsetof(struct twlcfg_settings, message_utf16) == 0x5e);
static_assert(offsetof(struct twlcfg_settings, message_utf16) == 0x5e);
static_assert(offsetof(struct twlcfg_settings, parent_ctrl_answer) == 0xa6);
static_assert(sizeof(struct twlcfg_settings) == 0x128);


struct __attribute__((__packed__)) hwinfo_n_settings {
	uint32_t id1;
	uint8_t id2[16];
};


enum athfirm_type {
	athfirm_dwm_w015 = 1,
	athfirm_dwm_w024 = 2,
	athfirm_dwm_w028 = 3
};

struct __attribute__((__packed__)) twlcfg_athfirm {
	uint8_t type;
	uint8_t _reserved_0;
	uint16_t crc16;
	uint32_t ram_vars;
	uint32_t ram_base;
	uint32_t ram_size;
	uint8_t _reserved_1[16];
};


#define ABI_TWLCFG_SETTINGS ((volatile struct twlcfg_settings*)0x02000400)
#define ABI_HWINFO_N_SETTINGS ((volatile struct hwinfo_n_settings*)0x02000600)

#endif

