;
; Copyright 2019 Roman Skabin
;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; s3264 __vectorcall __ceil(f64 value);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__ceil@@8 proc
	roundsd   xmm0, xmm0, MM_ROUND_UP_NO_EXC
	vcvtsd2si rax , xmm0
	ret
__ceil@@8 endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; s3264 __vectorcall __floor(f64 value);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__floor@@8 proc
	roundsd   xmm0, xmm0, MM_ROUND_DOWN_NO_EXC
	vcvtsd2si rax , xmm0
	ret
__floor@@8 endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; s3264 __vectorcall __round(f64 value);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__round@@8 proc
	addsd     xmm0, HALF_64
	roundsd   xmm0, xmm0, MM_ROUND_DOWN_NO_EXC
	vcvtsd2si rax , xmm0
	ret
__round@@8 endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __exp(f64 power);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__exp proc
    push    rbp
    mov     rbp, rsp
    sub     rsp, 8
    
    vmovsd  qword ptr [rsp], xmm0
    fld     qword ptr [rsp]
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
    fstp    qword ptr [rsp]
    vmovsd  xmm0, qword ptr [rsp]

    mov     rsp, rbp
    pop     rbp
    ret
__exp endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __vectorcall __sqr(f64 base);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__sqr@@8 proc
	mulsd xmm0, xmm0
	ret
__sqr@@8 endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __pow(f64 base, f64 power);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__pow proc
	push   rbp
	mov    rbp, rsp
    sub    rsp, 16

    vmovsd qword ptr [rsp+8], xmm1
    vmovsd qword ptr [rsp], xmm0
	fld    qword ptr [rsp+8]
	fld    qword ptr [rsp]
	fyl2x
	fld1
	fld    st(1)
	fprem
	f2xm1
	fadd
	fscale
	fxch
	fstp   st(0)
    fstp   qword ptr [rsp]
    vmovsd xmm0, qword ptr [rsp]

	mov    rsp, rbp
	pop    rbp
	ret
__pow endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __vectorcall __sqrt(f64 base);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__sqrt@@8 proc
	sqrtsd xmm0, xmm0
	ret
__sqrt@@8 endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __root(f64 base, f64 root);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__root proc
	push    rbp
	mov     rbp, rsp
    sub     rsp, 16
	
    vmovsd  qword ptr [rsp+8], xmm1
    vmovsd  qword ptr [rsp], xmm0
	fld     qword ptr [rsp+8]
	fld1
	fdivr
	fld     qword ptr [rsp]
	fyl2x
	fld1
	fld     st(1)
	fprem
	f2xm1
	fadd
	fscale
	fxch
	fstp    st(0)
    fstp    qword ptr [rsp]
    vmovsd  xmm0, qword ptr [rsp]

	mov     rsp, rbp
	pop     rbp
	ret
