
#ifndef DAWN_HW_POWER_H_
#define DAWN_HW_POWER_H_

#include <dawn/hw/power/regs.h>
#include <dawn/hw/power/struct.h>

#ifdef ARM7
void power_haltcnt_wfi(void);
#endif

#endif

