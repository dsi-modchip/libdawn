
#ifndef DAWN_HW_FUSE_REGS_H_
#define DAWN_HW_FUSE_REGS_H_

#ifndef ARM7
#error "ConsoleID is exclusive to the ARM7"
#endif

#include <dawn/hw/iobase.h>

#define REG_CONSOLEID_ADDR (IO_FUSE_BASE + 0)
#define REG_FUSECTL_ADDR   (IO_FUSE_BASE + 8)

#define REG_CONSOLEID (*(volatile uint64_t*)REG_CONSOLEID_ADDR)
#define REG_FUSECTL   (*(volatile uint16_t*)REG_FUSECTL_ADDR)


#define REG_FUSECTL_CONSOLEID_ERROR_Lsb 0
#define REG_FUSECTL_CONSOLEID_ERROR_Msk (1<<REG_FUSECTL_CONSOLEID_ERROR_Lsb)

#endif

