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
	.file	"valueParam.c"
	.text
	.align	2
	.global	_Z3funiii
	.type	_Z3funiii, %function
_Z3funiii:
	.fnstart
.LFB0:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
.LCFI0:
	add	fp, sp, #0
.LCFI1:
	sub	sp, sp, #20
.LCFI2:
	str	r0, [fp, #-8]
	str	r1, [fp, #-12]
	str	r2, [fp, #-16]
	ldr	r2, [fp, #-8]
	ldr	r3, [fp, #-12]
	add	r2, r2, r3
	ldr	r3, [fp, #-16]
	add	r3, r2, r3
	mov	r0, r3
	add	sp, fp, #0
	ldmfd	sp!, {fp}
	bx	lr
.LFE0:
	.cantunwind
	.fnend
	.size	_Z3funiii, .-_Z3funiii
	.align	2
	.global	main
	.type	main, %function
main:
	.fnstart
.LFB1:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
.LCFI3:
	add	fp, sp, #4
.LCFI4:
	sub	sp, sp, #8
.LCFI5:
	ldr	r0, [fp, #-8]
	ldr	r1, [fp, #-8]
	ldr	r2, [fp, #-8]
	bl	_Z3funiii
	mov	r3, r0
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-8]
	mov	r0, r3
	sub	sp, fp, #4
	ldmfd	sp!, {fp, lr}
	bx	lr
.LFE1:
	.cantunwind
	.fnend
	.size	main, .-main
	.ident	"GCC: (ctng-1.6.1) 4.4.3"
	.section	.note.GNU-stack,"",%progbits