__root endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __cos(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__cos proc
    push   rbp
    mov    rbp, rsp
    sub    rsp, 8

    vmovsd qword ptr [rsp], xmm0
	fld    qword ptr [rsp]
	fcos
    fstp   qword ptr [rsp]
    vmovsd xmm0, qword ptr [rsp]

    mov   rsp, rbp
    pop   rbp
	ret
__cos endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __sin(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__sin proc
    push   rbp
    mov    rbp, rsp
    sub    rsp, 8
    
    vmovsd qword ptr [rsp], xmm0
	fld    qword ptr [rsp]
	fsin
    fstp   qword ptr [rsp]
    vmovsd xmm0, qword ptr [rsp]

    mov    rsp, rbp
    pop    rbp
	ret
__sin endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __tan(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__tan proc
	push   rbp
    mov    rbp, rsp
    sub    rsp, 8
    
    vmovsd qword ptr [rsp], xmm0
	fld    qword ptr [rsp]
	fptan
	fstp   st(0)
	fstp   qword ptr [rsp]
    vmovsd xmm0, qword ptr [rsp]

    mov    rsp, rbp
    pop    rbp
	ret
__tan endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __ctan(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__ctan proc
	push   rbp
    mov    rbp, rsp
    sub    rsp, 8
    
    vmovsd qword ptr [rsp], xmm0
	fld    qword ptr [rsp]
	fptan
	fdivr
    fstp   qword ptr [rsp]
    vmovsd xmm0, qword ptr [rsp]

    mov    rsp, rbp
    pop    rbp
	ret
__ctan endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __acos(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__acos proc
	push   rbp
    mov    rbp, rsp
    sub    rsp, 8
    
    vmovsd qword ptr [rsp], xmm0
	fld    qword ptr [rsp]
	fld    st(0)
	fmul   st(0), st(0)
	fld1
	fsubrp st(1), st(0)
	fsqrt
	fxch
	fpatan
    fstp   qword ptr [rsp]
    vmovsd xmm0, qword ptr [rsp]

    mov    rsp, rbp
    pop    rbp
	ret
__acos endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __asin(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__asin proc
	push   rbp
    mov    rbp, rsp
    sub    rsp, 8
    
    vmovsd qword ptr [rsp], xmm0
	fld    qword ptr [rsp]
	fld    st(0)
	fmul   st(0), st(0)
	fld1
	fsubrp st(1), st(0)
	fsqrt
	fpatan
	fstp   qword ptr [rsp]
    vmovsd xmm0, qword ptr [rsp]

    mov    rsp, rbp
    pop    rbp
	ret
__asin endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __atan(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__atan proc
	push   rbp
    mov    rbp, rsp
    sub    rsp, 8
    
    vmovsd qword ptr [rsp], xmm0
	fld    qword ptr [rsp]
	fld1
	fpatan
	fstp   qword ptr [rsp]
    vmovsd xmm0, qword ptr [rsp]

    mov    rsp, rbp
    pop    rbp
	ret
__atan endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __actan(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__actan proc
	push   rbp
    mov    rbp, rsp
    sub    rsp, 8
    
    vmovsd qword ptr [rsp], xmm0
	fld    qword ptr [rsp]
	fld1
	fpatan
	fchs
	fld    PI_2_64
	fadd
	fstp   qword ptr [rsp]
    vmovsd xmm0, qword ptr [rsp]

    mov    rsp, rbp
    pop    rbp
	ret
__actan endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __cosh(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_exp_for_hyperbolics proc
    fld     qword ptr [rsp+8]
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
_exp_for_hyperbolics endp

__cosh proc
	push   rbp
    mov    rbp, rsp
    sub    rsp, 8

    vmovsd qword ptr [rsp], xmm0
	call   _exp_for_hyperbolics
    fld    qword ptr [rsp]
    fchs
    fstp   qword ptr [rsp]
	call   _exp_for_hyperbolics
	fadd
	fld    TWO_64
	fdiv
    fstp   qword ptr [rsp]
    vmovsd xmm0, qword ptr [rsp]

	mov    rsp, rbp
	pop    rbp
	ret
__cosh endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __sinh(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__sinh proc
	push   rbp
    mov    rbp, rsp
    sub    rsp, 8

    vmovsd qword ptr [rsp], xmm0
	call   _exp_for_hyperbolics
    fld    qword ptr [rsp]
    fchs
    fstp   qword ptr [rsp]
	call   _exp_for_hyperbolics
	fsub
	fld    TWO_64
	fdiv
    fstp   qword ptr [rsp]
    vmovsd xmm0, qword ptr [rsp]

	mov    rsp, rbp
	pop    rbp
	ret
__sinh endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __tanh(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__tanh proc
	push   rbp
	mov    rbp, rsp
	sub    rsp, 8
	
    movsd  xmm1, xmm0
	call   __sinh
    vmovsd qword ptr [rsp], xmm0
    fld    qword ptr [rsp]
    movsd  xmm0, xmm1
	call   __cosh
    vmovsd qword ptr [rsp], xmm0
    fld    qword ptr [rsp]
	fdiv
    fstp   qword ptr [rsp]
    vmovsd xmm0, qword ptr [rsp]

	mov    rsp, rbp
	pop    rbp
	ret
__tanh endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __ctanh(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__ctanh proc
	push   rbp
	mov    rbp, rsp
	sub    rsp, 8
	
    movsd  xmm1, xmm0
	call   __cosh
    vmovsd qword ptr [rsp], xmm0
    fld    qword ptr [rsp]
    movsd  xmm0, xmm1
	call   __sinh
    vmovsd qword ptr [rsp], xmm0
    fld    qword ptr [rsp]
	fdiv
    fstp   qword ptr [rsp]
    vmovsd xmm0, qword ptr [rsp]

	mov    rsp, rbp
	pop    rbp
	ret
__ctanh endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __acosh(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__acosh proc
	push    rbp
	mov     rbp, rsp
    sub     rsp, 8

    vmovsd  qword ptr [rsp], xmm0
	fld     qword ptr [rsp]
	fld     st(0)
	fmul    st(0), st(0)
	fld1
	fsub
	fsqrt
	fadd
	fldln2
	fxch
	fyl2x
    fstp    qword ptr [rsp]
    vmovsd  xmm0, qword ptr [rsp]

	mov     rsp, rbp
	pop     rbp
	ret
__acosh endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __asinh(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__asinh proc
	push   rbp
	mov    rbp, rsp
    sub    rsp, 8

    vmovsd qword ptr [rsp], xmm0
	fld    qword ptr [rsp]
	fld    st(0)
	fmul   st(0), st(0)
	fld1
	fadd
	fsqrt
	fadd
	fldln2
	fxch
	fyl2x
	fstp   qword ptr [rsp]
    vmovsd xmm0, qword ptr [rsp]

	mov    rsp, rbp
	pop    rbp
	ret
__asinh endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __atanh(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__atanh proc
	push   rbp
	mov    rbp, rsp
    sub    rsp, 8

    vmovsd qword ptr [rsp], xmm0
	fld    qword ptr [rsp]
	fld    st(0)
	fld1
	fadd   st(1), st(0)
	fsubrp st(2), st(0)
	fdivr
	fldln2
	fxch
	fyl2x
	fld    TWO_64
	fdiv
    fstp   qword ptr [rsp]
    vmovsd xmm0, qword ptr [rsp]

	mov    rsp, rbp
	pop    rbp
	ret
__atanh endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __actanh(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__actanh proc
	push   rbp
	mov    rbp, rsp
    sub    rsp, 8

    vmovsd qword ptr [rsp], xmm0
	fld    qword ptr [rsp]
	fld    st(0)
	fld1
	fadd   st(1), st(0)
	fsubp  st(2), st(0)
	fdivr
	fldln2
	fxch
	fyl2x
	fld    TWO_64
	fdiv
    fstp   qword ptr [rsp]
    vmovsd xmm0, qword ptr [rsp]

	mov    rsp, rbp
	pop    rbp
	ret
__actanh endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __log(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__log proc
    push   rbp
	mov    rbp, rsp
    sub    rsp, 8

    vmovsd qword ptr [rsp], xmm0
	fldln2
	fld    qword ptr [rsp]
	fyl2x
	fstp   qword ptr [rsp]
    vmovsd xmm0, qword ptr [rsp]

	mov    rsp, rbp
	pop    rbp
	ret
__log endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __log2(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__log2 proc
    push   rbp
	mov    rbp, rsp
    sub    rsp, 8

    vmovsd qword ptr [rsp], xmm0
	fld1
	fld    qword ptr [rsp]
	fyl2x
	fstp   qword ptr [rsp]
    vmovsd xmm0, qword ptr [rsp]

	mov    rsp, rbp
	pop    rbp
	ret
__log2 endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __log10(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__log10 proc
    push   rbp
	mov    rbp, rsp
    sub    rsp, 8

    vmovsd qword ptr [rsp], xmm0
	fldlg2
	fld    qword ptr [rsp]
	fyl2x
	fstp   qword ptr [rsp]
    vmovsd xmm0, qword ptr [rsp]

	mov    rsp, rbp
	pop    rbp
	ret
__log10 endp
