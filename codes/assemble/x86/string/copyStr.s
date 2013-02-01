	.file	"copyStr.cc"
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
	subl	$48, %esp
	movl	$0, -4(%ebp)
	jmp	.L2
.L3:
	leal	-24(%ebp), %eax
	addl	-4(%ebp), %eax
	movzbl	(%eax), %edx
	leal	-44(%ebp), %eax
	addl	-4(%ebp), %eax
	movb	%dl, (%eax)
	addl	$1, -4(%ebp)
.L2:
	cmpl	$19, -4(%ebp)
	setle	%al
	testb	%al, %al
	jne	.L3
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
