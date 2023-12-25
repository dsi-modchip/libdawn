
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

typedef void (*init_fini_fn)(void);

// provide default implementations if libc doesn't (newlib should, at least,
// but maybe the user doesn't want to use it fsr)

/* init **********************************************************************/

extern init_fini_fn __preinit_array_start[];
extern init_fini_fn __preinit_array_end[];
extern init_fini_fn __init_array_start[];
extern init_fini_fn __init_array_end[];

void _init(void);
__attribute__((__weak__)) void _init(void) { }

extern void __libc_init_array(void) {
	size_t n = __preinit_array_end - __preinit_array_start;
	for (size_t i = 0; i < n; ++i) __preinit_array_start[i]();

	asm(""::"X"(_init)); /* prevent LTO from inlining _init - it's a weak ref! */
	_init();

	n = __init_array_end - __init_array_start;
	for (size_t i = 0; i < n; ++i) __init_array_start[i]();
}

/* fini **********************************************************************/

extern init_fini_fn __fini_array_start[];
extern init_fini_fn __fini_array_end[];

void _fini(void);
__attribute__((__weak__)) void _fini(void) { }

extern void __libc_fini_array(void) {
	size_t n = __fini_array_end - __fini_array_start;
	for (size_t i = n; i > 0; --i) __fini_array_start[i - 1]();

	asm(""::"X"(_fini)); /* prevent LTO from inlining _fini - it's a weak ref! */
	_fini();
}

/* exit **********************************************************************/

void __cxa_finalize(void* dso);

__attribute__((__weak__, __noreturn__))
void exit(int code) {
	__cxa_finalize(NULL); // calls all functions registered with atexit()
	// ^ _start() registers __libc_fini_array() with atexit()

	_exit(code);
}

__attribute__((__weak__))
void __cxa_finalize(void* dso) {
	(void)dso;

	// oops. not even this is provided. time to do it hackily, then
	asm(""::"X"(__libc_fini_array));
	__libc_fini_array();
}

// in case the above isn't provided, this one probably isn't either
__attribute__((__weak__))
int atexit(void (*fn)(void)) { (void)fn; return -1; }

