
#ifndef DAWN_HW_IRQ_REGS_H_
#define DAWN_HW_IRQ_REGS_H_

#include <dawn/hw/iobase.h>


#define REG_IME_ADDR (IO_IRQ_BASE + 0x08)
#define REG_IE_ADDR  (IO_IRQ_BASE + 0x10)
#define REG_IF_ADDR  (IO_IRQ_BASE + 0x14)

#ifdef ARM7
#define REG_IE2_ADDR  (IO_IRQ_BASE + 0x18)
#define REG_IF2_ADDR  (IO_IRQ_BASE + 0x1c)
#endif


#define REG_IME (*(volatile uint32_t*)REG_IME_ADDR)
#define REG_IE  (*(volatile uint32_t*)REG_IE_ADDR)
#define REG_IF  (*(volatile uint32_t*)REG_IF_ADDR)

#ifdef ARM7
#define REG_IE2 (*(volatile uint32_t*)REG_IE2_ADDR)
#define REG_IF2 (*(volatile uint32_t*)REG_IF2_ADDR)
#endif


#ifdef ARM7
#define VTOR_HANDLE_IRQ_ADDR   (0x0380fffc)
#define VTOR_HANDLE_DBG_ADDR   (0x0380ffdc) /**< also the debug stack top */

#define ROM_IRQ_CHECKFLG_ADDR  (0x0380fff8)
#define ROM_IRQ_CHECKFLG2_ADDR (0x0380ffc0)
#elif defined(ARM9)
/** NTR ROM uses 0x027ffd9c for this, but 0x2fff... aliases to this anyway */
#define VTOR_HANDLE_DBG_ADDR   (0x02fffd9c) /**< also the debug stack top */

#define VTOR_HANDLE_IRQ_OFF   (0x3ffc)
#define ROM_IRQ_CHECKFLG_OFF  (0x3ff8)
#endif


#define VTOR_HANDLE_DBG (*(void**)VTOR_HANDLE_DBG_ADDR)

#ifdef ARM7
#define VTOR_HANDLE_IRQ (*(void**)VTOR_HANDLE_IRQ_ADDR)

#define ROM_IRQ_CHECKFLG  (*(uint32_t*)ROM_IRQ_CHECKFLG_ADDR)
#define ROM_IRQ_CHECKFLG2 (*(uint32_t*)ROM_IRQ_CHECKFLG2_ADDR)
#endif


#define REG_IME_GLOBEN_Lsb 0

#define REG_IE_VBLANK_Lsb        0
#define REG_IE_HBLANK_Lsb        1
#define REG_IE_VCOUNT_Lsb        2
#define REG_IE_TM0OVF_Lsb        3
#define REG_IE_TM1OVF_Lsb        4
#define REG_IE_TM2OVF_Lsb        5
#define REG_IE_TM3OVF_Lsb        6
#ifdef ARM7
#define REG_IE_RTC_Lsb           7
#endif
#define REG_IE_DMA0_Lsb          8
#define REG_IE_DMA1_Lsb          9
#define REG_IE_DMA2_Lsb         10
#define REG_IE_DMA3_Lsb         11
#define REG_IE_KEY_Lsb          12
#define REG_IE_AGBSLOT_Lsb      13
#define REG_IE_GCD_DET_Lsb      14
#define REG_IE_GCD2_DET_Lsb     15
#define REG_IE_IPC_SYNC_Lsb     16
#define REG_IE_IPC_WRFIFO_E_Lsb 17
#define REG_IE_IPC_RDFIFO_A_Lsb 18
#define REG_IE_GCD_DREQ_Lsb     19
#define REG_IE_GCD_IRQ_Lsb      20
#ifdef ARM9
#define REG_IE_GPU_GXFIFO_Lsb   21
#endif
#ifdef ARM7
#define REG_IE_HINGEOPEN_Lsb    22
#define REG_IE_SPI_Lsb          23
#define REG_IE_NTRWL_Lsb        24
#endif
#ifdef ARM9
#define REG_IE_DSP_Lsb          24
#define REG_IE_CAMERA_Lsb       25
#endif
#define REG_IE_GCD2_DREQ_Lsb    26
#define REG_IE_GCD2_IRQ_Lsb     27
#define REG_IE_NDMA0_Lsb        28
#define REG_IE_NDMA1_Lsb        29
#define REG_IE_NDMA2_Lsb        30
#define REG_IE_NDMA3_Lsb        31

