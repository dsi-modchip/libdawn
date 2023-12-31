
#ifndef DAWN_HW_POWER_REGS_H_
#define DAWN_HW_POWER_REGS_H_

#include <dawn/hw/iobase.h>


#define REG_POSTFLG_ADDR (IO_POWER_BASE + 0)
#define REG_POWCNT_ADDR  (IO_POWER_BASE + 4)

#define REG_POSTFLG (*(volatile uint8_t*)REG_POSTFLG_ADDR)
#define REG_POWCNT  (*(volatile uint16_t*)REG_POWCNT_ADDR)


#define REG_POSTFLG_POSTBOOT_Lsb 0
#define REG_POSTFLG_POSTBOOT_Msk (1<<REG_POSTFLG_POSTBOOT_Lsb)

#ifdef ARM7
#define REG_HALTCNT_ADDR  (IO_POWER_BASE + 1)
#define REG_POWCNT2_ADDR  (IO_POWER_BASE + 4)
#define REG_BIOSPROT_ADDR (IO_POWER_BASE + 8)

#define REG_HALTCNT  (*(volatile uint8_t *)REG_HALTCNT_ADDR)
#define REG_POWCNT2  (*(volatile uint8_t *)REG_POWCNT2_ADDR)
#define REG_BIOSPROT (*(volatile uint16_t*)REG_BIOSPROT_ADDR)


#define REG_HALTCNT_MODE_Lsb 6

#define REG_POWCNT2_SOUND_EN_Lsb 0
#define REG_POWCNT2_WIFI_EN_Lsb  1


#define REG_HALTCNT_MODE_Msk (3<<REG_HALTCNT_MODE_Lsb)

#define REG_POWCNT2_SOUND_EN_Msk (1<<REG_POWCNT2_SOUND_EN_Lsb)
#define REG_POWCNT2_WIFI_EN_Msk  (1<<REG_POWCNT2_WIFI_EN_Lsb)

#define REG_HALTCNT_MODE_RUN   (0<<REG_HALTCNT_MODE_Lsb)
#define REG_HALTCNT_MODE_AGB   (1<<REG_HALTCNT_MODE_Lsb)
#define REG_HALTCNT_MODE_HALT  (2<<REG_HALTCNT_MODE_Lsb)
#define REG_HALTCNT_MODE_SLEEP (3<<REG_HALTCNT_MODE_Lsb)

#elif defined(ARM9)
#define REG_POWCNT1_ADDR  (IO_POWER_BASE + 4)
#define REG_POWCNT1 (*(volatile uint16_t*)REG_POWCNT1_ADDR)

#define REG_POWCNT1_LCDBAD_Lsb    0
#define REG_POWCNT1_PPUA_EN_Lsb   1
#define REG_POWCNT1_3DRE_EN_Lsb   2
#define REG_POWCNT1_3DGE_EN_Lsb   3
#define REG_POWCNT1_PPUB_EN_Lsb   8
#define REG_POWCNT1_DISPSWAP_Lsb 15

#define REG_POWCNT1_LCDBAD_Msk   (1<<REG_POWCNT1_LCDBAD_Lsb)
#define REG_POWCNT1_PPUA_EN_Msk  (1<<REG_POWCNT1_PPUA_EN_Lsb)
#define REG_POWCNT1_3DRE_EN_Msk  (1<<REG_POWCNT1_3DRE_EN_Lsb)
#define REG_POWCNT1_3DGE_EN_Msk  (1<<REG_POWCNT1_3DGE_EN_Lsb)
#define REG_POWCNT1_PPUB_EN_Msk  (1<<REG_POWCNT1_PPUB_EN_Lsb)
#define REG_POWCNT1_DISPSWAP_Msk (1<<REG_POWCNT1_DISPSWAP_Lsb)

#endif

#endif

