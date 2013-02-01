	.file	"bFirst.cc"
	.text
.globl main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$1, %edi
	call	malloc
	movq	%rax, -16(%rbp)
	cmpl	$0, -4(%rbp)
	jle	.L2
	movl	$8, %edi
	call	exit
.L2:
	movl	$1, %eax
	leave
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.4.1-4ubuntu9) 4.4.1"
	.section	.note.GNU-stack,"",@progbits
