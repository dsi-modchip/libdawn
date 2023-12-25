
#include <dawn/hw/arm.h>

#include <dawn/hw/scfg.h>
#include <dawn/hw/scfg/regs.h>

uint32_t scfg_check_ext_features(uint32_t need, bool enable) {
	uint32_t ext;

	CRITICAL_SECTION({
		ext = REG_SCFG_EXT;

		if (!enable) return ~ext & need;

		REG_SCFG_EXT = ext | need;

		ext = (~(uint32_t)REG_SCFG_EXT) & need;
	});

	return ext;
}

