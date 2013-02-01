	.arch armv4t
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 18, 4
	.file	"bPrintInt.c"
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,4
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	.fnstart
.LFB960:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
.LCFI0:
	.setfp fp, sp, #4
	add	fp, sp, #4
.LCFI1:
	.pad #8
	sub	sp, sp, #8
.LCFI2:
	mov	r3, #123
	str	r3, [fp, #-8]
	ldr	r0, .L3
	ldr	r1, [fp, #-8]
	bl	_ZNSolsEi
	mov	r3, #1
	mov	r0, r3
	sub	sp, fp, #4
	ldmfd	sp!, {fp, lr}
	bx	lr
.L4:
	.align	2
.L3:
	.word	_ZSt4cout
.LFE960:
	.fnend
	.size	main, .-main
	.align	2
	.type	_Z41__static_initialization_and_destruction_0ii, %function
_Z41__static_initialization_and_destruction_0ii:
	.fnstart
.LFB961:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
.LCFI3:
	.setfp fp, sp, #4
	add	fp, sp, #4
.LCFI4:
	.pad #8
	sub	sp, sp, #8
.LCFI5:
	str	r0, [fp, #-8]
	str	r1, [fp, #-12]
	ldr	r3, [fp, #-8]
	cmp	r3, #1
	bne	.L7
	ldr	r2, [fp, #-12]
	ldr	r3, .L8
	cmp	r2, r3
	bne	.L7
	ldr	r0, .L8+4
	bl	_ZNSt8ios_base4InitC1Ev
	ldr	r3, .L8+8
	ldr	r0, .L8+4
	mov	r1, r3
	ldr	r2, .L8+12
	bl	__aeabi_atexit
.L7:
	sub	sp, fp, #4
	ldmfd	sp!, {fp, lr}
	bx	lr
.L9:
	.align	2
.L8:
	.word	65535
	.word	_ZStL8__ioinit
	.word	_ZNSt8ios_base4InitD1Ev
	.word	__dso_handle
.LFE961:
	.fnend
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.align	2
	.type	_GLOBAL__I_main, %function
_GLOBAL__I_main:
	.fnstart
.LFB962:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
.LCFI6:
	.setfp fp, sp, #4
	add	fp, sp, #4
.LCFI7:
	mov	r0, #1
	ldr	r1, .L12
	bl	_Z41__static_initialization_and_destruction_0ii
	sub	sp, fp, #4
	ldmfd	sp!, {fp, lr}
	bx	lr
.L13:
	.align	2
.L12:
	.word	65535
.LFE962:
	.fnend
	.size	_GLOBAL__I_main, .-_GLOBAL__I_main
	.section	.init_array,"aw",%init_array
	.align	2
	.word	_GLOBAL__I_main(target1)
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
	.ident	"GCC: (ctng-1.6.1) 4.4.3"
	.section	.note.GNU-stack,"",%progbits
