
#ifndef DAWN_BAREMETALRT_ABI_USER_SETTINGS_H_
#define DAWN_BAREMETALRT_ABI_USER_SETTINGS_H_

#include <stddef.h>
#include <stdint.h>
#include <assert.h>


struct __attribute__((__packed__)) tsc_calibration {
	uint16_t tsc_cal_x1;
	uint16_t tsc_cal_y1;
	uint8_t tsc_cal_x1_px;
	uint8_t tsc_cal_y1_px;
	uint16_t tsc_cal_x2;
	uint16_t tsc_cal_y2;
	uint8_t tsc_cal_x2_px;
	uint8_t tsc_cal_y2_px;
};


struct __attribute__((__packed__)) user_settings {
	uint16_t version; /**< always 5 */
	uint8_t theme_color;
	uint8_t birth_month;
	uint8_t birth_day;
	uint8_t _reserved_1;
	uint16_t name_utf16[10];
	uint16_t name_len;
	uint16_t message_utf16[26];
	uint16_t message_len;
	uint8_t alarm_hour;
	uint8_t alarm_minute;
	uint8_t _reserved_2[4];

	struct tsc_calibration calib;

	struct {
		uint16_t language: 3;
		uint16_t gba_screen: 1;
		uint16_t default_bright: 2;
		uint16_t auto_mode: 1;
		uint16_t _reserved_5: 2;
		uint16_t settings_lost: 1;
		uint16_t _reserved_6: 6;
	} __attribute__((__packed__));

	uint8_t year; /**< epoch is 2000 */
	uint8_t _reserved_3;
	uint32_t rtc_offset;
	uint32_t _reserved_4;
};
static_assert(sizeof(struct user_settings) == 0x70);

#define ABI_USER_SETTINGS   ((volatile struct user_settings  *)0x02fffc80)

#endif

