	.file	"conDe.cc"
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.rodata
.LC0:
	.string	"one created"
	.section	.text._ZN3oneC1Ev,"axG",@progbits,_ZN3oneC1Ev,comdat
	.align 2
	.weak	_ZN3oneC1Ev
	.type	_ZN3oneC1Ev, @function
_ZN3oneC1Ev:
.LFB959:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	$.LC0, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	leave
	ret
	.cfi_endproc
.LFE959:
	.size	_ZN3oneC1Ev, .-_ZN3oneC1Ev
	.section	.rodata
.LC1:
	.string	"one deleted"
	.section	.text._ZN3oneD1Ev,"axG",@progbits,_ZN3oneD1Ev,comdat
	.align 2
	.weak	_ZN3oneD1Ev
	.type	_ZN3oneD1Ev, @function
_ZN3oneD1Ev:
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
	movl	$.LC1, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	leave
	ret
	.cfi_endproc
.LFE962:
	.size	_ZN3oneD1Ev, .-_ZN3oneD1Ev
.globl _Unwind_Resume
	.text
.globl main
	.type	main, @function
main:
.LFB963:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA963
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$24, %rsp
	leaq	-33(%rbp), %rax
	movq	%rax, %rdi
.LEHB0:
	.cfi_offset 3, -40
	.cfi_offset 12, -32
	.cfi_offset 13, -24
	call	_ZN3oneC1Ev
.LEHE0:
	movl	$1, %edi
.LEHB1:
	call	_Znwm
.LEHE1:
	movq	%rax, %rbx
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB2:
	call	_ZN3oneC1Ev
.LEHE2:
	movq	%rbx, -48(%rbp)
	leaq	-33(%rbp), %rax
	movq	%rax, %rdi
.LEHB3:
	call	_ZN3oneD1Ev
	jmp	.L13
.L11:
.L8:
	movl	%edx, %r12d
	movq	%rax, %r13
	movq	%rbx, %rdi
	call	_ZdlPv
	movq	%r13, %rax
	movslq	%r12d,%rdx
	jmp	.L9
.L13:
	leaq	-33(%rbp), %rax
	movq	%rax, %rsi
	movl	$_ZSt4cout, %edi
	call	_ZNSolsEPKv
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
.LEHE3:
	movl	$1, %ebx
	leaq	-33(%rbp), %rax
	movq	%rax, %rdi
.LEHB4:
	call	_ZN3oneD1Ev
.LEHE4:
	movl	%ebx, %eax
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	leave
	ret
.L12:
.L9:
	movl	%edx, %ebx
	movq	%rax, %r12
	leaq	-33(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN3oneD1Ev
	movq	%r12, %rax
	movslq	%ebx,%rdx
	movq	%rax, %rdi
.LEHB5:
	call	_Unwind_Resume
.LEHE5:
	.cfi_endproc
.LFE963:
	.size	main, .-main
.globl __gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA963:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE963-.LLSDACSB963
.LLSDACSB963:
	.uleb128 .LEHB0-.LFB963
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0x0
	.uleb128 0x0
	.uleb128 .LEHB1-.LFB963
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L12-.LFB963
	.uleb128 0x0
	.uleb128 .LEHB2-.LFB963
	.uleb128 .LEHE2-.LEHB2
	.uleb128 .L11-.LFB963
	.uleb128 0x0
	.uleb128 .LEHB3-.LFB963
	.uleb128 .LEHE3-.LEHB3
	.uleb128 .L12-.LFB963
	.uleb128 0x0
	.uleb128 .LEHB4-.LFB963
	.uleb128 .LEHE4-.LEHB4
	.uleb128 0x0
	.uleb128 0x0
	.uleb128 .LEHB5-.LFB963
	.uleb128 .LEHE5-.LEHB5
	.uleb128 0x0
	.uleb128 0x0
.LLSDACSE963:
	.text
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB973:
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
	jne	.L16
	cmpl	$65535, -8(%rbp)
	jne	.L16
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$_ZNSt8ios_base4InitD1Ev, %eax
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movq	%rax, %rdi
	call	__cxa_atexit
.L16:
	leave
	ret
	.cfi_endproc
.LFE973:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__I_main, @function
_GLOBAL__I_main:
.LFB974:
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
.LFE974:
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
