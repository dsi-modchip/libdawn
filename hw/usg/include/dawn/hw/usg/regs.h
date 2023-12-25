
#ifndef DAWN_HW_USG_REGS_H_
#define DAWN_HW_USG_REGS_H_

#include <dawn/hw/iobase.h>


/** from https://melonds.kuribo64.net/board/thread.php?pid=5772#5772 */

#define REG_REGCNT_ADDR   (IO_USG_BASE + 0x00)
#define REG_DISPCNT2_ADDR (IO_USG_BASE + 0x10)
#define REG_DISPSW_ADDR   (IO_USG_BASE + 0x20)
#define REG_CLK11M_ADDR   (IO_USG_BASE + 0x30)

#define REG_REGCNT   (*(volatile uint16_t*)REG_REGCNT_ADDR)
#define REG_DISPCNT2 (*(volatile uint16_t*)REG_DISPCNT2_ADDR)
#define REG_DISPSW   (*(volatile uint16_t*)REG_DISPSW_ADDR)
#define REG_CLK11M   (*(volatile uint16_t*)REG_CLK11M_ADDR)

#define REG_REGCNT_WE0_Lsb  0 /**< disable write to DISPCNT2 */
#define REG_REGCNT_WE1_Lsb  1 /**< disable write to DISPSW */
#define REG_REGCNT_WE2_Lsb  2 /**< disable write to CLK11M */
#define REG_REGCNT_RE0_Lsb  8 /**< disable read from DISPCNT2 */
#define REG_REGCNT_RE1_Lsb  9 /**< disable read from DISPSW */
#define REG_REGCNT_RE2_Lsb 10 /**< disable read from CLK11M */

#define REG_DISPCNT2_MOD_DUAL_SCREEN   0
#define REG_DISPCNT2_MOD_SINGLE_SCREEN 1

#define REG_DISPSW_WIN_Lsb      0
#define REG_DISPSW_A_Lsb        4
#define REG_DISPSW_M0_Lsb       8
#define REG_DISPSW_M1_Lsb       9
#define REG_DISPSW_TVOUT_Lsb   14
#define REG_DISPSW_KEYLOCK_Lsb 15

#define REG_CLK11M_CLK11_LOW    0
#define REG_CLK11M_CLK11_ACTIVE 1


#define REG_REGCNT_WE0_Msk (1<<REG_REGCNT_WE0_Lsb)
#define REG_REGCNT_WE1_Msk (1<<REG_REGCNT_WE1_Lsb)
#define REG_REGCNT_WE2_Msk (1<<REG_REGCNT_WE2_Lsb)
#define REG_REGCNT_RE0_Msk (1<<REG_REGCNT_RE0_Lsb)
#define REG_REGCNT_RE1_Msk (1<<REG_REGCNT_RE1_Lsb)
#define REG_REGCNT_RE2_Msk (1<<REG_REGCNT_RE2_Lsb)

#define REG_DISPSW_WIN_Msk     (3<<REG_DISPSW_WIN_Lsb)
#define REG_DISPSW_A_Msk       (3<<REG_DISPSW_A_Lsb)
#define REG_DISPSW_M0_Msk      (1<<REG_DISPSW_M0_Lsb)
#define REG_DISPSW_M1_Msk      (1<<REG_DISPSW_M1_Lsb)
#define REG_DISPSW_TVOUT_Msk   (1<<REG_DISPSW_TVOUT_Lsb)
#define REG_DISPSW_KEYLOCK_Msk (1<<REG_DISPSW_KEYLOCK_Lsb)


#define REG_DISPSW_WIN_MAIN_ONLY                  (0<<REG_DISPSW_WIN_Lsb)
#define REG_DISPSW_WIN_MAIN_FULL_SUB              (1<<REG_DISPSW_WIN_Lsb)
#define REG_DISPSW_WIN_MAIN_HALF_SUB_BOTTOM_LEFT  (2<<REG_DISPSW_WIN_Lsb)
#define REG_DISPSW_WIN_MAIN_HALF_SUB_BOTTOM_RIGHT (3<<REG_DISPSW_WIN_Lsb)

#define REG_DISPSW_A_FULL_7_1 (0<<REG_DISPSW_A_Lsb)
#define REG_DISPSW_A_FULL_6_2 (1<<REG_DISPSW_A_Lsb)
#define REG_DISPSW_A_FULL_5_3 (2<<REG_DISPSW_A_Lsb)
#define REG_DISPSW_A_FULL_4_4 (3<<REG_DISPSW_A_Lsb)

#define REG_DISPSW_A_HALF_3_1 (0<<REG_DISPSW_A_Lsb)
#define REG_DISPSW_A_HALF_2_2 (1<<REG_DISPSW_A_Lsb)
#define REG_DISPSW_A_HALF_1_3 (2<<REG_DISPSW_A_Lsb)
#define REG_DISPSW_A_HALF_0_4 (3<<REG_DISPSW_A_Lsb)

#define REG_DISPSW_M0_TV_SUB  (0<<REG_DISPSW_M0_Lsb)
#define REG_DISPSW_M0_TV_MAIN (1<<REG_DISPSW_M0_Lsb)

#define REG_DISPSW_M1_MAIN_BOTTOM_SUB_TOP (0<<REG_DISPSW_M1_Lsb)
#define REG_DISPSW_M1_MAIN_TOP_SUB_BOTTOM (1<<REG_DISPSW_M1_Lsb)

#define REG_DISPSW_TVOUT_DISABLED (0<<REG_DISPSW_TVOUT_Lsb)
#define REG_DISPSW_TVOUT_ENABLED  (1<<REG_DISPSW_TVOUT_Lsb)

#define REG_DISPSW_KEYLOCK_DISABLED (0<<REG_DISPSW_KEYLOCK_Lsb)
#define REG_DISPSW_KEYLOCK_ENABLED  (1<<REG_DISPSW_KEYLOCK_Lsb)

#endif

