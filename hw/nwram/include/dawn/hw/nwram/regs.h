
#ifndef DAWN_HW_NWRAM_REGS_H_
#define DAWN_HW_NWRAM_REGS_H_

#include <dawn/hw/iobase.h>


#define REG_MBK1_ADDR (IO_NWRAM_BASE + 0)
#define REG_MBK2_ADDR (IO_NWRAM_BASE + 4)
#define REG_MBK3_ADDR (IO_NWRAM_BASE + 8)
#define REG_MBK4_ADDR (IO_NWRAM_BASE +12)
#define REG_MBK5_ADDR (IO_NWRAM_BASE +16)
#define REG_MBK6_ADDR (IO_NWRAM_BASE +20)
#define REG_MBK7_ADDR (IO_NWRAM_BASE +24)
#define REG_MBK8_ADDR (IO_NWRAM_BASE +28)
#define REG_MBK9_ADDR (IO_NWRAM_BASE +32)

#define REG_MBK10_ADDR (IO_NWRAM_BASE + 0)
#define REG_MBK11_ADDR (IO_NWRAM_BASE + 1)
#define REG_MBK12_ADDR (IO_NWRAM_BASE + 2)
#define REG_MBK13_ADDR (IO_NWRAM_BASE + 3)

#define REG_MBK20_ADDR (IO_NWRAM_BASE + 4)
#define REG_MBK21_ADDR (IO_NWRAM_BASE + 5)
#define REG_MBK22_ADDR (IO_NWRAM_BASE + 6)
#define REG_MBK23_ADDR (IO_NWRAM_BASE + 7)

#define REG_MBK30_ADDR (IO_NWRAM_BASE + 8)
#define REG_MBK31_ADDR (IO_NWRAM_BASE + 9)
#define REG_MBK32_ADDR (IO_NWRAM_BASE +10)
#define REG_MBK33_ADDR (IO_NWRAM_BASE +11)

#define REG_MBK40_ADDR (IO_NWRAM_BASE +12)
#define REG_MBK41_ADDR (IO_NWRAM_BASE +13)
#define REG_MBK42_ADDR (IO_NWRAM_BASE +14)
#define REG_MBK43_ADDR (IO_NWRAM_BASE +15)

#define REG_MBK50_ADDR (IO_NWRAM_BASE +16)
#define REG_MBK51_ADDR (IO_NWRAM_BASE +17)
#define REG_MBK52_ADDR (IO_NWRAM_BASE +18)
#define REG_MBK53_ADDR (IO_NWRAM_BASE +19)


#define REG_MBK_ALLOC_BUS_Lsb 0
#define REG_MBK_ALLOC_OFF_Lsb 2
#define REG_MBK_ALLOC_EN_Lsb  7

#define REG_MBK_ALLOC_BUS_Msk (3<<REG_MBK_ALLOC_BUS_Lsb)
#define REG_MBK_ALLOC_OFF_Msk (7<<REG_MBK_ALLOC_OFF_Lsb)
#define REG_MBK_ALLOC_EN_Msk  (1<<REG_MBK_ALLOC_EN_Lsb)

#define REG_MBK_ALLOC_BUS_A9   (0<<REG_MBK_ALLOC_BUS_Lsb)
#define REG_MBK_ALLOC_BUS_A7   (1<<REG_MBK_ALLOC_BUS_Lsb)
#define REG_MBK_ALLOC_BUS_DSPI (2<<REG_MBK_ALLOC_BUS_Lsb)
#define REG_MBK_ALLOC_BUS_DSPD (3<<REG_MBK_ALLOC_BUS_Lsb)


#define REG_MBK_MAP_START_Lsb 3
#define REG_MBK_MAP_SIZE_Lsb 12
#define REG_MBK_MAP_END_Lsb  19

#define REG_MBK_MAP_START_Msk (0x3ff<<REG_MBK_MAP_START_Lsb)
#define REG_MBK_MAP_SIZE_Msk  (3<<REG_MBK_MAP_SIZE_Lsb)
#define REG_MBK_MAP_END_Msk   (0x3ff<<REG_MBK_MAP_END_Lsb)


#define REG_MBK_PROT_A_Lsb  0
#define REG_MBK_PROT_B_Lsb  8
#define REG_MBK_PROT_C_Lsb 16

#define REG_MBK_PROT_A_Msk (0x0f<<REG_MBK_PROT_A_Lsb)
#define REG_MBK_PROT_B_Msk (0xff<<REG_MBK_PROT_B_Lsb)
#define REG_MBK_PROT_C_Msk (0xff<<REG_MBK_PROT_C_Lsb)


#define REG_MBK1 (*(volatile uint32_t*)REG_MBK1_ADDR)
#define REG_MBK2 (*(volatile uint32_t*)REG_MBK2_ADDR)
#define REG_MBK3 (*(volatile uint32_t*)REG_MBK3_ADDR)
#define REG_MBK4 (*(volatile uint32_t*)REG_MBK4_ADDR)
#define REG_MBK5 (*(volatile uint32_t*)REG_MBK5_ADDR)
#define REG_MBK6 (*(volatile uint32_t*)REG_MBK6_ADDR)
#define REG_MBK7 (*(volatile uint32_t*)REG_MBK7_ADDR)
#define REG_MBK8 (*(volatile uint32_t*)REG_MBK8_ADDR)
#ifdef ARM7
#define REG_MBK9 (*(volatile uint32_t*)REG_MBK9_ADDR)
#elif defined(ARM9)
#define REG_MBK9 (*(const volatile uint32_t*)REG_MBK9_ADDR)
#endif

#define REG_MBK10 (*(volatile uint8_t*)REG_MBK10_ADDR)
#define REG_MBK11 (*(volatile uint8_t*)REG_MBK11_ADDR)
#define REG_MBK12 (*(volatile uint8_t*)REG_MBK12_ADDR)
#define REG_MBK13 (*(volatile uint8_t*)REG_MBK13_ADDR)

#define REG_MBK20 (*(volatile uint8_t*)REG_MBK20_ADDR)
#define REG_MBK21 (*(volatile uint8_t*)REG_MBK21_ADDR)
#define REG_MBK22 (*(volatile uint8_t*)REG_MBK22_ADDR)
#define REG_MBK23 (*(volatile uint8_t*)REG_MBK23_ADDR)

#define REG_MBK30 (*(volatile uint8_t*)REG_MBK30_ADDR)
#define REG_MBK31 (*(volatile uint8_t*)REG_MBK31_ADDR)
#define REG_MBK32 (*(volatile uint8_t*)REG_MBK32_ADDR)
#define REG_MBK33 (*(volatile uint8_t*)REG_MBK33_ADDR)

#define REG_MBK40 (*(volatile uint8_t*)REG_MBK40_ADDR)
#define REG_MBK41 (*(volatile uint8_t*)REG_MBK41_ADDR)
#define REG_MBK42 (*(volatile uint8_t*)REG_MBK42_ADDR)
#define REG_MBK43 (*(volatile uint8_t*)REG_MBK43_ADDR)

#define REG_MBK50 (*(volatile uint8_t*)REG_MBK50_ADDR)
#define REG_MBK51 (*(volatile uint8_t*)REG_MBK51_ADDR)
#define REG_MBK52 (*(volatile uint8_t*)REG_MBK52_ADDR)
#define REG_MBK53 (*(volatile uint8_t*)REG_MBK53_ADDR)

#endif

