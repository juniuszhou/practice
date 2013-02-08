	.file	"cGlobalObj.cc"
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.text
	.align 2
.globl _ZN1aC2Ev
	.type	_ZN1aC2Ev, @function
_ZN1aC2Ev:
.LFB958:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	$_ZTV1a+16, (%rax)
	movq	-8(%rbp), %rax
	movl	$10, 8(%rax)
	leave
	ret
	.cfi_endproc
.LFE958:
	.size	_ZN1aC2Ev, .-_ZN1aC2Ev
	.align 2
.globl _ZN1aC1Ev
	.type	_ZN1aC1Ev, @function
_ZN1aC1Ev:
.LFB959:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	$_ZTV1a+16, (%rax)
	movq	-8(%rbp), %rax
	movl	$10, 8(%rax)
	leave
	ret
	.cfi_endproc
.LFE959:
	.size	_ZN1aC1Ev, .-_ZN1aC1Ev
	.section	.rodata
.LC0:
	.string	"out of provess"
	.text
	.align 2
.globl _ZN1aD2Ev
	.type	_ZN1aD2Ev, @function
_ZN1aD2Ev:
.LFB961:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	$_ZTV1a+16, (%rax)
	movl	$.LC0, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	movl	$0, %eax
	testb	%al, %al
	je	.L8
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv
.L8:
	leave
	ret
	.cfi_endproc
.LFE961:
	.size	_ZN1aD2Ev, .-_ZN1aD2Ev
	.align 2
.globl _ZN1aD1Ev
	.type	_ZN1aD1Ev, @function
_ZN1aD1Ev:
.LFB962:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	$_ZTV1a+16, (%rax)
	movl	$.LC0, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	movl	$0, %eax
	testb	%al, %al
	je	.L12
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv
.L12:
	leave
	ret
	.cfi_endproc
.LFE962:
	.size	_ZN1aD1Ev, .-_ZN1aD1Ev
	.align 2
.globl _ZN1aD0Ev
	.type	_ZN1aD0Ev, @function
_ZN1aD0Ev:
.LFB963:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	$_ZTV1a+16, (%rax)
	movl	$.LC0, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	movl	$1, %eax
	testb	%al, %al
	je	.L16
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv
.L16:
	leave
	ret
	.cfi_endproc
.LFE963:
	.size	_ZN1aD0Ev, .-_ZN1aD0Ev
	.align 2
.globl _ZN2aaC2Ev
	.type	_ZN2aaC2Ev, @function
_ZN2aaC2Ev:
.LFB965:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	$_ZTV2aa+16, (%rax)
	movq	-8(%rbp), %rax
	movl	$10, 8(%rax)
	leave
	ret
	.cfi_endproc
.LFE965:
	.size	_ZN2aaC2Ev, .-_ZN2aaC2Ev
	.align 2
.globl _ZN2aaC1Ev
	.type	_ZN2aaC1Ev, @function
_ZN2aaC1Ev:
.LFB966:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	$_ZTV2aa+16, (%rax)
	movq	-8(%rbp), %rax
	movl	$10, 8(%rax)
	leave
	ret
	.cfi_endproc
.LFE966:
	.size	_ZN2aaC1Ev, .-_ZN2aaC1Ev
	.align 2
.globl _ZN2aaD2Ev
	.type	_ZN2aaD2Ev, @function
_ZN2aaD2Ev:
.LFB968:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	$_ZTV2aa+16, (%rax)
	movl	$.LC0, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	movl	$0, %eax
	testb	%al, %al
	je	.L24
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv
.L24:
	leave
	ret
	.cfi_endproc
.LFE968:
	.size	_ZN2aaD2Ev, .-_ZN2aaD2Ev
	.align 2
.globl _ZN2aaD1Ev
	.type	_ZN2aaD1Ev, @function
