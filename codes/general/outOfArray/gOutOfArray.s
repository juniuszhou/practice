	.file	"gOutOfArray.c"
	.section	.rodata
.LC0:
	.string	"%c %d\n"
	.text
.globl main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, -52(%rbp)
	jmp	.L2
.L3:
	movl	-52(%rbp), %eax
	cltq
	movzbl	-44(%rbp,%rax), %eax
	movsbl	%al,%ecx
	movl	$.LC0, %eax
	movl	-52(%rbp), %edx
	movl	%ecx, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	addl	$1, -52(%rbp)
.L2:
	cmpl	$8114, -52(%rbp)
	jle	.L3
	movl	$1, %eax
	movq	-8(%rbp), %rdx
	xorq	%fs:40, %rdx
	je	.L5
	call	__stack_chk_fail
.L5:
	leave
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.4.1-4ubuntu9) 4.4.1"
	.section	.note.GNU-stack,"",@progbits
