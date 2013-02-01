	.file	"bFloat.cc"
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
	subl	$24, %esp
	flds	-12(%ebp)
	fmuls	-8(%ebp)
	fstps	-4(%ebp)
	flds	-4(%ebp)
	fnstcw	-18(%ebp)
	movzwl	-18(%ebp), %eax
	movb	$12, %ah
	movw	%ax, -20(%ebp)
	fldcw	-20(%ebp)
	fistpl	-24(%ebp)
	fldcw	-18(%ebp)
	movl	-24(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.6.1-9ubuntu3) 4.6.1"
	.section	.note.GNU-stack,"",@progbits