_ZN2aaD1Ev:
.LFB969:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	$_ZTV2aa+16, (%rax)
	movl	$.LC0, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	movl	$0, %eax
	testb	%al, %al
	je	.L28
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv
.L28:
	leave
	ret
	.cfi_endproc
.LFE969:
	.size	_ZN2aaD1Ev, .-_ZN2aaD1Ev
	.align 2
.globl _ZN2aaD0Ev
	.type	_ZN2aaD0Ev, @function
_ZN2aaD0Ev:
.LFB970:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	$_ZTV2aa+16, (%rax)
	movl	$.LC0, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	movl	$1, %eax
	testb	%al, %al
	je	.L32
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv
.L32:
	leave
	ret
	.cfi_endproc
.LFE970:
	.size	_ZN2aaD0Ev, .-_ZN2aaD0Ev
.globl gaa1234
	.bss
	.align 16
	.type	gaa1234, @object
	.size	gaa1234, 16
gaa1234:
	.zero	16
.globl ga1234
	.align 16
	.type	ga1234, @object
	.size	ga1234, 16
ga1234:
	.zero	16
.globl abcd
	.data
	.align 4
	.type	abcd, @object
	.size	abcd, 4
abcd:
	.long	23456
	.text
.globl main
	.type	main, @function
main:
.LFB971:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	movl	$1, %eax
	leave
	ret
	.cfi_endproc
.LFE971:
	.size	main, .-main
	.weak	_ZTV2aa
	.section	.rodata._ZTV2aa,"aG",@progbits,_ZTV2aa,comdat
	.align 32
	.type	_ZTV2aa, @object
	.size	_ZTV2aa, 32
_ZTV2aa:
	.quad	0
	.quad	_ZTI2aa
	.quad	_ZN2aaD1Ev
	.quad	_ZN2aaD0Ev
	.weak	_ZTV1a
	.section	.rodata._ZTV1a,"aG",@progbits,_ZTV1a,comdat
	.align 32
	.type	_ZTV1a, @object
	.size	_ZTV1a, 32
_ZTV1a:
	.quad	0
	.quad	_ZTI1a
	.quad	_ZN1aD1Ev
	.quad	_ZN1aD0Ev
	.weak	_ZTI2aa
	.section	.rodata._ZTI2aa,"aG",@progbits,_ZTI2aa,comdat
	.align 16
	.type	_ZTI2aa, @object
	.size	_ZTI2aa, 16
_ZTI2aa:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTS2aa
	.weak	_ZTS2aa
	.section	.rodata._ZTS2aa,"aG",@progbits,_ZTS2aa,comdat
	.type	_ZTS2aa, @object
	.size	_ZTS2aa, 4
_ZTS2aa:
	.string	"2aa"
	.weak	_ZTI1a
	.section	.rodata._ZTI1a,"aG",@progbits,_ZTI1a,comdat
	.align 16
	.type	_ZTI1a, @object
	.size	_ZTI1a, 16
_ZTI1a:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTS1a
	.weak	_ZTS1a
	.section	.rodata._ZTS1a,"aG",@progbits,_ZTS1a,comdat
	.type	_ZTS1a, @object
	.size	_ZTS1a, 3
_ZTS1a:
	.string	"1a"
	.text
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB980:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	cmpl	$1, -4(%rbp)
	jne	.L37
	cmpl	$65535, -8(%rbp)
	jne	.L37
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$_ZNSt8ios_base4InitD1Ev, %eax
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movq	%rax, %rdi
	call	__cxa_atexit
	movl	$gaa1234, %edi
	call	_ZN2aaC1Ev
	movl	$_ZN2aaD1Ev, %eax
	movl	$__dso_handle, %edx
	movl	$gaa1234, %esi
	movq	%rax, %rdi
	call	__cxa_atexit
	movl	$ga1234, %edi
	call	_ZN1aC1Ev
	movl	$_ZN1aD1Ev, %eax
	movl	$__dso_handle, %edx
	movl	$ga1234, %esi
	movq	%rax, %rdi
	call	__cxa_atexit
