
#include <stdint.h>
#include <stdbool.h>

#include <dawn/util/macro.h>
#include <dawn/baremetal-rt/abi/sysv.h>


#include "parse-args.h"


__attribute__((__noreturn__)) extern int main(int argc, char** argv, char** envp);


__attribute__((__noreturn__)) void _start(void);
__attribute__((__noreturn__)) void _start(void) {
	PARSE_STACK;

	main(argc, argv, envp);

	__builtin_unreachable();
}

