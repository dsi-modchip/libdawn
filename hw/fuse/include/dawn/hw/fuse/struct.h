
#ifndef DAWN_HW_FUSE_STRUCT_H_
#define DAWN_HW_FUSE_STRUCT_H_

#ifndef ARM7
#error "ConsoleID is exclusive to the ARM7"
#endif

#include <stdint.h>

#include <dawn/hw/iobase.h>

struct fuse_hw {
	uint64_t consoleid;
	uint16_t fusectl;
};

#define REG_FUSE_HW (*(volatile struct fuse_hw*)IO_FUSE_BASE)

#endif

