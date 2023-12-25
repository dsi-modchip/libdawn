
#include <dawn/hw/arm.h>
#include <dawn/hw/cpu/cp15.h>
#include <dawn/hw/irq.h>
#include <dawn/hw/model.h>

#include <dawn/hw/rom/common9.h>

/*
NDS9: BUG: No Discard (r0=0) doesn't work. The function always waits for at
least one IRQ to occur (no matter which, including IRQs that are not selected
in r1), even if the desired flag was already set. NB. the same bug is also
found in the GBA/NDS7 functions, but it's compensated by a second bug, ie. the
GBA/NDS7 functions are working okay because their "bug doesn't work".

Return: No return value, the selected flag(s) are automatically reset in BIOS
Interrupt Flags value in RAM upon return.

DSi9: BUG: The function tries to enter Halt state via Port 4000301h (which
would be okay on ARM7, but it's probably ignored on ARM9, which should normally
use CP15 to enter Halt state; if Port 4000301h is really ignored, then the
function will "successfully" wait for interrupts, but without actually entering
any kind of low power mode).
*/

static bool ARM_CODE FASTMEM_FUNC(intrwait_sub)(volatile uint32_t* checkflg, uint32_t flags) {
	uint32_t cf;
	CRITICAL_SECTION({
		cf = *checkflg;
		flags &= cf;
		if (flags) *checkflg = cf ^ flags;
	});
	return flags != 0;
}

// actually, just reimplement it here, because it's so bugged anyway
void ARM_CODE FASTMEM_FUNC(swi_IntrWait)(bool always_wait, uint32_t flags) {
	volatile uint32_t* checkflg = (volatile uint32_t*)((cp15_dtcm_get_base() & 0xfffff000) + VTOR_HANDLE_IRQ_OFF);

	if (always_wait) intrwait_sub(checkflg, flags);
	do cp15_wfi();
	while (!intrwait_sub(checkflg, flags));
}

