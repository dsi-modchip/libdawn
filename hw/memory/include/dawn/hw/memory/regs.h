
#ifndef DAWN_HW_MEMORY_REGS_H_
#define DAWN_HW_MEMORY_REGS_H_

/** NOTE: BIOSPROT is included in the power management I/O registers */
/** NOTE: NWRAM is included in the nwram registers. This file only concerns
 *        itself with the old NTR memories */

#include <dawn/hw/iobase.h>


#define REG_EXMEMCNT_ADDR  (IO_MEMORY_BASE + 4)
#define REG_EXMEMCNT (*(volatile uint16_t*)REG_EXMEMCNT_ADDR)

#define REG_EXMEMCNT_SLOT2_SRAM_Lsb   0
#define REG_EXMEMCNT_SLOT2_ROM1_Lsb   2
#define REG_EXMEMCNT_SLOT2_ROM2_Lsb   4
#define REG_EXMEMCNT_SLOT2_PHI_Lsb    5
#define REG_EXMEMCNT_SLOT2_ACCESS_Lsb 7
#define REG_EXMEMCNT_GCD2_ACCESS_Lsb 10
#define REG_EXMEMCNT_GCD_ACCESS_Lsb  11
#define REG_EXMEMCNT_CE2_Lsb         13
#define REG_EXMEMCNT_MODE_Lsb        14
#define REG_EXMEMCNT_PRIO_Lsb        15

#define REG_EXMEMCNT_SLOT2_SRAM_Msk   (3<<REG_EXMEMCNT_SLOT2_SRAM_Lsb)
#define REG_EXMEMCNT_SLOT2_ROM1_Msk   (3<<REG_EXMEMCNT_SLOT2_ROM1_Lsb)
#define REG_EXMEMCNT_SLOT2_ROM2_Msk   (1<<REG_EXMEMCNT_SLOT2_ROM2_Lsb)
#define REG_EXMEMCNT_SLOT2_PHI_Msk    (3<<REG_EXMEMCNT_SLOT2_PHI_Lsb)
#define REG_EXMEMCNT_SLOT2_ACCESS_Msk (1<<REG_EXMEMCNT_SLOT2_ACCESS_Lsb)
#define REG_EXMEMCNT_GCD2_ACCESS_Msk  (1<<REG_EXMEMCNT_GCD2_ACCESS_Lsb)
#define REG_EXMEMCNT_GCD_ACCESS_Msk   (1<<REG_EXMEMCNT_GCD_ACCESS_Lsb)
#define REG_EXMEMCNT_CE2_Msk          (1<<REG_EXMEMCNT_CE2_Lsb)
#define REG_EXMEMCNT_MODE_Msk         (1<<REG_EXMEMCNT_MODE_Lsb)
#define REG_EXMEMCNT_PRIO_Msk         (1<<REG_EXMEMCNT_PRIO_Lsb)

#define REG_EXMEMCNT_SLOT2_SRAM_10CYC (0<<REG_EXMEMCNT_SLOT2_SRAM_Lsb)
#define REG_EXMEMCNT_SLOT2_SRAM_8CYC  (1<<REG_EXMEMCNT_SLOT2_SRAM_Lsb)
#define REG_EXMEMCNT_SLOT2_SRAM_6CYC  (2<<REG_EXMEMCNT_SLOT2_SRAM_Lsb)
#define REG_EXMEMCNT_SLOT2_SRAM_18CYC (3<<REG_EXMEMCNT_SLOT2_SRAM_Lsb)

#define REG_EXMEMCNT_SLOT2_ROM1_10CYC (0<<REG_EXMEMCNT_SLOT2_ROM1_Lsb)
#define REG_EXMEMCNT_SLOT2_ROM1_8CYC  (1<<REG_EXMEMCNT_SLOT2_ROM1_Lsb)
#define REG_EXMEMCNT_SLOT2_ROM1_6CYC  (2<<REG_EXMEMCNT_SLOT2_ROM1_Lsb)
#define REG_EXMEMCNT_SLOT2_ROM1_18CYC (3<<REG_EXMEMCNT_SLOT2_ROM1_Lsb)

