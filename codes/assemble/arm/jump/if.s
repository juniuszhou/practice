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
	.file	"if.cc"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	.fnstart
.LFB0:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
.LCFI0:
	add	fp, sp, #0
.LCFI1:
	sub	sp, sp, #12
.LCFI2:
	mov	r3, #0
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-8]
	cmp	r3, #0
	ble	.L2
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
	b	.L3
.L2:
	ldr	r3, [fp, #-8]
	sub	r3, r3, #1
	str	r3, [fp, #-8]
.L3:
	ldr	r3, [fp, #-8]
	mov	r0, r3
	add	sp, fp, #0
	ldmfd	sp!, {fp}
	bx	lr
.LFE0:
	.cantunwind
	.fnend
	.size	main, .-main
	.ident	"GCC: (ctng-1.6.1) 4.4.3"
	.section	.note.GNU-stack,"",%progbits
