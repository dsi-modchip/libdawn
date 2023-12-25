
#ifndef DAWN_HW_GPIO_H_
#define DAWN_HW_GPIO_H_

#include <stdint.h>
#include <stdbool.h>

#include <dawn/hw/gpio/regs.h>
#include <dawn/hw/gpio/struct.h>

enum twl_gpio_pin {
	twl_gpio_180 = REG_GPIO_180_Lsb,
	twl_gpio_181 = REG_GPIO_181_Lsb,
	twl_gpio_182 = REG_GPIO_182_Lsb,
	twl_gpio_330 = REG_GPIO_330_Lsb,
	twl_gpio_hpnsp = REG_GPIO_HPnSP_Lsb,
	twl_gpio_nirqo = REG_GPIO_nIRQO_Lsb,
	twl_gpio_mute  = REG_GPIO_MUTE_Lsb,

	twl_gpio_wifi = REG_GPIO_WIFI_WO_Lsb,
};

enum twl_gpio_pin_mask {
	twl_gpio_180_msk = REG_GPIO_180_Msk,
	twl_gpio_181_msk = REG_GPIO_181_Msk,
	twl_gpio_182_msk = REG_GPIO_182_Msk,
	twl_gpio_330_msk = REG_GPIO_330_Msk,
	twl_gpio_hpnsp_msk = REG_GPIO_HPnSP_Msk,
	twl_gpio_nirqo_msk = REG_GPIO_nIRQO_Msk,
	twl_gpio_mute_msk  = REG_GPIO_MUTE_Msk,

	twl_gpio_wifi_msk = REG_GPIO_WIFI_WO_Msk,
};

enum twl_gpio_dir {
	twl_gpio_input  = 0,
	twl_gpio_output = 1,
};

enum twl_gpio_edge {
	twl_gpio_fall = 0,
	twl_gpio_rise = 1,
};

static inline enum twl_gpio_pin_mask gpio_get_mask(void) {
	return REG_GPIO_HW.data | (REG_GPIO_HW.wifi & REG_GPIO_WIFI_WO_Msk);
}
static inline bool gpio_get(enum twl_gpio_pin pin) {
	return gpio_get_mask() & (1 << pin);
}

static inline void gpio_put_masked(enum twl_gpio_pin_mask msk, enum twl_gpio_pin_mask val) {
	if (msk & 0xf7)
		REG_GPIO_HW.data = (REG_GPIO_HW.data & ~(uint8_t)msk) | val;
	if (msk & REG_GPIO_WIFI_WO_Msk)
		REG_GPIO_HW.wifi = (REG_GPIO_HW.wifi & ~(uint16_t)REG_GPIO_WIFI_WO_Msk) | (val & REG_GPIO_WIFI_WO_Msk);
}
static inline void gpio_put_all(enum twl_gpio_pin_mask val) {
	REG_GPIO_HW.data = val;
	REG_GPIO_HW.wifi = val & REG_GPIO_WIFI_WO_Msk;
}
static inline void gpio_put(enum twl_gpio_pin pin, bool v) {
	gpio_put_masked(1 << pin, (v?1:0) << pin);
}

static inline void gpio_set_dir_masked(enum twl_gpio_pin_mask msk, enum twl_gpio_dir dir) {
	uint8_t v = REG_GPIO_HW.dir & ~(uint8_t)msk;
	if (dir == twl_gpio_output) v |= msk;
	REG_GPIO_HW.dir = v;
}
static inline void gpio_set_dir_all_bits(uint8_t values) {
	REG_GPIO_HW.dir = values;
}
static inline void gpio_set_dir(enum twl_gpio_pin pin, enum twl_gpio_dir dir) {
	gpio_set_dir_masked(1 << pin, dir);
}
static inline uint8_t gpio_get_dir_mask(void) {
	return REG_GPIO_HW.dir;
}
static inline enum twl_gpio_dir gpio_get_dir(enum twl_gpio_pin pin) {
	return (REG_GPIO_HW.dir >> pin) & 1;
}
static inline bool gpio_is_dir_out(enum twl_gpio_pin pin) {
	return gpio_get_dir(pin) == twl_gpio_output;
}

static inline enum twl_gpio_pin_mask gpio_get_irq_mask(void) {
	return REG_GPIO_HW.ie;
}
static inline bool gpio_is_pin_ie(enum twl_gpio_pin pin) {
	return (REG_GPIO_HW.ie >> pin) & 1;
}

void gpio_set_irq_masked(enum twl_gpio_pin_mask msk, enum twl_gpio_pin_mask val);
static inline void gpio_set_irq_all(enum twl_gpio_pin_mask val) {
	REG_GPIO_HW.ie = val;
}
static inline void gpio_set_irq(enum twl_gpio_pin pin, bool enable) {
	gpio_set_irq_masked(1 << pin, (enable?1:0) << pin);
}

static inline uint8_t gpio_get_irq_edge_mask(void) {
	return REG_GPIO_HW.iedge;
}
static inline enum twl_gpio_edge gpio_get_irq_edge(enum twl_gpio_pin pin) {
	return (gpio_get_irq_edge_mask() >> pin) & 1;
}

void gpio_set_irq_edge_masked(enum twl_gpio_pin_mask msk, enum twl_gpio_edge edge);
static inline void gpio_set_irq_edge_all(uint8_t values) {
	REG_GPIO_HW.iedge = values;
}
static inline void gpio_set_irq_edge(enum twl_gpio_pin pin, enum twl_gpio_edge edge) {
	gpio_set_irq_edge_masked(1 << pin, edge);
}

#endif