#define REG_EXMEMCNT_SLOT2_ROM2_6CYC (0<<REG_EXMEMCNT_SLOT2_ROM2_Lsb)
#define REG_EXMEMCNT_SLOT2_ROM2_4CYC (1<<REG_EXMEMCNT_SLOT2_ROM2_Lsb)

#define REG_EXMEMCNT_SLOT2_PHI_OFF    (0<<REG_EXMEMCNT_SLOT2_PHI_Lsb)
#define REG_EXMEMCNT_SLOT2_PHI_4MHZ   (1<<REG_EXMEMCNT_SLOT2_PHI_Lsb)
#define REG_EXMEMCNT_SLOT2_PHI_8MHZ   (2<<REG_EXMEMCNT_SLOT2_PHI_Lsb)
#define REG_EXMEMCNT_SLOT2_PHI_16MHZ  (3<<REG_EXMEMCNT_SLOT2_PHI_Lsb)

#define REG_EXMEMCNT_SLOT2_ACCESS_ARM9 (0<<REG_EXMEMCNT_SLOT2_ACCESS_Lsb)
#define REG_EXMEMCNT_SLOT2_ACCESS_ARM7 (1<<REG_EXMEMCNT_SLOT2_ACCESS_Lsb)
#define REG_EXMEMCNT_GCD2_ACCESS_ARM9  (0<<REG_EXMEMCNT_GCD2_ACCESS_Lsb)
#define REG_EXMEMCNT_GCD2_ACCESS_ARM7  (1<<REG_EXMEMCNT_GCD2_ACCESS_Lsb)
#define REG_EXMEMCNT_GCD_ACCESS_ARM9   (0<<REG_EXMEMCNT_GCD_ACCESS_Lsb)
#define REG_EXMEMCNT_GCD_ACCESS_ARM7   (1<<REG_EXMEMCNT_GCD_ACCESS_Lsb)
#define REG_EXMEMCNT_PRIO_ARM9         (0<<REG_EXMEMCNT_PRIO_Lsb)
#define REG_EXMEMCNT_PRIO_ARM7         (1<<REG_EXMEMCNT_PRIO_Lsb)

#define REG_EXMEMCNT_CE2_ENABLE (1<<REG_EXMEMCNT_CE2_Lsb)

#define REG_EXMEMCNT_MODE_ASYNC (0<<REG_EXMEMCNT_MODE_Lsb)
#define REG_EXMEMCNT_MODE_SYNC  (1<<REG_EXMEMCNT_MODE_Lsb)

#ifdef ARM7
#define REG_EXMEMSTAT_ADDR (REG_EXMEMCNT_ADDR)
#define REG_EXMEMSTAT (*(volatile const uint16_t*)REG_EXMEMSTAT_ADDR)
#endif

#ifdef ARM9
#define REG_WRAMCNT_ADDR  (IO_MEMORY_BASE + 0x47)
#define REG_WRAMCNT (*(volatile uint8_t*)REG_WRAMCNT_ADDR)
#elif defined(ARM7)
#define REG_WRAMSTAT_ADDR (IO_MEMORY_BASE + 0x41)
#define REG_WRAMSTAT (*(volatile const uint8_t*)REG_WRAMSTAT_ADDR)
#endif

#define REG_WRAMCNT_ALLOC_Lsb 0
#define REG_WRAMCNT_ALLOC_Msk (3<<REG_WRAMCNT_ALLOC_Lsb)

#define REG_WRAMCNT_ALLOC_A9_32_A7_0     (0<<REG_WRAMCNT_ALLOC_Lsb)
#define REG_WRAMCNT_ALLOC_A9_16_A7_16    (1<<REG_WRAMCNT_ALLOC_Lsb)
#define REG_WRAMCNT_ALLOC_A9_16_A7_16SWP (2<<REG_WRAMCNT_ALLOC_Lsb)
#define REG_WRAMCNT_ALLOC_A9_0_A7_32     (3<<REG_WRAMCNT_ALLOC_Lsb)

