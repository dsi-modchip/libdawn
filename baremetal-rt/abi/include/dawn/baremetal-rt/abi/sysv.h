
#ifndef DAWN_BAREMETALRT_ABI_SYSV_H_
#define DAWN_BAREMETALRT_ABI_SYSV_H_

#include <stddef.h>
#include <stdint.h>
#include <assert.h>


/** define argc/argv/envp/auxv stuff needed for program initialization.
 * homebrew conventions are very ad-hoc, but let's try to make it look as much
 * as SysV as possible. https://lwn.net/Articles/631631/ has a nice ascii
 * diagram of how memory *actually* should look like. we don't have sys/auxv.h
 * so we'll have to redefine a few more structs */

#define HB_ARGV_MAGIC (0x5f617267u/*"argv"*/)

struct abi_hb_argv {
	uint32_t magic;                 /* overlaps with: autoload_a9_addr */
	char* cmdline;                                 /* autoload_a7_addr */
	size_t cmdline_len;                            /* secarea_disable */
	int argc;                                      /* used_size */
	char** argv;                                   /* header_size */
	int dummy; /**< newheap base? */               /* twl_paramtbl_a9_off */
	uint32_t host_ipv4;                            /* twl_paramtbl_a7_off */
};

#define ABI_HB_ARGV ((struct abi_hb_argv*)0x02fffe70)


typedef struct {
	uint32_t a_type;
	union {
		uint32_t a_val;
	} a_un;
} Elf32_auxv_t;


enum auxv_type {
	AT_NULL = 0,
	AT_IGNORE,
	AT_EXECFD,
	AT_PHDR,
	AT_PHENT,
	AT_PHNUM,
	AT_PAGESZ, /**< system page size (4k MPU pages?) */
	AT_BASE,
	AT_FLAGS,
	AT_ENTRY, /**< entrypoint address */
	AT_NOTELF, /**< 1 if not an ELF executable */
	AT_UID,
	AT_EUID,
	AT_GID,
	AT_EGID,
	AT_PLATFORM, /* "arm\0" */
	AT_HWCAP, /* see arch/arm/include/uapi/asm/hwcap.h in Linux source tree */
	AT_CLKTCK, /* for times(2): 33 MHz? something else? */
	AT_FPUCW,
	AT_DCACHEBSIZE,
	AT_ICACHEBSIZE,
	AT_UCACHEBSIZE,
	AT_IGNOREPPC,
	AT_SECURE, /**< "Has a nonzero value if this executable should be treated securely." */
	AT_BASE_PLATFORM,
	AT_RANDOM, /**< 16 random bytes */
	AT_HWCAP2,
	AT_EXECFN = 31, /**< executable file name */
	AT_SYSINFO, /**< pointer to bootstub */
	AT_SYSINFO_EHDR,
	AT_L1I_CACHESHAPE,
	AT_L1D_CACHESHAPE,
	AT_L2_CACHESHAPE,
	AT_L3_CACHESHAPE,
	AT_L1I_CACHESIZE = 40,
	AT_L1I_CACHEGEOMETRY,
	AT_L1D_CACHESIZE,
	AT_L1D_CACHEGEOMETRY,
	AT_L2_CACHESIZE,
	AT_L2_CACHEGEOMETRY,
	AT_L3_CACHESIZE,
	AT_L3_CACHEGEOMETRY,
	AT_MINSIGSTKSZ = 51,
};


uint32_t getauxval(uint32_t type);


#define ABI_AUXV_IGNORE_MAGIC (0x4e574144u/*"DAWN"*/)

#endif

