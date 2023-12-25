@ vim: set ft=armv5:

#ifndef DAWN_UTIL_MACRO_ASMINC_H_
#define DAWN_UTIL_MACRO_ASMINC_H_

.macro DAWN_BEGIN_FUNC name section=0 sectpriv=ax bits=progbits
	.if \section\() == 0
		.section .text.\name\(), "\sectpriv\()", %\bits\()
	.else
		.section \section\(), "\sectpriv\()", %\bits\()
	.endif
	.global \name\()
	.type \name\(), %function
\name\():
.endm

.macro DAWN_BEGIN_FUNC_FASTMEM name section=0 sectpriv=ax bits=progbits
	.if \section\() == 0
#ifdef ARM7
		.section .wram.text.\name\(), "\sectpriv\()", %\bits\()
#elif defined(ARM9)
		.section .itcm.text.\name\(), "\sectpriv\()", %\bits\()
#else
#error "???"
#endif
	.else
		.section \section\(), "\sectpriv\()", %\bits\()
	.endif
	.global \name\()
	.type \name\(), %function
\name\():
.endm

.macro DAWN_BEGIN_FUNC_NOSEC name
	.global \name\()
	.type \name\(), %function
\name\():
.endm

.macro DAWN_END_FUNC name
.size \name\(), . - \name\()
.endm

#endif

