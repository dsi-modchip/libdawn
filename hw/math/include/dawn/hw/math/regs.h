
#ifndef DAWN_HW_MATH_REGS_H_
#define DAWN_HW_MATH_REGS_H_

#ifndef ARM9
#error "Math accelerator is exclusive to the ARM9!"
#endif

#include <dawn/hw/iobase.h>

#define REG_DIVCNT_ADDR         (IO_MATH_BASE + 0x00)
#define REG_NUMER_ADDR          (IO_MATH_BASE + 0x10)
#define REG_DENOM_ADDR          (IO_MATH_BASE + 0x18)
#define REG_DIV_RESUlT_ADDR     (IO_MATH_BASE + 0x20)
#define REG_DIVREM_RESUlT_ADDR  (IO_MATH_BASE + 0x28)

#define REG_SQRTCNT_ADDR     (IO_MATH_BASE + 0x30)
#define REG_SQRT_RESULT_ADDR (IO_MATH_BASE + 0x34)
#define REG_SQRT_PARAM_ADDR  (IO_MATH_BASE + 0x38)


#define REG_DIVCNT        (*(volatile uint32_t*)REG_DIVCNT_ADDR)
#define REG_NUMER         (*(volatile  int64_t*)REG_NUMER_ADDR)
#define REG_DENOM         (*(volatile  int64_t*)REG_DENOM_ADDR)
#define REG_DIV_RESUlT    (*(volatile  int64_t*)REG_DIV_RESUlT_ADDR)
#define REG_DIVREM_RESUlT (*(volatile  int64_t*)REG_DIVREM_RESUlT_ADDR)

#define REG_SQRTCNT     (*(volatile uint32_t*)REG_SQRTCNT_ADDR)
#define REG_SQRT_RESULT (*(volatile uint32_t*)REG_SQRT_RESULT_ADDR)
#define REG_SQRT_PARAM  (*(volatile uint64_t*)REG_SQRT_PARAM_ADDR)


#define REG_DIVCNT_MODE_32d32 0
#define REG_DIVCNT_MODE_64d32 1
#define REG_DIVCNT_MODE_64d64 2

#define REG_SQRTCNT_MODE_32 0
#define REG_SQRTCNT_MODE_64 1


#define REG_DIVCNT_MODE_Lsb     0
#define REG_DIVCNT_DBZERR_Lsb  14
#define REG_DIVCNT_BUSY_Lsb    15

#define REG_SQRTCNT_MODE_Lsb    0
#define REG_SQRTCNT_BUSY_Lsb   15


#define REG_DIVCNT_MODE_Msk   (2<<REG_DIVCNT_MODE_Lsb)
#define REG_DIVCNT_DBZERR_Msk (1<<REG_DIVCNT_DBZERR_Lsb)
#define REG_DIVCNT_BUSY_Msk   (1<<REG_DIVCNT_BUSY_Lsb)

#define REG_SQRTCNT_MODE_Msk (1<<REG_SQRTCNT_MODE_Lsb)
#define REG_SQRTCNT_BUSY_Msk (1<<REG_SQRTCNT_BUSY_Lsb)

#endif