#ifdef ARM7
#define REG_IE2_GPIO180_Lsb      0
#define REG_IE2_GPIO181_Lsb      1
#define REG_IE2_GPIO182_Lsb      2
#define REG_IE2_GPIO330_Lsb      4
#define REG_IE2_HPnSP_Lsb        5
#define REG_IE2_POWER_Lsb        6
#define REG_IE2_GPIO333_Lsb      7
#define REG_IE2_SDMC_CTL_Lsb     8
#define REG_IE2_SDMC_DATA1_Lsb   9
#define REG_IE2_SDIO_CTL_Lsb    10
#define REG_IE2_SDIO_DATA1_Lsb  11
#define REG_IE2_AES_Lsb         12
#define REG_IE2_I2C_Lsb         13
#define REG_IE2_MICEXT_Lsb      14
#endif


#define REG_IME_GLOBEN_Msk (1<<REG_IME_GLOBEN_Lsb)

#define REG_IE_VBLANK_Msk (1<<REG_IE_VBLANK_Lsb)
#define REG_IE_HBLANK_Msk (1<<REG_IE_HBLANK_Lsb)
#define REG_IE_VCOUNT_Msk (1<<REG_IE_VCOUNT_Lsb)
#define REG_IE_TM0OVF_Msk (1<<REG_IE_TM0OVF_Lsb)
#define REG_IE_TM1OVF_Msk (1<<REG_IE_TM1OVF_Lsb)
#define REG_IE_TM2OVF_Msk (1<<REG_IE_TM2OVF_Lsb)
#define REG_IE_TM3OVF_Msk (1<<REG_IE_TM3OVF_Lsb)
#ifdef ARM7
#define REG_IE_RTC_Msk (1<<REG_IE_RTC_Lsb)
#endif
#define REG_IE_DMA0_Msk (1<<REG_IE_DMA0_Lsb)
#define REG_IE_DMA1_Msk (1<<REG_IE_DMA1_Lsb)
#define REG_IE_DMA2_Msk (1<<REG_IE_DMA2_Lsb)
#define REG_IE_DMA3_Msk (1<<REG_IE_DMA3_Lsb)
#define REG_IE_KEY_Msk (1<<REG_IE_KEY_Lsb)
#define REG_IE_AGBSLOT_Msk (1<<REG_IE_AGBSLOT_Lsb)
#define REG_IE_GCD_DET_Msk (1<<REG_IE_GCD_DET_Lsb)
#define REG_IE_GCD2_DET_Msk (1<<REG_IE_GCD2_DET_Lsb)
#define REG_IE_IPC_SYNC_Msk (1<<REG_IE_IPC_SYNC_Lsb)
#define REG_IE_IPC_WRFIFO_E_Msk (1<<REG_IE_IPC_WRFIFO_E_Lsb)
#define REG_IE_IPC_RDFIFO_A_Msk (1<<REG_IE_IPC_RDFIFO_A_Lsb)
#define REG_IE_GCD_DREQ_Msk (1<<REG_IE_GCD_DREQ_Lsb)
#define REG_IE_GCD_IRQ_Msk (1<<REG_IE_GCD_IRQ_Lsb)
#ifdef ARM9
#define REG_IE_GPU_GXFIFO_Msk (1<<REG_IE_GPU_GXFIFO_Lsb)
#endif
#ifdef ARM7
#define REG_IE_HINGEOPEN_Msk (1<<REG_IE_HINGEOPEN_Lsb)
#define REG_IE_SPI_Msk (1<<REG_IE_SPI_Lsb)
#define REG_IE_NTRWL_Msk (1<<REG_IE_NTRWL_Lsb)
#endif
#ifdef ARM9
#define REG_IE_DSP_Msk (1<<REG_IE_DSP_Lsb)
#define REG_IE_CAMERA_Msk (1<<REG_IE_CAMERA_Lsb)
#endif
#define REG_IE_GCD2_DREQ_Msk (1<<REG_IE_GCD2_DREQ_Lsb)
#define REG_IE_GCD2_IRQ_Msk (1<<REG_IE_GCD2_IRQ_Lsb)
#define REG_IE_NDMA0_Msk (1<<REG_IE_NDMA0_Lsb)
#define REG_IE_NDMA1_Msk (1<<REG_IE_NDMA1_Lsb)
#define REG_IE_NDMA2_Msk (1<<REG_IE_NDMA2_Lsb)
#define REG_IE_NDMA3_Msk (1<<REG_IE_NDMA3_Lsb)

