
#ifndef DAWN_HW_FUSE_H_
#define DAWN_HW_FUSE_H_


#ifdef ARM7
#include <dawn/hw/fuse/regs.h>
#include <dawn/hw/fuse/struct.h>
#endif


static inline uint16_t fuse_get_die_y(uint64_t fuseval) {
	return (fuseval >>  0) & ((1<<12)-1);
}
static inline uint16_t fuse_get_die_x(uint64_t fuseval) {
	return (fuseval >> 12) & ((1<<12)-1);
}
static inline uint8_t fuse_get_wafer(uint64_t fuseval) {
	return (fuseval >> 24) & ((1<< 8)-1);
}
static inline uint32_t fuse_get_lot(uint64_t fuseval) {
	return (fuseval >> 32) & ((1<<20)-1);
}
static inline uint32_t fuse_get_fab(uint64_t fuseval) {
	return (fuseval >> 52) & ((1<< 9)-1);
}

static inline uint16_t consoleid_get_die_y(void) {
	return fuse_get_die_y(REG_FUSE_HW.consoleid);
}
static inline uint16_t consoleid_get_die_x(void) {
	return fuse_get_die_x(REG_FUSE_HW.consoleid);
}
static inline uint8_t consoleid_get_wafer(void) {
	return fuse_get_wafer(REG_FUSE_HW.consoleid);
}
static inline uint32_t consoleid_get_lot(void) {
	return fuse_get_lot(REG_FUSE_HW.consoleid);
}
static inline uint32_t consoleid_get_fab(void) {
	return fuse_get_fab(REG_FUSE_HW.consoleid);
}

#endif

