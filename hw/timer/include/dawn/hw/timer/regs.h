
#ifndef DAWN_HW_TIMER_REGS_H_
#define DAWN_HW_TIMER_REGS_H_

#include <dawn/hw/iobase.h>


#define REG_TMxCNT_L_ADDR(x) (IO_TIMER_BASE + (x)*4 + 0)
#define REG_TMxCNT_H_ADDR(x) (IO_TIMER_BASE + (x)*4 + 2)

#define REG_TM0CNT_L_ADDR REG_TMxCNT_L_ADDR(0)
#define REG_TM1CNT_L_ADDR REG_TMxCNT_L_ADDR(1)
#define REG_TM2CNT_L_ADDR REG_TMxCNT_L_ADDR(2)
#define REG_TM3CNT_L_ADDR REG_TMxCNT_L_ADDR(3)
#define REG_TM0CNT_H_ADDR REG_TMxCNT_H_ADDR(0)
#define REG_TM1CNT_H_ADDR REG_TMxCNT_H_ADDR(1)
#define REG_TM2CNT_H_ADDR REG_TMxCNT_H_ADDR(2)
#define REG_TM3CNT_H_ADDR REG_TMxCNT_H_ADDR(3)


#define REG_TMxCNT_L(x) (*(volatile uint16_t*)REG_TMxCNT_L_ADDR(x))
#define REG_TMxCNT_H(x) (*(volatile uint16_t*)REG_TMxCNT_H_ADDR(x))

#define REG_TM0CNT_L (*(volatile uint16_t*)REG_TM0CNT_L_ADDR)
#define REG_TM1CNT_L (*(volatile uint16_t*)REG_TM1CNT_L_ADDR)
#define REG_TM2CNT_L (*(volatile uint16_t*)REG_TM2CNT_L_ADDR)
#define REG_TM3CNT_L (*(volatile uint16_t*)REG_TM3CNT_L_ADDR)
#define REG_TM0CNT_H (*(volatile uint16_t*)REG_TM0CNT_H_ADDR)
#define REG_TM1CNT_H (*(volatile uint16_t*)REG_TM1CNT_H_ADDR)
#define REG_TM2CNT_H (*(volatile uint16_t*)REG_TM2CNT_H_ADDR)
#define REG_TM3CNT_H (*(volatile uint16_t*)REG_TM3CNT_H_ADDR)


#define REG_TMxCNT_CLKDIV_Lsb 0
#define REG_TMxCNT_CHAIN_Lsb  2
#define REG_TMxCNT_IE_Lsb     6
#define REG_TMxCNT_EN_Lsb     7

#define REG_TMxCNT_CLKDIV_Msk (3<<REG_TMxCNT_CLKDIV_Lsb)
#define REG_TMxCNT_CHAIN_Msk  (1<<REG_TMxCNT_CHAIN_Lsb)
#define REG_TMxCNT_IE_Msk     (1<<REG_TMxCNT_IE_Lsb)
#define REG_TMxCNT_EN_Msk     (1<<REG_TMxCNT_EN_Lsb)

#define REG_TMxCNT_CLKDIV_1    (0<<REG_TMxCNT_CLKDIV_Lsb)
#define REG_TMxCNT_CLKDIV_64   (1<<REG_TMxCNT_CLKDIV_Lsb)
#define REG_TMxCNT_CLKDIV_256  (2<<REG_TMxCNT_CLKDIV_Lsb)
#define REG_TMxCNT_CLKDIV_1024 (3<<REG_TMxCNT_CLKDIV_Lsb)

#endif

