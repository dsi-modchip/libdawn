
#include <dawn/hw/arm.h>
// cf. meson.build:
// not using these as it also has to run on NTR
/*#include <dawn/hw/scfg.h>
#include <dawn/hw/gpio.h>*/

#define REG_SCFG_A9ROM (*(volatile  uint8_t*)0x04004000)
#define REG_SCFG_OP    (*(volatile  uint8_t*)0x04004024)
#define REG_GPIO_IN    (*(volatile  uint8_t*)0x04004c00)

#include <dawn/hw/model.h>


#define TEST_VAL_1 0x1337
#define TEST_VAL_2 0x4a5c /* selected to have a large hamming distance from TV1 and ~TV1 */

#define TEST_ADDR_0 ((volatile uint16_t*)0x027ffff8)
#define TEST_ADDR_1 ((volatile uint16_t*)0x023ffffa)
#define TEST_ADDR_2 ((volatile uint16_t*)0x027ffffa)
#define TEST_ADDR_3 ((volatile uint16_t*)0x02fffffa)
#define TEST_ADDR_4 ((volatile uint16_t*)0x0cfffffa)
#define TEST_ADDR_5 ((volatile uint16_t*)0x0dfffffa)


static bool test_backed(volatile uint16_t* testaddr) {
	*testaddr = TEST_VAL_1;
	*TEST_ADDR_0 = TEST_VAL_2; // circumvent open bus effects if we need to take those into account
	return *testaddr == TEST_VAL_1;
}
static bool test_mirror(volatile uint16_t* testaddr) {
	*testaddr = TEST_VAL_1;
	*TEST_ADDR_0 = TEST_VAL_2; // circumvent open bus effects if we need to take those into account
	return *testaddr == *TEST_ADDR_2;
}


extern enum dawn_hw_model_type __dawn_hw_model_type;
enum dawn_hw_model_type __dawn_hw_model_type = 0xff;

enum dawn_hw_model_type dawn_hw_model_get(void) {
#ifdef LIBDAWN_HW_MODEL_DETECT_OVERRIDE
	// used in the hax fw bootloader, because it runs before FCRAM is enabled!
	__dawn_hw_model_type = LIBdawn_HW_MODEL_DETECT_OVERRIDE;
	return __dawn_hw_model_type;
#endif
	if (__dawn_hw_model_type == 0xff) return __dawn_hw_model_type;

	/*
	 * the general gist to determine the hardware model is:
	 * * read GPIO_IN & 15: 7 if dawn (even in ntrmode), undef. if ntr   ---> not here!
	 * * read SCFG_A9ROM: 0x01 if BootROM disabled and dawn BIOS visible
	 * * write test value to, see if any of these pop up at 0x023f_fff8:
	 *     - 0x0dff_fff8
	 *     - 0x0cff_fff8
	 *     - 0x02ff_fff8
	 *     - 0x027f_fff8
	 */
	uint8_t gpio, a9rom, op;
	uint8_t ramfield = 0;

	CRITICAL_SECTION({
		a9rom = REG_SCFG_A9ROM;
		gpio = REG_GPIO_IN & 0xf;
		op = REG_SCFG_OP & 3;
#ifndef LIBDAWN_HW_MODEL_NO_RAMTEST
		if (test_mirror(TEST_ADDR_2)) ramfield |= 1<<2;
		if (test_mirror(TEST_ADDR_3)) ramfield |= 1<<3;
		if (test_mirror(TEST_ADDR_4)) ramfield |= 1<<4;
		if (test_backed(TEST_ADDR_5)) ramfield |= 1<<5;
#else
		(void)ramfield;
#endif
	});

	/*
	 * now we need to decide what the console type actually is.
	 */
	int ram_megs;
#ifndef LIBDAWN_HW_MODEL_NO_RAMTEST
	if (a9rom == 0x01) {
		if (op == 0) ram_megs = 16;
		else ram_megs = 32;
	} else ram_megs = 4;
#else
	if (ramfield & (1<<5)) ram_megs = 32;
	else if (!(ramfield & (1<<3))) ram_megs = 16;
	else if (!(ramfield & (1<<2))) ram_megs = 8;
	else ram_megs = 4;
#endif

	enum dawn_hw_model_type r = 0;
	if (ram_megs == 8 || ram_megs == 32) r |= dawn_hw_model_debug_flag;

	if (ram_megs >= 16 || a9rom == 0x01) r |= dawn_hw_model_twl;
	else if (gpio == 7) r |= dawn_hw_model_twl_ntrmode;
	else r |= dawn_hw_model_ntr;

	return (__dawn_hw_model_type = r);
}