#define REG_WRAMCNT_ALLOC_BANK1_A9 (0<<REG_WRAMCNT_ALLOC_Lsb)
#define REG_WRAMCNT_ALLOC_BANK2_A9 (0<<REG_WRAMCNT_ALLOC_Lsb)
#define REG_WRAMCNT_ALLOC_BANK1_A7 (1<<REG_WRAMCNT_ALLOC_Lsb)
#define REG_WRAMCNT_ALLOC_BANK2_A7 (2<<REG_WRAMCNT_ALLOC_Lsb)

#ifdef ARM7
#define REG_VRAMSTAT_ADDR (IO_MEMORY_BASE + 0x40)
#define REG_VRAMSTAT (*(volatile const uint8_t*)REG_VRAMSTAT_ADDR)

#define REG_WIFIWAITCNT_ADDR (IO_MEMORY_BASE + 6)
#define REG_WIFIWAITCNT (*(volatile uint8_t*)REG_WIFIWAITCNT_ADDR)


#define REG_VRAMSTAT_C_MST_ARM7_Lsb 0
#define REG_VRAMSTAT_D_MST_ARM7_Lsb 1

#define REG_VRAMSTAT_C_MST_ARM7_Msk (1<<REG_VRAMSTAT_C_MST_ARM7_Lsb)
#define REG_VRAMSTAT_D_MST_ARM7_Msk (1<<REG_VRAMSTAT_D_MST_ARM7_Lsb)

#define REG_WIFIWAITCNT_WS0NS_Lsb 0
#define REG_WIFIWAITCNT_WS0S_Lsb  2
#define REG_WIFIWAITCNT_WS1NS_Lsb 3
#define REG_WIFIWAITCNT_WS1S_Lsb  5
#define REG_WIFIWAITCNT_MCLK_DIS_Lsb 7

#define REG_WIFIWAITCNT_WS0NS_Msk (3<<REG_WIFIWAITCNT_WS0NS_Lsb)
#define REG_WIFIWAITCNT_WS0S_Msk  (1<<REG_WIFIWAITCNT_WS0S_Lsb)
#define REG_WIFIWAITCNT_WS1NS_Msk (3<<REG_WIFIWAITCNT_WS1NS_Lsb)
#define REG_WIFIWAITCNT_WS1S_Msk  (1<<REG_WIFIWAITCNT_WS1S_Lsb)
#define REG_WIFIWAITCNT_MCLK_DIS_Msk (1<<REG_WIFIWAITCNT_MCLK_DIS_Lsb)

#define REG_WIFIWAITCNT_WSNS_10 0
#define REG_WIFIWAITCNT_WSNS_8  1
#define REG_WIFIWAITCNT_WSNS_6  2
#define REG_WIFIWAITCNT_WSNS_18 3

#define REG_WIFIWAITCNT_WS0S_6  (0<<REG_WIFIWAITCNT_WS0S_Lsb)
#define REG_WIFIWAITCNT_WS0S_4  (1<<REG_WIFIWAITCNT_WS0S_Lsb)
#define REG_WIFIWAITCNT_WS1S_10 (0<<REG_WIFIWAITCNT_WS1S_Lsb)
#define REG_WIFIWAITCNT_WS1S_4  (1<<REG_WIFIWAITCNT_WS1S_Lsb)

#elif defined(ARM9)
#define REG_VRAMCNT_A_ADDR (IO_VIDEO_BASE + 0)
#define REG_VRAMCNT_B_ADDR (IO_VIDEO_BASE + 1)
#define REG_VRAMCNT_C_ADDR (IO_VIDEO_BASE + 2)
#define REG_VRAMCNT_D_ADDR (IO_VIDEO_BASE + 3)
#define REG_VRAMCNT_E_ADDR (IO_VIDEO_BASE + 4)
#define REG_VRAMCNT_F_ADDR (IO_VIDEO_BASE + 5)
#define REG_VRAMCNT_G_ADDR (IO_VIDEO_BASE + 6)
#define REG_VRAMCNT_H_ADDR (IO_VIDEO_BASE + 8)
#define REG_VRAMCNT_I_ADDR (IO_VIDEO_BASE + 9)

