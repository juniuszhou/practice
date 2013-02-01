	.file	"virtualFun.cc"
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.text._ZN1a2okEv,"axG",@progbits,_ZN1a2okEv,comdat
	.align 2
	.weak	_ZN1a2okEv
	.type	_ZN1a2okEv, @function
_ZN1a2okEv:
.LFB966:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$_ZSt4cout, (%esp)
	call	_ZNSolsEi
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE966:
	.size	_ZN1a2okEv, .-_ZN1a2okEv
	.section	.text._ZN1a3ok2Ev,"axG",@progbits,_ZN1a3ok2Ev,comdat
	.align 2
	.weak	_ZN1a3ok2Ev
	.type	_ZN1a3ok2Ev, @function
_ZN1a3ok2Ev:
.LFB967:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$_ZSt4cout, (%esp)
	call	_ZNSolsEi
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE967:
	.size	_ZN1a3ok2Ev, .-_ZN1a3ok2Ev
	.section	.text._ZN1a3funEv,"axG",@progbits,_ZN1a3funEv,comdat
	.align 2
	.weak	_ZN1a3funEv
	.type	_ZN1a3funEv, @function
_ZN1a3funEv:
.LFB968:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	$0, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$_ZSt4cout, (%esp)
	call	_ZNSolsEi
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE968:
	.size	_ZN1a3funEv, .-_ZN1a3funEv
	.section	.text._ZN1aC2Ev,"axG",@progbits,_ZN1aC5Ev,comdat
	.align 2
	.weak	_ZN1aC2Ev
	.type	_ZN1aC2Ev, @function
_ZN1aC2Ev:
.LFB972:
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
.LFE972:
	.size	_ZN1aC2Ev, .-_ZN1aC2Ev
	.section	.text._ZN1bC2Ev,"axG",@progbits,_ZN1bC5Ev,comdat
	.align 2
	.weak	_ZN1bC2Ev
	.type	_ZN1bC2Ev, @function
_ZN1bC2Ev:
.LFB974:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN1aC2Ev
	movl	8(%ebp), %eax
	movl	$_ZTV1b+8, (%eax)
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE974:
	.size	_ZN1bC2Ev, .-_ZN1bC2Ev
	.text
	.globl	main
	.type	main, @function
main:
.LFB969:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	andl	$-16, %esp
	subl	$32, %esp
	movl	$8, (%esp)
	.cfi_offset 3, -12
	call	_Znwj
	movl	%eax, %ebx
	movl	%ebx, (%esp)
	call	_ZN1bC1Ev
	movl	%ebx, 28(%esp)
	movl	28(%esp), %eax
	movl	(%eax), %eax
	addl	$8, %eax
	movl	(%eax), %edx
	movl	28(%esp), %eax
	movl	%eax, (%esp)
	call	*%edx
	movl	$0, %eax
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	.cfi_restore 3
	ret
	.cfi_endproc
.LFE969:
	.size	main, .-main
	.weak	_ZTV1b
	.section	.rodata._ZTV1b,"aG",@progbits,_ZTV1b,comdat
	.align 8
	.type	_ZTV1b, @object
	.size	_ZTV1b, 20
_ZTV1b:
	.long	0
	.long	_ZTI1b
	.long	_ZN1a2okEv
	.long	_ZN1a3ok2Ev
	.long	_ZN1a3funEv
	.weak	_ZTV1a
	.section	.rodata._ZTV1a,"aG",@progbits,_ZTV1a,comdat
	.align 8
	.type	_ZTV1a, @object
	.size	_ZTV1a, 20
_ZTV1a:
	.long	0
	.long	_ZTI1a
	.long	_ZN1a2okEv
	.long	_ZN1a3ok2Ev
	.long	_ZN1a3funEv
	.weak	_ZTS1b
	.section	.rodata._ZTS1b,"aG",@progbits,_ZTS1b,comdat
	.type	_ZTS1b, @object
	.size	_ZTS1b, 3
_ZTS1b:
	.string	"1b"
	.weak	_ZTI1b
	.section	.rodata._ZTI1b,"aG",@progbits,_ZTI1b,comdat
	.align 4
	.type	_ZTI1b, @object
	.size	_ZTI1b, 12
_ZTI1b:
	.long	_ZTVN10__cxxabiv120__si_class_type_infoE+8
	.long	_ZTS1b
	.long	_ZTI1a
	.weak	_ZTS1a
	.section	.rodata._ZTS1a,"aG",@progbits,_ZTS1a,comdat
	.type	_ZTS1a, @object
	.size	_ZTS1a, 3
_ZTS1a:
	.string	"1a"
	.weak	_ZTI1a
	.section	.rodata._ZTI1a,"aG",@progbits,_ZTI1a,comdat
	.align 4
	.type	_ZTI1a, @object
	.size	_ZTI1a, 8
_ZTI1a:
	.long	_ZTVN10__cxxabiv117__class_type_infoE+8
	.long	_ZTS1a
	.text
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB976:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	cmpl	$1, 8(%ebp)
	jne	.L7
	cmpl	$65535, 12(%ebp)
	jne	.L7
	movl	$_ZStL8__ioinit, (%esp)
	call	_ZNSt8ios_base4InitC1Ev
	movl	$_ZNSt8ios_base4InitD1Ev, %eax
	movl	$__dso_handle, 8(%esp)
	movl	$_ZStL8__ioinit, 4(%esp)
	movl	%eax, (%esp)
	call	__cxa_atexit
.L7:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE976:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I_main, @function
_GLOBAL__sub_I_main:
.LFB977:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	$65535, 4(%esp)
	movl	$1, (%esp)
	call	_Z41__static_initialization_and_destruction_0ii
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE977:
	.size	_GLOBAL__sub_I_main, .-_GLOBAL__sub_I_main
	.section	.ctors,"aw",@progbits
	.align 4
	.long	_GLOBAL__sub_I_main
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
	.weak	_ZN1aC1Ev
	.set	_ZN1aC1Ev,_ZN1aC2Ev
	.weak	_ZN1bC1Ev
	.set	_ZN1bC1Ev,_ZN1bC2Ev
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