.L37:
	leave
	ret
	.cfi_endproc
.LFE980:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__I__ZN1aC2Ev, @function
_GLOBAL__I__ZN1aC2Ev:
.LFB981:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	movl	$65535, %esi
	movl	$1, %edi
	call	_Z41__static_initialization_and_destruction_0ii
	leave
	ret
	.cfi_endproc
.LFE981:
	.size	_GLOBAL__I__ZN1aC2Ev, .-_GLOBAL__I__ZN1aC2Ev
	.section	.ctors,"aw",@progbits
	.align 8
	.quad	_GLOBAL__I__ZN1aC2Ev
	.weakref	_ZL20__gthrw_pthread_oncePiPFvvE,pthread_once
	.weakref	_ZL27__gthrw_pthread_getspecificj,pthread_getspecific
	.weakref	_ZL27__gthrw_pthread_setspecificjPKv,pthread_setspecific
	.weakref	_ZL22__gthrw_pthread_createPmPK14pthread_attr_tPFPvS3_ES3_,pthread_create
	.weakref	_ZL20__gthrw_pthread_joinmPPv,pthread_join
	.weakref	_ZL21__gthrw_pthread_equalmm,pthread_equal
	.weakref	_ZL20__gthrw_pthread_selfv,pthread_self
	.weakref	_ZL22__gthrw_pthread_detachm,pthread_detach
	.weakref	_ZL22__gthrw_pthread_cancelm,pthread_cancel
	.weakref	_ZL19__gthrw_sched_yieldv,sched_yield
	.weakref	_ZL26__gthrw_pthread_mutex_lockP15pthread_mutex_t,pthread_mutex_lock
	.weakref	_ZL29__gthrw_pthread_mutex_trylockP15pthread_mutex_t,pthread_mutex_trylock
	.weakref	_ZL31__gthrw_pthread_mutex_timedlockP15pthread_mutex_tPK8timespec,pthread_mutex_timedlock
	.weakref	_ZL28__gthrw_pthread_mutex_unlockP15pthread_mutex_t,pthread_mutex_unlock
	.weakref	_ZL26__gthrw_pthread_mutex_initP15pthread_mutex_tPK19pthread_mutexattr_t,pthread_mutex_init
	.weakref	_ZL29__gthrw_pthread_mutex_destroyP15pthread_mutex_t,pthread_mutex_destroy
	.weakref	_ZL30__gthrw_pthread_cond_broadcastP14pthread_cond_t,pthread_cond_broadcast
	.weakref	_ZL27__gthrw_pthread_cond_signalP14pthread_cond_t,pthread_cond_signal
	.weakref	_ZL25__gthrw_pthread_cond_waitP14pthread_cond_tP15pthread_mutex_t,pthread_cond_wait
	.weakref	_ZL30__gthrw_pthread_cond_timedwaitP14pthread_cond_tP15pthread_mutex_tPK8timespec,pthread_cond_timedwait
	.weakref	_ZL28__gthrw_pthread_cond_destroyP14pthread_cond_t,pthread_cond_destroy
	.weakref	_ZL26__gthrw_pthread_key_createPjPFvPvE,pthread_key_create
	.weakref	_ZL26__gthrw_pthread_key_deletej,pthread_key_delete
	.weakref	_ZL30__gthrw_pthread_mutexattr_initP19pthread_mutexattr_t,pthread_mutexattr_init
	.weakref	_ZL33__gthrw_pthread_mutexattr_settypeP19pthread_mutexattr_ti,pthread_mutexattr_settype
	.weakref	_ZL33__gthrw_pthread_mutexattr_destroyP19pthread_mutexattr_t,pthread_mutexattr_destroy
	.ident	"GCC: (Ubuntu 4.4.1-4ubuntu9) 4.4.1"
	.section	.note.GNU-stack,"",@progbits
