
#include <dawn/hw/arm.h>
#include <dawn/hw/irq.h>
#include <dawn/hw/model.h>
#include <dawn/hw/power.h>

#include <dawn/hw/rom/common7.h>


typedef void (*intrwait_fn)(bool, uint32_t, uint32_t);
typedef void (*vbintrwait_fn)(void);

/*
DSi7: BUG: The function tries to wait for IF and IF2 interrupts, but it does
accidently ignore the old IF interrupts, and works only with new IF2 ones.
*/

static bool ARM_CODE FASTMEM_FUNC(intrwait_sub)(uint32_t flags, uint32_t flags2) {
	uint32_t cf;
	bool r;
	CRITICAL_SECTION({
		cf = ROM_IRQ_CHECKFLG;
		flags &= cf;
		if (flags) ROM_IRQ_CHECKFLG = cf ^ flags;

		cf = ROM_IRQ_CHECKFLG2;
		flags2 &= cf;
		if (flags2) ROM_IRQ_CHECKFLG2 = cf ^ flags2;

		r = (flags | flags2) != 0;
	});
	return r;
}
static void ARM_CODE FASTMEM_FUNC(intrwait_twl)(bool always_wait, uint32_t flags, uint32_t flags2) {
	if (always_wait) intrwait_sub(flags, flags2);
	do power_haltcnt_wfi();
	while (!intrwait_sub(flags, flags2));
}
static void intrwait_ntr(bool always_wait, uint32_t flags, uint32_t flags2) {
	(void)flags2;
	ARM_SWI2(0x04, always_wait?1:0, flags);
}

static intrwait_fn resolve_intrwait(void) {
	if (dawn_hw_model_is_twl_mode()) return intrwait_twl;
	else return intrwait_ntr;
}

void swi_IntrWait(bool always_wait, uint32_t flags, uint32_t flags2)
	__attribute__((__ifunc__("resolve_intrwait")));


void vbintrwait_twl(void) { intrwait_twl(true, 1, 0); }
void vbintrwait_ntr(void) { ARM_SWI0(0x05); }

static vbintrwait_fn resolve_vbintrwait(void) {
	if (dawn_hw_model_is_twl_mode()) return vbintrwait_twl;
	else return vbintrwait_ntr;
}

void swi_VBlankIntrWait(void) __attribute__((__ifunc__("resolve_vbintrwait")));

