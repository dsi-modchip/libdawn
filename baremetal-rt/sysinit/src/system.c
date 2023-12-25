
#include <dawn/options.h>
#include <dawn/hw/arm.h>
#ifdef ARM9
#include <dawn/hw/cpu/mpu.h>
#endif
#include <dawn/hw/irq.h>
#include <dawn/hw/memory.h>
#include <dawn/hw/model.h>
#include <dawn/hw/power.h>
#include <dawn/hw/scfg.h>
#include <dawn/hw/timer.h>

#include <dawn/baremetal-rt/isr.h>
#include <dawn/baremetal-rt/vtor.h>

void __crt0_hardware_init(void);
void SystemInit(void); // defined in cmsis-core

#ifdef ARM9
extern void __crt0_mpu_init(void);
extern uint32_t __itcm_start[];
#endif

ARM_CODE void __crt0_hardware_init(void) {
#ifdef ARM9
	if (dawn_hw_model_is_twl_mode())
		scfg_set_twl_clk(LIBDAWN_DEFAULT_TWL_ARM9_CPU_SPEED);
#endif

	// CMSIS-Core support
	asm(""::"X"(SystemInit));
	SystemInit();

	// init vectors
#ifdef ARM9
	if (__itcm_start[0] == 0x6276646c /* "ldvb"; LibDawnVtorBase (cf. isr/vtor.S) */) {
		// use low exception vector -> redirect IRQ, ABT and UND
		cp15_control_set_masked(0, cp15_ctl_exn_vector_hi);
	} else
#endif
	{
		vtor_debug_set(VTOR_BIOS_DEBUG);
		irq_main_isr_set(isr_handler);
	}

#ifdef ARM9
	__crt0_mpu_init();
#endif

	// stop & reset timers (DMA and NDMA already reset by crt0)
	for (int i = 0; i < 4; ++i)
		REG_TIMER_HW[i].cnt = 0;

#ifdef ARM7
	REG_POWER_HW.powcnt2 = REG_POWCNT2_SOUND_EN_Msk; // wifi only when driver is loaded
	// TODO: stop sound channels
	// TODO: tell PMIC to enable sound (delegate this to a driver?)
#endif
#ifdef ARM9
	REG_POWER_HW.powcnt1 = REG_POWCNT1_PPUA_EN_Msk|REG_POWCNT1_PPUB_EN_Msk
	                     | REG_POWCNT1_3DRE_EN_Msk|REG_POWCNT1_3DGE_EN_Msk;
	REG_MEMORY_HW.vramcnt_i = REG_MEMORY_HW.vramcnt_h = REG_MEMORY_HW.vramcnt_g
		= REG_MEMORY_HW.vramcnt_f= REG_MEMORY_HW.vramcnt_e = 0; // disable
	REG_MEMORY_HW.vramcnt_d = REG_MEMORY_HW.vramcnt_c = REG_MEMORY_HW.vramcnt_b
		= REG_MEMORY_HW.vramcnt_a = REG_VRAMCNT_EN_Msk|REG_VRAMCNT_A_MST_LCDC;
	// TODO: display init: clear registers, set mode
#endif

	irq_enable_set(0); // drivers must enable the separate relevant flags
	cpsr_irq_enable();
	irq_main_enable_set(true);
}

// provide default (empty) implementation when not linking with cmsis-core
__attribute__((__weak__)) void SystemInit(void) { }