#define REG_VRAMCNT_A (*(volatile uint8_t*)REG_VRAMCNT_A_ADDR)
#define REG_VRAMCNT_B (*(volatile uint8_t*)REG_VRAMCNT_B_ADDR)
#define REG_VRAMCNT_C (*(volatile uint8_t*)REG_VRAMCNT_C_ADDR)
#define REG_VRAMCNT_D (*(volatile uint8_t*)REG_VRAMCNT_D_ADDR)
#define REG_VRAMCNT_E (*(volatile uint8_t*)REG_VRAMCNT_E_ADDR)
#define REG_VRAMCNT_F (*(volatile uint8_t*)REG_VRAMCNT_F_ADDR)
#define REG_VRAMCNT_G (*(volatile uint8_t*)REG_VRAMCNT_G_ADDR)
#define REG_VRAMCNT_H (*(volatile uint8_t*)REG_VRAMCNT_H_ADDR)
#define REG_VRAMCNT_I (*(volatile uint8_t*)REG_VRAMCNT_I_ADDR)

#define REG_VRAMCNT_MST_Lsb 0
#define REG_VRAMCNT_OFF_Lsb 3
#define REG_VRAMCNT_EN_Lsb  7

#define REG_VRAMCNT_MST_Msk (7<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_OFF_Msk (3<<REG_VRAMCNT_OFF_Lsb)
#define REG_VRAMCNT_EN_Msk  (1<<REG_VRAMCNT_EN_Lsb)

#define REG_VRAMCNT_A_MST_LCDC     (0<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_A_MST_MAIN_BG  (1<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_A_MST_MAIN_OBJ (2<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_A_MST_3D_TEX   (3<<REG_VRAMCNT_MST_Lsb)

#define REG_VRAMCNT_B_MST_LCDC     (0<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_B_MST_MAIN_BG  (1<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_B_MST_MAIN_OBJ (2<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_B_MST_3D_TEX   (3<<REG_VRAMCNT_MST_Lsb)

#define REG_VRAMCNT_C_MST_LCDC     (0<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_C_MST_MAIN_BG  (1<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_C_MST_ARM7     (2<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_C_MST_3D_TEX   (3<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_C_MST_SUB_BG   (4<<REG_VRAMCNT_MST_Lsb)

#define REG_VRAMCNT_D_MST_LCDC     (0<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_D_MST_MAIN_BG  (1<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_D_MST_ARM7     (2<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_D_MST_3D_TEX   (3<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_D_MST_SUB_OBJ  (4<<REG_VRAMCNT_MST_Lsb)

#define REG_VRAMCNT_E_MST_LCDC      (0<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_E_MST_MAIN_BG   (1<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_E_MST_MAIN_OBJ  (2<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_E_MST_3D_TEXPAL (3<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_E_MST_MAIN_BGEXTPAL (4<<REG_VRAMCNT_MST_Lsb)

#define REG_VRAMCNT_F_MST_LCDC      (0<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_F_MST_MAIN_BG   (1<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_F_MST_MAIN_OBJ  (2<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_F_MST_3D_TEXPAL (3<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_F_MST_MAIN_BGEXTPAL  (4<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_F_MST_MAIN_OBJEXTPAL (5<<REG_VRAMCNT_MST_Lsb)

#define REG_VRAMCNT_G_MST_LCDC      (0<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_G_MST_MAIN_BG   (1<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_G_MST_MAIN_OBJ  (2<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_G_MST_3D_TEXPAL (3<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_G_MST_MAIN_BGEXTPAL  (4<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_G_MST_MAIN_OBJEXTPAL (5<<REG_VRAMCNT_MST_Lsb)

#define REG_VRAMCNT_H_MST_LCDC         (0<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_H_MST_SUB_BG       (1<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_H_MST_SUB_BGEXTPAL (2<<REG_VRAMCNT_MST_Lsb)

#define REG_VRAMCNT_I_MST_LCDC          (0<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_I_MST_SUB_BG        (1<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_I_MST_SUB_OBJ       (2<<REG_VRAMCNT_MST_Lsb)
#define REG_VRAMCNT_I_MST_SUB_OBJEXTPAL (3<<REG_VRAMCNT_MST_Lsb)

#endif

#endif

