	.file	"gParameter.cc"
	.text
.globl _Z3funiRi
	.type	_Z3funiRi, @function
_Z3funiRi:
.LFB0:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	movl	$99, -4(%rbp)
	movq	-16(%rbp), %rax
	movl	$88, (%rax)
	movl	$1, %eax
	leave
	ret
	.cfi_endproc
.LFE0:
	.size	_Z3funiRi, .-_Z3funiRi
.globl _Z4funsP3abc
	.type	_Z4funsP3abc, @function
_Z4funsP3abc:
.LFB1:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movl	$1, %eax
	leave
	ret
	.cfi_endproc
.LFE1:
	.size	_Z4funsP3abc, .-_Z4funsP3abc
.globl main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	leaq	-8(%rbp), %rdx
	movl	-4(%rbp), %eax
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	_Z3funiRi
	movl	%eax, -12(%rbp)
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_Z4funsP3abc
	movl	%eax, -12(%rbp)
	movl	$1, %eax
	leave
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.4.1-4ubuntu9) 4.4.1"
	.section	.note.GNU-stack,"",@progbits
