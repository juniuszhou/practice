	.file	"setjmp.c"
	.text
	.type	dummy, @function
dummy:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	popl	%ebp
	.cfi_def_cfa 4, 4
	.cfi_restore 5
	ret
	.cfi_endproc
.LFE0:
	.size	dummy, .-dummy
	.section	.rodata
.LC0:
	.string	"framepointer is %x\n"
.LC1:
	.string	"framepointer are %x\n"
	.text
	.globl	getfp
	.type	getfp, @function
getfp:
.LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	$23, -20(%ebp)
	leal	-20(%ebp), %eax
	addl	$4, %eax
	movl	%eax, -16(%ebp)
	movl	$0, -12(%ebp)
	movl	-16(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	$.LC0, %eax
	movl	-16(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	printf
	movl	$.LC1, %eax
	movl	-12(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	printf
	leal	-20(%ebp), %eax
	addl	$4, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	getfp, .-getfp
	.globl	setjmp
	.type	setjmp, @function
setjmp:
.LFB2:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$92, %esp
	movl	$0, %edi
	.cfi_offset 3, -20
	.cfi_offset 6, -16
	.cfi_offset 7, -12
	movl	$0, -28(%ebp)
	movl	$0, -32(%ebp)
	movl	$0, -36(%ebp)
	movl	$0, -40(%ebp)
	movl	$0, -44(%ebp)
	movl	$0, -48(%ebp)
	movl	$0, -52(%ebp)
	movl	$0, %esi
	movl	$0, %ebx
	testl	%edi, %edi
	je	.L4
	movl	%ebx, 36(%esp)
	movl	%esi, 32(%esp)
	movl	-52(%ebp), %eax
	movl	%eax, 28(%esp)
	movl	-48(%ebp), %eax
	movl	%eax, 24(%esp)
	movl	-44(%ebp), %eax
	movl	%eax, 20(%esp)
	movl	-40(%ebp), %eax
	movl	%eax, 16(%esp)
	movl	-36(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	-32(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-28(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%edi, (%esp)
	call	dummy
.L4:
	movl	8(%ebp), %eax
	leal	4(%eax), %ebx
	call	getfp
	movl	%eax, (%ebx)
	movl	8(%ebp), %eax
	addl	$4, %eax
	movl	(%eax), %eax
	addl	$4, %eax
	movl	8(%ebp), %edx
	addl	$8, %edx
	movl	(%eax), %ecx
	movl	%ecx, (%edx)
	movl	4(%eax), %ecx
	movl	%ecx, 4(%edx)
	movl	8(%eax), %ecx
	movl	%ecx, 8(%edx)
	movl	12(%eax), %ecx
	movl	%ecx, 12(%edx)
	movl	16(%eax), %ecx
	movl	%ecx, 16(%edx)
	movl	20(%eax), %ecx
	movl	%ecx, 20(%edx)
	movl	24(%eax), %ecx
	movl	%ecx, 24(%edx)
	movl	28(%eax), %ecx
	movl	%ecx, 28(%edx)
	movl	32(%eax), %ecx
	movl	%ecx, 32(%edx)
	movl	36(%eax), %ecx
	movl	%ecx, 36(%edx)
	movl	40(%eax), %ecx
	movl	%ecx, 40(%edx)
	movl	44(%eax), %ecx
	movl	%ecx, 44(%edx)
	movl	48(%eax), %ecx
	movl	%ecx, 48(%edx)
	movl	52(%eax), %ecx
	movl	%ecx, 52(%edx)
	movl	56(%eax), %eax
	movl	%eax, 56(%edx)
	movl	$0, %eax
	addl	$92, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%edi
	.cfi_restore 7
	popl	%ebp
	.cfi_def_cfa 4, 4
	.cfi_restore 5
	ret
	.cfi_endproc
.LFE2:
	.size	setjmp, .-setjmp
	.comm	env,400,32
	.section	.rodata
.LC2:
	.string	" length is %d \n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB3:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$32, %esp
	movl	$.LC2, %eax
	movl	$4, 4(%esp)
	movl	%eax, (%esp)
	call	printf
	movl	$env, (%esp)
	call	setjmp
	movl	%eax, 28(%esp)
	movl	$1, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
