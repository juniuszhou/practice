	.file	"exception.cc"
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
.globl _Unwind_Resume
	.text
.globl _Z3funv
	.type	_Z3funv, @function
_Z3funv:
.LFB957:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA957
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$16, %rsp
	leaq	-17(%rbp), %rax
	movq	%rax, %rdi
.LEHB0:
	.cfi_offset 3, -32
	.cfi_offset 12, -24
	call	_ZN3oneC1Ev
.LEHE0:
	cmpl	$45, -24(%rbp)
	jne	.L10
	movl	$4, %edi
	call	__cxa_allocate_exception
	movq	%rax, %rdx
	movl	$111, (%rdx)
	movl	$0, %edx
	movl	$_ZTIi, %esi
	movq	%rax, %rdi
.LEHB1:
	call	__cxa_throw
.LEHE1:
.L8:
	cmpq	$1, %rdx
	jne	.L5
.L4:
	movq	%rax, %rdi
	call	__cxa_begin_catch
	movl	(%rax), %eax
	movl	%eax, -28(%rbp)
.LEHB2:
	call	__cxa_end_catch
.LEHE2:
	jmp	.L3
.L10:
	nop
.L3:
	leaq	-17(%rbp), %rax
	movq	%rax, %rdi
.LEHB3:
	call	_ZN3oneD1Ev
.LEHE3:
	addq	$16, %rsp
	popq	%rbx
	popq	%r12
	leave
	ret
.L9:
.L5:
	movl	%edx, %ebx
	movq	%rax, %r12
	leaq	-17(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN3oneD1Ev
	movq	%r12, %rax
	movslq	%ebx,%rdx
	movq	%rax, %rdi
.LEHB4:
	call	_Unwind_Resume
.LEHE4:
	.cfi_endproc
.LFE957:
	.size	_Z3funv, .-_Z3funv
.globl __gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
	.align 4
.LLSDA957:
	.byte	0xff
	.byte	0x3
	.uleb128 .LLSDATT957-.LLSDATTD957
.LLSDATTD957:
	.byte	0x1
	.uleb128 .LLSDACSE957-.LLSDACSB957
.LLSDACSB957:
	.uleb128 .LEHB0-.LFB957
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0x0
	.uleb128 0x0
	.uleb128 .LEHB1-.LFB957
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L8-.LFB957
	.uleb128 0x3
	.uleb128 .LEHB2-.LFB957
	.uleb128 .LEHE2-.LEHB2
	.uleb128 .L9-.LFB957
	.uleb128 0x0
	.uleb128 .LEHB3-.LFB957
	.uleb128 .LEHE3-.LEHB3
	.uleb128 0x0
	.uleb128 0x0
	.uleb128 .LEHB4-.LFB957
	.uleb128 .LEHE4-.LEHB4
	.uleb128 0x0
	.uleb128 0x0
.LLSDACSE957:
	.byte	0x0
	.byte	0x0
	.byte	0x1
	.byte	0x7d
	.align 4
	.long	_ZTIf
.LLSDATT957:
	.text
.globl main
	.type	main, @function
main:
.LFB958:
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
.LFE958:
	.size	main, .-main
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB959:
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
	jne	.L15
	cmpl	$65535, -8(%rbp)
	jne	.L15
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$_ZNSt8ios_base4InitD1Ev, %eax
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movq	%rax, %rdi
	call	__cxa_atexit
.L15:
	leave
	ret
	.cfi_endproc
.LFE959:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__I__Z3funv, @function
_GLOBAL__I__Z3funv:
.LFB960:
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
.LFE960:
	.size	_GLOBAL__I__Z3funv, .-_GLOBAL__I__Z3funv
	.section	.ctors,"aw",@progbits
	.align 8
	.quad	_GLOBAL__I__Z3funv
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
	.ident	"GCC: (Ubuntu 4.4.1-4ubuntu8) 4.4.1"
	.section	.note.GNU-stack,"",@progbits
