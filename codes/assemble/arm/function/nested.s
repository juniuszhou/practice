	.arch armv4t
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 18, 4
	.file	"nested.c"
	.text
	.align	2
	.global	_Z4fun2v
	.type	_Z4fun2v, %function
_Z4fun2v:
	.fnstart
.LFB0:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
.LCFI0:
	add	fp, sp, #0
.LCFI1:
	add	sp, fp, #0
	ldmfd	sp!, {fp}
	bx	lr
.LFE0:
	.cantunwind
	.fnend
	.size	_Z4fun2v, .-_Z4fun2v
	.align	2
	.global	_Z3funv
	.type	_Z3funv, %function
_Z3funv:
	.fnstart
.LFB1:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
.LCFI2:
	add	fp, sp, #4
.LCFI3:
	sub	sp, sp, #8
.LCFI4:
	mov	r3, #0
	str	r3, [fp, #-8]
	bl	_Z4fun2v
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #4
	ldmfd	sp!, {fp, lr}
	bx	lr
.LFE1:
	.cantunwind
	.fnend
	.size	_Z3funv, .-_Z3funv
	.align	2
	.global	main
	.type	main, %function
main:
	.fnstart
.LFB2:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
.LCFI5:
	add	fp, sp, #4
.LCFI6:
	sub	sp, sp, #8
.LCFI7:
	mov	r3, #12
	strh	r3, [fp, #-10]	@ movhi
	bl	_Z3funv
	mov	r3, r0
	str	r3, [fp, #-8]
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #4
	ldmfd	sp!, {fp, lr}
	bx	lr
.LFE2:
	.cantunwind
	.fnend
	.size	main, .-main
	.ident	"GCC: (ctng-1.6.1) 4.4.3"
	.section	.note.GNU-stack,"",%progbits
