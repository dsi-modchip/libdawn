
#include <dawn/hw/model.h>

#include <dawn/hw/rom/common7.h>


// BUG: DSi7 accidently reads from SineTable instead of PitchTable, as
// workaround for obtaining PitchTable values, one can set
// "r0=(0..2FFh)-46Ah" on DSi.

typedef uint16_t (*pitchtab_fn)(int idx);

static uint16_t pitchtab_twl(int idx) {
	return ARM_SWI1(0x1c, idx-0x46a);
}
static uint16_t pitchtab_ntr(int idx) {
	return ARM_SWI1(0x1c, idx);
}
static pitchtab_fn resolve_pitchtab(void) {
	if (dawn_hw_model_is_twl_mode()) return pitchtab_twl;
	else return pitchtab_ntr;
}

uint16_t swi_GetPitchTable(int idx) __attribute__((__ifunc__("resolve_pitchtab")));

