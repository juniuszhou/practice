	.file	"code.c"
	.text
.globl kk
	.type	kk, @function
kk:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$1024, %esp
	leal	-1024(%ebp), %eax
	leal	64(%ebp), %edx
.L2:
	movl	$35, (%eax)
	addl	$68, %eax
	cmpl	%edx, %eax
	jne	.L2
	movl	-276(%ebp), %eax
	addl	-480(%ebp), %eax
	leave
	ret
	.size	kk, .-kk
.globl ari
	.type	ari, @function
ari:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	leal	0(,%edx,4), %ecx
	testl	%edx, %edx
	movl	$12, %eax
	cmovne	%ecx, %eax
	popl	%ebp
	ret
	.size	ari, .-ari
.globl accum
	.bss
	.align 4
	.type	accum, @object
	.size	accum, 4
accum:
	.zero	4
	.ident	"GCC: (Ubuntu 4.4.1-4ubuntu9) 4.4.1"
	.section	.note.GNU-stack,"",@progbits
