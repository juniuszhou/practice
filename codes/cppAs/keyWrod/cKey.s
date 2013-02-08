	.file	"cKey.cc"
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.text._ZN3oneC2Ev,"axG",@progbits,_ZN3oneC2Ev,comdat
	.align 2
	.weak	_ZN3oneC2Ev
	.type	_ZN3oneC2Ev, @function
_ZN3oneC2Ev:
.LFB960:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	$_ZTV3one+16, (%rax)
	leave
	ret
	.cfi_endproc
.LFE960:
	.size	_ZN3oneC2Ev, .-_ZN3oneC2Ev
	.section	.text._ZN3twoC1Ev,"axG",@progbits,_ZN3twoC1Ev,comdat
	.align 2
	.weak	_ZN3twoC1Ev
	.type	_ZN3twoC1Ev, @function
_ZN3twoC1Ev:
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
	movq	%rax, %rdi
	call	_ZN3oneC2Ev
	movq	-8(%rbp), %rax
	movq	$_ZTV3two+16, (%rax)
	leave
	ret
	.cfi_endproc
.LFE963:
	.size	_ZN3twoC1Ev, .-_ZN3twoC1Ev
	.section	.text._ZN3twoD1Ev,"axG",@progbits,_ZN3twoD1Ev,comdat
	.align 2
	.weak	_ZN3twoD1Ev
	.type	_ZN3twoD1Ev, @function
_ZN3twoD1Ev:
.LFB966:
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
	movq	$_ZTV3two+16, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN3oneD2Ev
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
.LFE966:
	.size	_ZN3twoD1Ev, .-_ZN3twoD1Ev
	.section	.text._ZN3twoD0Ev,"axG",@progbits,_ZN3twoD0Ev,comdat
	.align 2
	.weak	_ZN3twoD0Ev
	.type	_ZN3twoD0Ev, @function
_ZN3twoD0Ev:
.LFB967:
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
	movq	$_ZTV3two+16, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN3oneD2Ev
	movl	$1, %eax
	testb	%al, %al
	je	.L12
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv
.L12:
	leave
	ret
	.cfi_endproc
.LFE967:
	.size	_ZN3twoD0Ev, .-_ZN3twoD0Ev
	.text
.globl main
	.type	main, @function
main:
.LFB957:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	.cfi_offset 3, -24
	call	_ZN3twoC1Ev
	leaq	-32(%rbp), %rax
	movq	%rax, -40(%rbp)
	movl	$99, -20(%rbp)
	movq	-40(%rbp), %rax
	testq	%rax, %rax
	jne	.L14
	movl	$0, %eax
	jmp	.L15
.L14:
	movl	$0, %ecx
	movl	$_ZTI5three, %edx
	movl	$_ZTI3one, %esi
	movq	%rax, %rdi
	call	__dynamic_cast
.L15:
	movq	%rax, -48(%rbp)
	movl	$1, %ebx
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN3twoD1Ev
	movl	%ebx, %eax
	addq	$40, %rsp
	popq	%rbx
	leave
	ret
	.cfi_endproc
.LFE957:
	.size	main, .-main
	.weak	_ZTV3two
	.section	.rodata._ZTV3two,"aG",@progbits,_ZTV3two,comdat
	.align 32
	.type	_ZTV3two, @object
	.size	_ZTV3two, 32
_ZTV3two:
	.quad	0
	.quad	_ZTI3two
	.quad	_ZN3twoD1Ev
	.quad	_ZN3twoD0Ev
	.weak	_ZTS5three
	.section	.rodata._ZTS5three,"aG",@progbits,_ZTS5three,comdat
	.type	_ZTS5three, @object
	.size	_ZTS5three, 7
_ZTS5three:
	.string	"5three"
	.weak	_ZTI5three
	.section	.rodata._ZTI5three,"aG",@progbits,_ZTI5three,comdat
	.align 16
	.type	_ZTI5three, @object
	.size	_ZTI5three, 24
_ZTI5three:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTS5three
	.quad	_ZTI3one
	.weak	_ZTS3two
	.section	.rodata._ZTS3two,"aG",@progbits,_ZTS3two,comdat
	.type	_ZTS3two, @object
	.size	_ZTS3two, 5
_ZTS3two:
	.string	"3two"
	.weak	_ZTI3two
	.section	.rodata._ZTI3two,"aG",@progbits,_ZTI3two,comdat
	.align 16
	.type	_ZTI3two, @object
	.size	_ZTI3two, 24
_ZTI3two:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTS3two
	.quad	_ZTI3one
	.text
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB968:
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
	jne	.L19
	cmpl	$65535, -8(%rbp)
	jne	.L19
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$_ZNSt8ios_base4InitD1Ev, %eax
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movq	%rax, %rdi
	call	__cxa_atexit
.L19:
	leave
	ret
	.cfi_endproc
.LFE968:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__I_main, @function
_GLOBAL__I_main:
.LFB969:
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
.LFE969:
	.size	_GLOBAL__I_main, .-_GLOBAL__I_main
	.section	.ctors,"aw",@progbits
	.align 8
	.quad	_GLOBAL__I_main
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
