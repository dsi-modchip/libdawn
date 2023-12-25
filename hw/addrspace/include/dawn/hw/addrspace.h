
#ifndef DAWN_HW_ADDRSPACE_H_
#define DAWN_HW_ADDRSPACE_H_

/* NOTE: this file needs to be includable from assembly sources */

#ifdef ARM9
#define ITCM_BASE     (0x00000000)
#define MRAM_BASE     (0x02000000)
#define WRAM_BASE     (0x03000000)
#define IO_BASE       (0x04000000)
#define PALETTE_BASE  (0x05000000)
#define VRAM_BASE     (0x06000000)
#define OAM_BASE      (0x07000000)
#define SLOT2ROM_BASE (0x08000000)
#define SLOT2RAM_BASE (0x0a000000)
#define ROM_BASE      (0xffff0000)
#endif

#ifdef ARM7
#define ROM_BASE      (0x00000000)
#define MRAM_BASE     (0x02000000)
#define WRAM_BASE     (0x03000000)
#define IO_BASE       (0x04000000)
#define VRAM_BASE     (0x06000000)
#define SLOT2ROM_BASE (0x08000000)
#define SLOT2RAM_BASE (0x0a000000)
#endif

#endif

