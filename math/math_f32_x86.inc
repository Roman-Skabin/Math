;
; Copyright 2019 Roman Skabin
;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; s32 __vectorcall __ceilf(f32 value);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__ceilf@@4 proc
	roundss   xmm0, xmm0, MM_ROUND_UP_NO_EXC
	vcvtss2si eax , xmm0
	ret
__ceilf@@4 endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; s32 __vectorcall __floorf(f32 value);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__floorf@@4 proc
	roundss   xmm0, xmm0, MM_ROUND_DOWN_NO_EXC
	vcvtss2si eax , xmm0
	ret
__floorf@@4 endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; s32 __vectorcall __roundf(f32 value);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__roundf@@4 proc
	addss     xmm0, HALF_32
	roundss   xmm0, xmm0, MM_ROUND_DOWN_NO_EXC
	vcvtss2si eax , xmm0
	ret
__roundf@@4 endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __expf(f32 power);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___expf proc
    fld     dword ptr [esp+4]
    fldl2e
    fmul
    fld     st(0)
    frndint
    fsub    st(1), st(0)
    fxch
    f2xm1
    fld1
    fadd
    fscale
    fstp    st(1)
    ret
___expf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __vectorcall __sqrf(f32 base);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__sqrf@@4 proc
	vmulss xmm0, xmm0, xmm0
	ret
__sqrf@@4 endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __powf(f32 base, f32 power);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___powf proc
	fld    dword ptr [esp+8]
	fld    dword ptr [esp+4]
	fyl2x
	fld1
	fld    st(1)
	fprem
	f2xm1
	fadd
	fscale
	fxch
	fstp   st(0)
	ret
___powf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __vectorcall __sqrtf(f32 base);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__sqrtf@@4 proc
	sqrtss xmm0, xmm0
	ret
__sqrtf@@4 endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __rootf(f32 base, f32 root);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___rootf proc
	fld    dword ptr [esp+8]
	fld1
	fdivr
	fld    dword ptr [esp+4]
	fyl2x
	fld1
	fld    st(1)
	fprem
	f2xm1
	fadd
	fscale
	fxch
	fstp   st(0)
	ret
___rootf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __cosf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___cosf proc
	fld  dword ptr [esp+4]
	fcos
	ret
___cosf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __sinf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___sinf proc
	fld  dword ptr [esp+4]
	fsin
	ret
___sinf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __tanf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___tanf proc
	fld   dword ptr [esp+4]
	fptan
	fstp  st(0)
	ret
___tanf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __ctanf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___ctanf proc
	fld   dword ptr [esp+4]
	fptan
	fdivr
	ret
___ctanf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __acosf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___acosf proc
	fld    dword ptr [esp+4]
	fld    st(0)
	fmul   st(0), st(0)
	fld1
	fsubrp st(1), st(0)
	fsqrt
	fxch
	fpatan
	ret
___acosf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __asinf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___asinf proc
	fld    dword ptr [esp+4]
	fld    st(0)
	fmul   st(0), st(0)
	fld1
	fsubrp st(1), st(0)
	fsqrt
	fpatan
	ret
___asinf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __atanf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___atanf proc
	fld    dword ptr [esp+4]
	fld1
	fpatan
	ret
___atanf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __actanf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___actanf proc
	fld    dword ptr [esp+4]
	fld1
	fpatan
	fchs
	fld    PI_2_32
	fadd
	ret
___actanf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __coshf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___coshf proc
	push   ebp
	mov    ebp, esp
	sub    esp, 4

	vmovss xmm0, dword ptr [ebp+8]
	vmovss dword ptr [esp], xmm0
	call   ___expf
	fld    dword ptr [esp]
	fchs
	fstp   dword ptr [esp]
	call   ___expf
	fadd
	fld    TWO_32
	fdiv

	mov    esp, ebp
	pop    ebp
	ret
___coshf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __sinhf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___sinhf proc
	push   ebp
	mov    ebp, esp
	sub    esp, 4

	vmovss xmm0, dword ptr [ebp+8]
	vmovss dword ptr [esp], xmm0
	call   ___expf
	fld    dword ptr [esp]
	fchs
	fstp   dword ptr [esp]
	call   ___expf
	fsub
	fld    TWO_32
	fdiv

	mov    esp, ebp
	pop    ebp
	ret
___sinhf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __tanhf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___tanhf proc
	push   ebp
	mov    ebp, esp
	sub    esp, 4
	
	vmovss xmm0, dword ptr [ebp+8]
	vmovss dword ptr [esp], xmm0
	call   ___sinhf
	call   ___coshf
	fdiv

	mov    esp, ebp
	pop    ebp
	ret
___tanhf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __ctanhf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___ctanhf proc
	push   ebp
	mov    ebp, esp
	sub    esp, 4
	
	vmovss xmm0, dword ptr [ebp+8]
	vmovss dword ptr [esp], xmm0
	call   ___coshf
	call   ___sinhf
	fdiv

	mov    esp, ebp
	pop    ebp
	ret
___ctanhf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __acoshf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___acoshf proc
	fld    dword ptr [esp+4]
	fld    st(0)
	fmul   st(0), st(0)
	fld1
	fsub
	fsqrt
	fadd
	fldln2
	fxch
	fyl2x
	ret
___acoshf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __asinhf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___asinhf proc
	fld    dword ptr [esp+4]
	fld    st(0)
	fmul   st(0), st(0)
	fld1
	fadd
	fsqrt
	fadd
	fldln2
	fxch
	fyl2x
	ret
___asinhf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __atanhf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___atanhf proc
	fld    dword ptr [esp+4]
	fld    st(0)
	fld1
	fadd   st(1), st(0)
	fsubrp st(2), st(0)
	fdivr
	fldln2
	fxch
	fyl2x
	fld    TWO_32
	fdiv
	ret
___atanhf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __actanhf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___actanhf proc
	fld    dword ptr [esp+4]
	fld    st(0)
	fld1
	fadd   st(1), st(0)
	fsubp  st(2), st(0)
	fdivr
	fldln2
	fxch
	fyl2x
	fld    TWO_32
	fdiv
	ret
___actanhf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __logf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___logf proc
	fldln2
	fld    dword ptr [esp+4]
	fyl2x
	ret
___logf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __log2f(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___log2f proc
	fld1
	fld   dword ptr [esp+4]
	fyl2x
	ret
___log2f endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __log10f(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___log10f proc
	fldlg2
	fld    dword ptr [esp+4]
	fyl2x
	ret
___log10f endp