#ifdef ARM7
#define REG_IE2_GPIO180_Msk (1<<REG_IE2_GPIO180_Lsb)
#define REG_IE2_GPIO181_Msk (1<<REG_IE2_GPIO181_Lsb)
#define REG_IE2_GPIO182_Msk (1<<REG_IE2_GPIO182_Lsb)
#define REG_IE2_GPIO330_Msk (1<<REG_IE2_GPIO330_Lsb)
#define REG_IE2_HPnSP_Msk (1<<REG_IE2_HPnSP_Lsb)
#define REG_IE2_POWER_Msk (1<<REG_IE2_POWER_Lsb)
#define REG_IE2_GPIO333_Msk (1<<REG_IE2_GPIO333_Lsb)
#define REG_IE2_SDMC_CTL_Msk (1<<REG_IE2_SDMC_CTL_Lsb)
#define REG_IE2_SDMC_DATA1_Msk (1<<REG_IE2_SDMC_DATA1_Lsb)
#define REG_IE2_SDIO_CTL_Msk (1<<REG_IE2_SDIO_CTL_Lsb)
#define REG_IE2_SDIO_DATA1_Msk (1<<REG_IE2_SDIO_DATA1_Lsb)
#define REG_IE2_AES_Msk (1<<REG_IE2_AES_Lsb)
#define REG_IE2_I2C_Msk (1<<REG_IE2_I2C_Lsb)
#define REG_IE2_MICEXT_Msk (1<<REG_IE2_MICEXT_Lsb)
#endif


#define REG_IF_VBLANK_Lsb        0
#define REG_IF_HBLANK_Lsb        1
#define REG_IF_VCOUNT_Lsb        2
#define REG_IF_TM0OVF_Lsb        3
#define REG_IF_TM1OVF_Lsb        4
#define REG_IF_TM2OVF_Lsb        5
#define REG_IF_TM3OVF_Lsb        6
#ifdef ARM7
#define REG_IF_RTC_Lsb           7
#endif
#define REG_IF_DMA0_Lsb          8
#define REG_IF_DMA1_Lsb          9
#define REG_IF_DMA2_Lsb         10
#define REG_IF_DMA3_Lsb         11
#define REG_IF_KEY_Lsb          12
#define REG_IF_AGBSLOT_Lsb      13
#define REG_IF_GCD_DET_Lsb      14
#define REG_IF_GCD2_DET_Lsb     15
#define REG_IF_IPC_SYNC_Lsb     16
#define REG_IF_IPC_WRFIFO_E_Lsb 17
#define REG_IF_IPC_RDFIFO_A_Lsb 18
#define REG_IF_GCD_DREQ_Lsb     19
#define REG_IF_GCD_IRQ_Lsb      20
#ifdef ARM9
#define REG_IF_GPU_GXFIFO_Lsb   21
#endif
#ifdef ARM7
#define REG_IF_HINGEOPEN_Lsb    22
#define REG_IF_SPI_Lsb          23
#define REG_IF_NTRWL_Lsb          24
#endif
#ifdef ARM9
#define REG_IF_DSP_Lsb          24
#define REG_IF_CAMERA_Lsb       25
#endif
#define REG_IF_GCD2_DREQ_Lsb    26
#define REG_IF_GCD2_IRQ_Lsb     27
#define REG_IF_NDMA0_Lsb        28
#define REG_IF_NDMA1_Lsb        29
#define REG_IF_NDMA2_Lsb        30
#define REG_IF_NDMA3_Lsb        31

#ifdef ARM7
#define REG_IF2_GPIO180_Lsb      0
#define REG_IF2_GPIO181_Lsb      1
#define REG_IF2_GPIO182_Lsb      2
#define REG_IF2_GPIO330_Lsb      4
#define REG_IF2_HPnSP_Lsb        5
#define REG_IF2_POWER_Lsb        6
#define REG_IF2_GPIO333_Lsb      7
#define REG_IF2_SDMC_CTL_Lsb     8
#define REG_IF2_SDMC_DATA1_Lsb   9
#define REG_IF2_SDIO_CTL_Lsb    10
#define REG_IF2_SDIO_DATA1_Lsb  11
#define REG_IF2_AES_Lsb         12
#define REG_IF2_I2C_Lsb         13
#define REG_IF2_MICEXT_Lsb      14
#endif


