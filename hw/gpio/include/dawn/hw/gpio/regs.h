
#ifndef DAWN_HW_GPIO_REGS_H_
#define DAWN_HW_GPIO_REGS_H_

#include <dawn/hw/iobase.h>

#ifndef ARM7
#error "GPIO is exclusive to the ARM7!"
#endif

#define REG_GPIO_DATA_ADDR  (IO_GPIO_BASE + 0)
#define REG_GPIO_DIR_ADDR   (IO_GPIO_BASE + 1)
#define REG_GPIO_IEDGE_ADDR (IO_GPIO_BASE + 2)
#define REG_GPIO_IE_ADDR    (IO_GPIO_BASE + 3)
#define REG_GPIO_WIFI_ADDR  (IO_GPIO_BASE + 4)

#define REG_GPIO_DATA  (*(volatile uint8_t*)REG_GPIO_DATA_ADDR)
#define REG_GPIO_DIR   (*(volatile uint8_t*)REG_GPIO_DIR_ADDR)
#define REG_GPIO_IEDGE (*(volatile uint8_t*)REG_GPIO_IEDGE_ADDR)
#define REG_GPIO_IE    (*(volatile uint8_t*)REG_GPIO_IE_ADDR)
#define REG_GPIO_WIFI  (*(volatile uint16_t*)REG_GPIO_WIFI_ADDR)

#define REG_GPIO_180_Lsb (0)
#define REG_GPIO_180_Msk (1<<REG_GPIO_180_Lsb)

#define REG_GPIO_181_Lsb (1)
#define REG_GPIO_181_Msk (1<<REG_GPIO_181_Lsb)

#define REG_GPIO_182_Lsb (2)
#define REG_GPIO_182_Msk (1<<REG_GPIO_182_Lsb)

/* GPIO330 testpoint on PCB */
#define REG_GPIO_330_Lsb (4)
#define REG_GPIO_330_Msk (1<<REG_GPIO_330_Lsb)

/* HP#SP: headphone insertion detection (1 if inserted) */
#define REG_GPIO_HPnSP_Lsb (5)
#define REG_GPIO_HPnSP_Msk (1<<REG_GPIO_HPnSP_Lsb)

/* /IRQ_O: powerbutton pressed for a short amount of time (from BPTWL) */
#define REG_GPIO_nIRQO_Lsb (6)
#define REG_GPIO_nIRQO_Msk (1<<REG_GPIO_nIRQO_Lsb)

/* sound enable (to TSC/CODEC) */
#define REG_GPIO_MUTE_Lsb (7)
#define REG_GPIO_MUTE_Msk (1<<REG_GPIO_MUTE_Lsb)

#define REG_GPIO_WIFI_WO_Lsb (0)
#define REG_GPIO_WIFI_WO_Msk (1<<REG_GPIO_WIFI_WO_Lsb)

/* WiFi mode (set to 0 for NWifi (Ath6k), 1 for DSWifi) */
#define REG_GPIO_WIFI_ATHSEL_Lsb (8)
#define REG_GPIO_WIFI_ATHSEL_Msk (1<<REG_GPIO_WIFI_ATHSEL_Lsb)

#endif

