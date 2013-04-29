	.file	"virFunc.cc"
	.section	.text._ZN1aC2Ev,"axG",@progbits,_ZN1aC5Ev,comdat
	.align 2
	.weak	_ZN1aC2Ev
	.type	_ZN1aC2Ev, @function
_ZN1aC2Ev:
.LFB2:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	movl	$_ZTV1a+8, (%eax)
	popl	%ebp
	.cfi_def_cfa 4, 4
	.cfi_restore 5
	ret
	.cfi_endproc
.LFE2:
	.size	_ZN1aC2Ev, .-_ZN1aC2Ev
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
	pushl	%ebx
	andl	$-16, %esp
	subl	$32, %esp
	movl	$4, (%esp)
	.cfi_offset 3, -12
	call	_Znwj
	movl	%eax, %ebx
	movl	$0, (%ebx)
	movl	%ebx, (%esp)
	call	_ZN1aC1Ev
	movl	%ebx, 24(%esp)
	movl	24(%esp), %eax
	movl	(%eax), %eax
	movl	(%eax), %edx
	movl	24(%esp), %eax
	movl	%eax, (%esp)
	call	*%edx
	movl	$9, 28(%esp)
	movl	24(%esp), %eax
	movl	(%eax), %eax
	addl	$4, %eax
	movl	(%eax), %edx
	movl	24(%esp), %eax
	movl	%eax, (%esp)
	call	*%edx
	movl	24(%esp), %eax
	movl	(%eax), %eax
	addl	$8, %eax
	movl	(%eax), %edx
	movl	24(%esp), %eax
	movl	%eax, (%esp)
	call	*%edx
	movl	24(%esp), %eax
	movl	(%eax), %eax
	addl	$12, %eax
	movl	(%eax), %edx
	movl	24(%esp), %eax
	movl	%eax, (%esp)
	call	*%edx
	movl	28(%esp), %eax
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	.cfi_restore 3
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.weak	_ZN1aC1Ev
	.set	_ZN1aC1Ev,_ZN1aC2Ev
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
