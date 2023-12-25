
#ifndef DAWN_HW_SCFG_H_
#define DAWN_HW_SCFG_H_

#include <stdint.h>
#include <stdbool.h>

#include <dawn/hw/scfg/regs.h>
#include <dawn/hw/scfg/struct.h>

/**
 * Checks if certain SCFG_EXT features are enabled, and optionally enables it
 * if possible.
 *
 * @param need a bitmap of SCFG_EXT flags that need to be checked for
 *
 * @param enable whether to attempt enabling the requested flags if not enabled
 *               yet.
 *
 * @return the flags that are or could NOT be set in SCFG_EXT. This may be due
 *         to either SCFG_EXT.bit31 being zero, or certain flags needing to be
 *         set by a specific CPU.
 */
uint32_t scfg_check_ext_features(uint32_t need, bool enable);

#ifdef ARM9
void scfg_set_twl_clk(bool mhz133);
#endif

#endif

