
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include <dawn/util/macro.h>
#include <dawn/baremetal-rt/abi/sysv.h>


#include "parse-args.h"


__attribute__((__noreturn__)) void _start(void);

extern void __libc_init_array(void); // newlib defines this
extern void __libc_fini_array(void); // newlib defines this

// "Declare main without a prototype. Prevents LTO type warnings.
// Technically UB but so is picking one signature and the user picking another."
//   - sdk-seven
extern int main();

__attribute__((__noreturn__)) void _start(void) {
	PARSE_STACK;

	atexit(__libc_fini_array); // this is what newlib's crt0 does, too

	__libc_init_array();

	// newlib exit() calls __cxa_finalize(NULL), then calls _exit()
	exit(main(argc, argv, envp));
}

