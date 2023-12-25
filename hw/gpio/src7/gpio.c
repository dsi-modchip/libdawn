
#include <dawn/hw/arm.h>

#include <dawn/hw/gpio.h>

void gpio_set_irq_masked(enum twl_gpio_pin_mask msk, enum twl_gpio_pin_mask val) {
	CRITICAL_SECTION({
		HW_WRITE_MASKED(REG_GPIO_HW.ie, msk, val);
	});
}

void gpio_set_irq_edge_masked(enum twl_gpio_pin_mask msk, enum twl_gpio_edge edge) {
	CRITICAL_SECTION({
		HW_WRITE_MASKED(REG_GPIO_HW.iedge, msk,
				((edge == twl_gpio_rise) ? msk : 0));
	});
}

