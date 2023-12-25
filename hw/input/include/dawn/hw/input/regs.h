
#ifndef DAWN_HW_INPUT_REGS_H_
#define DAWN_HW_INPUT_REGS_H_

#include <dawn/hw/iobase.h>

#define REG_KEYINPUT_ADDR (IO_INPUT_BASE + 0)
#define REG_KEYCNT_ADDR   (IO_INPUT_BASE + 2)

#define REG_KEYINPUT (*(volatile uint16_t*)REG_KEYINPUT_ADDR)
#define REG_KEYCNT   (*(volatile uint16_t*)REG_KEYCNT_ADDR)

#ifdef ARM7
#define REG_EXTKEYIN_ADDR (IO_INPUT_BASE + 6)
#define REG_EXTKEYIN (*(volatile uint16_t*)REG_EXTKEYIN_ADDR)
#endif

/**
 * Pxx testpoints on the PCB correspond to KEYINPUT/KEYCNT bit 1<<xx
 * Ryy testpoints correspond to EXTKEYIN (DEBUG isn't wired on DSi?)
 */

#define REG_KEYINPUT_A_Lsb      0
#define REG_KEYINPUT_B_Lsb      1
#define REG_KEYINPUT_SELECT_Lsb 2
#define REG_KEYINPUT_START_Lsb  3
#define REG_KEYINPUT_RIGHT_Lsb  4
#define REG_KEYINPUT_LEFT_Lsb   5
#define REG_KEYINPUT_UP_Lsb     6
#define REG_KEYINPUT_DOWN_Lsb   7
#define REG_KEYINPUT_R_Lsb      8
#define REG_KEYINPUT_L_Lsb      9

#define REG_KEYCNT_IE_A_Lsb      0
#define REG_KEYCNT_IE_B_Lsb      1
#define REG_KEYCNT_IE_SELECT_Lsb 2
#define REG_KEYCNT_IE_START_Lsb  3
#define REG_KEYCNT_IE_RIGHT_Lsb  4
#define REG_KEYCNT_IE_LEFT_Lsb   5
#define REG_KEYCNT_IE_UP_Lsb     6
#define REG_KEYCNT_IE_DOWN_Lsb   7
#define REG_KEYCNT_IE_R_Lsb      8
#define REG_KEYCNT_IE_L_Lsb      9

#define REG_KEYCNT_IRQEN_Lsb     14
#define REG_KEYCNT_IRQ_LOGIC_Lsb 15

#ifdef ARM7
#define REG_EXTKEYIN_X_Lsb     0
#define REG_EXTKEYIN_Y_Lsb     1
#define REG_EXTKEYIN_DEBUG_Lsb 3
#define REG_EXTKEYIN_PEN_Lsb   6
#define REG_EXTKEYIN_HINGE_Lsb 7
#endif


#define REG_KEYINPUT_A_Msk      (1<<REG_KEYINPUT_A_Lsb)
#define REG_KEYINPUT_B_Msk      (1<<REG_KEYINPUT_B_Lsb)
#define REG_KEYINPUT_SELECT_Msk (1<<REG_KEYINPUT_SELECT_Lsb)
#define REG_KEYINPUT_START_Msk  (1<<REG_KEYINPUT_START_Lsb)
#define REG_KEYINPUT_RIGHT_Msk  (1<<REG_KEYINPUT_RIGHT_Lsb)
#define REG_KEYINPUT_LEFT_Msk   (1<<REG_KEYINPUT_LEFT_Lsb)
#define REG_KEYINPUT_UP_Msk     (1<<REG_KEYINPUT_UP_Lsb)
#define REG_KEYINPUT_DOWN_Msk   (1<<REG_KEYINPUT_DOWN_Lsb)
#define REG_KEYINPUT_R_Msk      (1<<REG_KEYINPUT_R_Lsb)
#define REG_KEYINPUT_L_Msk      (1<<REG_KEYINPUT_L_Lsb)

#define REG_KEYCNT_IE_A_Msk      (1<<REG_KEYCNT_IE_A_Lsb)
#define REG_KEYCNT_IE_B_Msk      (1<<REG_KEYCNT_IE_B_Lsb)
#define REG_KEYCNT_IE_SELECT_Msk (1<<REG_KEYCNT_IE_SELECT_Lsb)
#define REG_KEYCNT_IE_START_Msk  (1<<REG_KEYCNT_IE_START_Lsb)
#define REG_KEYCNT_IE_RIGHT_Msk  (1<<REG_KEYCNT_IE_RIGHT_Lsb)
#define REG_KEYCNT_IE_LEFT_Msk   (1<<REG_KEYCNT_IE_LEFT_Lsb)
#define REG_KEYCNT_IE_UP_Msk     (1<<REG_KEYCNT_IE_UP_Lsb)
#define REG_KEYCNT_IE_DOWN_Msk   (1<<REG_KEYCNT_IE_DOWN_Lsb)
#define REG_KEYCNT_IE_R_Msk      (1<<REG_KEYCNT_IE_R_Lsb)
#define REG_KEYCNT_IE_L_Msk      (1<<REG_KEYCNT_IE_L_Lsb)

#define REG_KEYCNT_IRQEN_Msk     (1<<REG_KEYCNT_IRQEN_Lsb)
#define REG_KEYCNT_IRQ_LOGIC_Msk (1<<REG_KEYCNT_IRQ_LOGIC_Lsb)

#ifdef ARM7
#define REG_EXTKEYIN_X_Msk     (1<<REG_EXTKEYIN_X_Lsb)
#define REG_EXTKEYIN_Y_Msk     (1<<REG_EXTKEYIN_Y_Lsb)
#define REG_EXTKEYIN_DEBUG_Msk (1<<REG_EXTKEYIN_DEBUG_Lsb)
#define REG_EXTKEYIN_PEN_Msk   (1<<REG_EXTKEYIN_PEN_Lsb)
#define REG_EXTKEYIN_HINGE_Msk (1<<REG_EXTKEYIN_HINGE_Lsb)
#endif

#endif

