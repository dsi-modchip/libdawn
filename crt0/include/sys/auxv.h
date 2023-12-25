
#ifndef SYS_AUXV_H_
#define SYS_AUXV_H_

#include <dawn/baremetal-rt/abi/sysv.h>

unsigned long getauxval(unsigned long type);

#endif

