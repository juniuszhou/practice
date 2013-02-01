	.file	"bCalling.cc"
	.text
	.align 2
	.def	__ZSt17__verify_groupingPKcjRKSs;	.scl	3;	.type	32;	.endef
__ZSt17__verify_groupingPKcjRKSs:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNKSs4sizeEv
	decl	%eax
	movl	%eax, -4(%ebp)
	movl	12(%ebp), %eax
	decl	%eax
	movl	%eax, -12(%ebp)
	leal	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-4(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZSt3minIjERKT_S2_S2_
	movl	(%eax), %eax
	movl	%eax, -8(%ebp)
	movl	-4(%ebp), %eax
	movl	%eax, -16(%ebp)
	movb	$1, -17(%ebp)
	movl	$0, -24(%ebp)
L2:
	movl	-24(%ebp), %eax
	cmpl	-8(%ebp), %eax
	jae	L5
	cmpb	$0, -17(%ebp)
	je	L5
	movl	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNKSsixEj
	movl	%eax, %ecx
	movl	-24(%ebp), %eax
	movl	8(%ebp), %edx
	addl	%eax, %edx
	movzbl	(%ecx), %eax
	cmpb	(%edx), %al
	sete	%al
	movb	%al, -17(%ebp)
	leal	-16(%ebp), %eax
	decl	(%eax)
	leal	-24(%ebp), %eax
	incl	(%eax)
	jmp	L2
L5:
	cmpl	$0, -16(%ebp)
	je	L6
	cmpb	$0, -17(%ebp)
	je	L6
	movl	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNKSsixEj
	movl	%eax, %ecx
	movl	-8(%ebp), %eax
	movl	8(%ebp), %edx
	addl	%eax, %edx
	movzbl	(%ecx), %eax
	cmpb	(%edx), %al
	sete	%al
	movb	%al, -17(%ebp)
	leal	-16(%ebp), %eax
	decl	(%eax)
	jmp	L5
L6:
	movl	$0, 4(%esp)
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNKSsixEj
	movl	%eax, %ecx
	movl	-8(%ebp), %eax
	movl	8(%ebp), %edx
	addl	%eax, %edx
	movzbl	(%ecx), %eax
	cmpb	(%edx), %al
	jg	L8
	movzbl	-17(%ebp), %eax
	andl	$1, %eax
	movb	%al, -25(%ebp)
	jmp	L9
L8:
	movb	$0, -25(%ebp)
L9:
	movzbl	-25(%ebp), %eax
	movb	%al, -17(%ebp)
	movzbl	-17(%ebp), %eax
	leave
	ret
.lcomm __ZSt8__ioinit,16
	.def	___main;	.scl	2;	.type	32;	.endef
	.align 2
.globl _main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	andl	$-16, %esp
	movl	$0, %eax
	addl	$15, %eax
	addl	$15, %eax
	shrl	$4, %eax
	sall	$4, %eax
	movl	%eax, -20(%ebp)
	movl	-20(%ebp), %eax
	call	__alloca
	call	___main
	movl	$10, -4(%ebp)
	movl	-4(%ebp), %edx
/APP
	movl %edx, %eax; 	  	movl %esp, %edx; 	  	movl %edx, %ebp
/NO_APP
	movl	%edx, -16(%ebp)
	movl	%ecx, -12(%ebp)
	movl	$__ZSt3hexRSt8ios_base, 4(%esp)
	movl	$__ZSt4cout, (%esp)
	call	__ZNSolsEPFRSt8ios_baseS0_E
	movl	%eax, %ecx
	movl	-16(%ebp), %eax
	movl	-12(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, 8(%esp)
	movl	%ecx, (%esp)
	call	__ZNSolsEy
	movl	$__ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, 4(%esp)
	movl	%eax, (%esp)
	call	__ZNSolsEPFRSoS_E
	movl	$1, %eax
	leave
	ret
	.section	.text$_ZSt3hexRSt8ios_base,"x"
	.linkonce discard
	.align 2
.globl __ZSt3hexRSt8ios_base
	.def	__ZSt3hexRSt8ios_base;	.scl	2;	.type	32;	.endef
__ZSt3hexRSt8ios_base:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	$74, 8(%esp)
	movl	$8, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNSt8ios_base4setfESt13_Ios_FmtflagsS0_
	movl	8(%ebp), %eax
	leave
	ret
	.section	.text$_ZNSt8ios_base4setfESt13_Ios_FmtflagsS0_,"x"
	.linkonce discard
	.align 2
.globl __ZNSt8ios_base4setfESt13_Ios_FmtflagsS0_
	.def	__ZNSt8ios_base4setfESt13_Ios_FmtflagsS0_;	.scl	2;	.type	32;	.endef
__ZNSt8ios_base4setfESt13_Ios_FmtflagsS0_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	12(%eax), %eax
	movl	%eax, -4(%ebp)
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZStcoSt13_Ios_Fmtflags
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	addl	$12, %eax
	movl	%eax, (%esp)
	call	__ZStaNRSt13_Ios_FmtflagsS_
	movl	16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZStanSt13_Ios_FmtflagsS_
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	addl	$12, %eax
	movl	%eax, (%esp)
	call	__ZStoRRSt13_Ios_FmtflagsS_
	movl	-4(%ebp), %eax
	leave
	ret
	.section	.text$_ZStoRRSt13_Ios_FmtflagsS_,"x"
	.linkonce discard
	.align 2
.globl __ZStoRRSt13_Ios_FmtflagsS_
	.def	__ZStoRRSt13_Ios_FmtflagsS_;	.scl	2;	.type	32;	.endef
__ZStoRRSt13_Ios_FmtflagsS_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, (%esp)
	call	__ZStorSt13_Ios_FmtflagsS_
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	movl	8(%ebp), %eax
	leave
	ret
	.section	.text$_ZStorSt13_Ios_FmtflagsS_,"x"
	.linkonce discard
	.align 2
.globl __ZStorSt13_Ios_FmtflagsS_
	.def	__ZStorSt13_Ios_FmtflagsS_;	.scl	2;	.type	32;	.endef
__ZStorSt13_Ios_FmtflagsS_:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %eax
	orl	8(%ebp), %eax
	popl	%ebp
	ret
	.section	.text$_ZStanSt13_Ios_FmtflagsS_,"x"
	.linkonce discard
	.align 2
.globl __ZStanSt13_Ios_FmtflagsS_
	.def	__ZStanSt13_Ios_FmtflagsS_;	.scl	2;	.type	32;	.endef
__ZStanSt13_Ios_FmtflagsS_:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %eax
	andl	8(%ebp), %eax
	popl	%ebp
	ret
	.section	.text$_ZStaNRSt13_Ios_FmtflagsS_,"x"
	.linkonce discard
	.align 2
.globl __ZStaNRSt13_Ios_FmtflagsS_
	.def	__ZStaNRSt13_Ios_FmtflagsS_;	.scl	2;	.type	32;	.endef
__ZStaNRSt13_Ios_FmtflagsS_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, (%esp)
	call	__ZStanSt13_Ios_FmtflagsS_
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	movl	8(%ebp), %eax
	leave
	ret
	.section	.text$_ZStcoSt13_Ios_Fmtflags,"x"
	.linkonce discard
	.align 2
.globl __ZStcoSt13_Ios_Fmtflags
	.def	__ZStcoSt13_Ios_Fmtflags;	.scl	2;	.type	32;	.endef
__ZStcoSt13_Ios_Fmtflags:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	notl	%eax
	popl	%ebp
	ret
	.section	.text$_ZSt3minIjERKT_S2_S2_,"x"
	.linkonce discard
	.align 2
.globl __ZSt3minIjERKT_S2_S2_
	.def	__ZSt3minIjERKT_S2_S2_;	.scl	2;	.type	32;	.endef
__ZSt3minIjERKT_S2_S2_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	12(%ebp), %eax
	movl	8(%ebp), %edx
	movl	(%eax), %eax
	cmpl	(%edx), %eax
	jae	L19
	movl	12(%ebp), %eax
	movl	%eax, -4(%ebp)
	jmp	L18
L19:
	movl	8(%ebp), %eax
	movl	%eax, -4(%ebp)
L18:
	movl	-4(%ebp), %eax
	leave
	ret
	.text
	.align 2
	.def	__Z41__static_initialization_and_destruction_0ii;	.scl	3;	.type	32;	.endef
__Z41__static_initialization_and_destruction_0ii:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	cmpl	$65535, 12(%ebp)
	jne	L21
	cmpl	$1, 8(%ebp)
	jne	L21
	movl	$__ZSt8__ioinit, (%esp)
	call	__ZNSt8ios_base4InitC1Ev
L21:
	cmpl	$65535, 12(%ebp)
	jne	L20
	cmpl	$0, 8(%ebp)
	jne	L20
	movl	$__ZSt8__ioinit, (%esp)
	call	__ZNSt8ios_base4InitD1Ev
L20:
	leave
	ret
	.align 2
	.def	__GLOBAL__I_main;	.scl	3;	.type	32;	.endef
__GLOBAL__I_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	$65535, 4(%esp)
	movl	$1, (%esp)
	call	__Z41__static_initialization_and_destruction_0ii
	leave
	ret
	.section	.ctors,"w"
	.align 4
	.long	__GLOBAL__I_main
	.text
	.align 2
	.def	__GLOBAL__D_main;	.scl	3;	.type	32;	.endef
__GLOBAL__D_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	$65535, 4(%esp)
	movl	$0, (%esp)
	call	__Z41__static_initialization_and_destruction_0ii
	leave
	ret
	.section	.dtors,"w"
	.align 4
	.long	__GLOBAL__D_main
	.def	__ZNSt8ios_base4InitD1Ev;	.scl	3;	.type	32;	.endef
	.def	__ZNSolsEPFRSoS_E;	.scl	3;	.type	32;	.endef
	.def	__ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_;	.scl	3;	.type	32;	.endef
	.def	__ZNSolsEy;	.scl	3;	.type	32;	.endef
	.def	__ZNSolsEPFRSt8ios_baseS0_E;	.scl	3;	.type	32;	.endef
	.def	__ZNSt8ios_base4InitC1Ev;	.scl	3;	.type	32;	.endef
	.def	__ZNKSsixEj;	.scl	3;	.type	32;	.endef
	.def	__ZNKSs4sizeEv;	.scl	3;	.type	32;	.endef
	.def	__ZSt3minIjERKT_S2_S2_;	.scl	3;	.type	32;	.endef