#define REG_IF_VBLANK_Msk (1<<REG_IF_VBLANK_Lsb)
#define REG_IF_HBLANK_Msk (1<<REG_IF_HBLANK_Lsb)
#define REG_IF_VCOUNT_Msk (1<<REG_IF_VCOUNT_Lsb)
#define REG_IF_TM0OVF_Msk (1<<REG_IF_TM0OVF_Lsb)
#define REG_IF_TM1OVF_Msk (1<<REG_IF_TM1OVF_Lsb)
#define REG_IF_TM2OVF_Msk (1<<REG_IF_TM2OVF_Lsb)
#define REG_IF_TM3OVF_Msk (1<<REG_IF_TM3OVF_Lsb)
#ifdef ARM7
#define REG_IF_RTC_Msk (1<<REG_IF_RTC_Lsb)
#endif
#define REG_IF_DMA0_Msk (1<<REG_IF_DMA0_Lsb)
#define REG_IF_DMA1_Msk (1<<REG_IF_DMA1_Lsb)
#define REG_IF_DMA2_Msk (1<<REG_IF_DMA2_Lsb)
#define REG_IF_DMA3_Msk (1<<REG_IF_DMA3_Lsb)
#define REG_IF_KEY_Msk (1<<REG_IF_KEY_Lsb)
#define REG_IF_AGBSLOT_Msk (1<<REG_IF_AGBSLOT_Lsb)
#define REG_IF_GCD_DET_Msk (1<<REG_IF_GCD_DET_Lsb)
#define REG_IF_GCD2_DET_Msk (1<<REG_IF_GCD2_DET_Lsb)
#define REG_IF_IPC_SYNC_Msk (1<<REG_IF_IPC_SYNC_Lsb)
#define REG_IF_IPC_WRFIFO_E_Msk (1<<REG_IF_IPC_WRFIFO_E_Lsb)
#define REG_IF_IPC_RDFIFO_A_Msk (1<<REG_IF_IPC_RDFIFO_A_Lsb)
#define REG_IF_GCD_DREQ_Msk (1<<REG_IF_GCD_DREQ_Lsb)
#define REG_IF_GCD_IRQ_Msk (1<<REG_IF_GCD_IRQ_Lsb)
#ifdef ARM9
#define REG_IF_GPU_GXFIFO_Msk (1<<REG_IF_GPU_GXFIFO_Lsb)
#endif
#ifdef ARM7
#define REG_IF_HINGEOPEN_Msk (1<<REG_IF_HINGEOPEN_Lsb)
#define REG_IF_SPI_Msk (1<<REG_IF_SPI_Lsb)
#define REG_IF_NTRWL_Msk (1<<REG_IF_NTRWL_Lsb)
#endif
#ifdef ARM9
#define REG_IF_DSP_Msk (1<<REG_IF_DSP_Lsb)
#define REG_IF_CAMERA_Msk (1<<REG_IF_CAMERA_Lsb)
#endif
#define REG_IF_GCD2_DREQ_Msk (1<<REG_IF_GCD2_DREQ_Lsb)
#define REG_IF_GCD2_IRQ_Msk (1<<REG_IF_GCD2_IRQ_Lsb)
#define REG_IF_NDMA0_Msk (1<<REG_IF_NDMA0_Lsb)
#define REG_IF_NDMA1_Msk (1<<REG_IF_NDMA1_Lsb)
#define REG_IF_NDMA2_Msk (1<<REG_IF_NDMA2_Lsb)
#define REG_IF_NDMA3_Msk (1<<REG_IF_NDMA3_Lsb)

#ifdef ARM7
#define REG_IF2_GPIO180_Msk (1<<REG_IF2_GPIO180_Lsb)
#define REG_IF2_GPIO181_Msk (1<<REG_IF2_GPIO181_Lsb)
#define REG_IF2_GPIO182_Msk (1<<REG_IF2_GPIO182_Lsb)
#define REG_IF2_GPIO330_Msk (1<<REG_IF2_GPIO330_Lsb)
#define REG_IF2_HPnSP_Msk (1<<REG_IF2_HPnSP_Lsb)
#define REG_IF2_POWER_Msk (1<<REG_IF2_POWER_Lsb)
#define REG_IF2_GPIO333_Msk (1<<REG_IF2_GPIO333_Lsb)
#define REG_IF2_SDMC_CTL_Msk (1<<REG_IF2_SDMC_CTL_Lsb)
#define REG_IF2_SDMC_DATA1_Msk (1<<REG_IF2_SDMC_DATA1_Lsb)
#define REG_IF2_SDIO_CTL_Msk (1<<REG_IF2_SDIO_CTL_Lsb)
#define REG_IF2_SDIO_DATA1_Msk (1<<REG_IF2_SDIO_DATA1_Lsb)
#define REG_IF2_AES_Msk (1<<REG_IF2_AES_Lsb)
#define REG_IF2_I2C_Msk (1<<REG_IF2_I2C_Lsb)
#define REG_IF2_MICEXT_Msk (1<<REG_IF2_MICEXT_Lsb)
#endif

#endif

