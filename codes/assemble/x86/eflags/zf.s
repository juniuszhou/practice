	.file	"zf.cc"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	$-1, -16(%ebp)
	movl	$2, -12(%ebp)
	movl	-16(%ebp), %eax
	cmpl	-12(%ebp), %eax
	jne	.L2
	movl	$1, %eax
	jmp	.L3
.L2:
	movl	-16(%ebp), %eax
	cmpl	-12(%ebp), %eax
	jbe	.L4
	movl	$1, %eax
	jmp	.L3
.L4:
	movl	-8(%ebp), %eax
	cmpl	-4(%ebp), %eax
	jle	.L5
	movl	$1, %eax
	jmp	.L3
.L5:
	movl	$0, %eax
.L3:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
