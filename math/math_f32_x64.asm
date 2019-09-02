; Copyright 2019 Roman Skabin
; 
;    Licensed under the Apache License, Version 2.0 (the "License");
;    you may not use this file except in compliance with the License.
;    You may obtain a copy of the License at
; 
;        http://www.apache.org/licenses/LICENSE-2.0
; 
;    Unless required by applicable law or agreed to in writing, software
;    distributed under the License is distributed on an "AS IS" BASIS,
;    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
;    See the License for the specific language governing permissions and
;    limitations under the License.

include math.inc

if _X64

.code

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; s32 __vectorcall __ceilf(f32 value);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__ceilf@@8 proc
	roundss  xmm0, xmm0, MM_ROUND_UP_NO_EXC
	cvtss2si rax , xmm0
	ret
__ceilf@@8 endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; s32 __vectorcall __floorf(f32 value);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__floorf@@8 proc
	roundss  xmm0, xmm0, MM_ROUND_DOWN_NO_EXC
	cvtss2si rax , xmm0
	ret
__floorf@@8 endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; s32 __vectorcall __roundf(f32 value);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__roundf@@8 proc
	addss    xmm0, HALF_32
	roundss  xmm0, xmm0, MM_ROUND_DOWN_NO_EXC
	cvtss2si rax , xmm0
	ret
__roundf@@8 endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __expf(f32 power);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__expf proc
    push    rbp
    mov     rbp, rsp
    sub     rsp, 4
    
    movss   dword ptr [rsp], xmm0
    fld     dword ptr [rsp]
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
    fstp    dword ptr [rsp]
    movss   xmm0, dword ptr [rsp]

    mov     rsp, rbp
    pop     rbp
    ret
__expf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __powf(f32 base, f32 power);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__powf proc
	push   rbp
	mov    rbp, rsp
    sub    rsp, 8

    movss  dword ptr [rsp+4], xmm1
    movss  dword ptr [rsp], xmm0
	fld    dword ptr [rsp+4]
	fld    dword ptr [rsp]
	fyl2x
	fld1
	fld    st(1)
	fprem
	f2xm1
	fadd
	fscale
	fxch
	fstp   st(0)
    fstp   dword ptr [rsp]
    movss  xmm0, dword ptr [rsp]

	mov    rsp, rbp
	pop    rbp
	ret
__powf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __vectorcall __sqrtf(f32 base);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__sqrtf@@8 proc
	sqrtss xmm0, xmm0
	ret
__sqrtf@@8 endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __rootf(f32 base, f32 root);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__rootf proc
	push   rbp
	mov    rbp, rsp
    sub    rsp, 8
	
    movss  dword ptr [rsp+4], xmm1
    movss  dword ptr [rsp], xmm0
	fld    dword ptr [rsp+4]
	fld1
	fdivr
	fld    dword ptr [rsp]
	fyl2x
	fld1
	fld    st(1)
	fprem
	f2xm1
	fadd
	fscale
	fxch
	fstp   st(0)
    fstp   dword ptr [rsp]
    movss  xmm0, dword ptr [rsp]

	mov    rsp, rbp
	pop    rbp
	ret
__rootf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __cosf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__cosf proc
    push  rbp
    mov   rbp, rsp
    sub   rsp, 4

    movss dword ptr [rsp], xmm0
	fld   dword ptr [rsp]
	fcos
    fstp  dword ptr [rsp]
    movss xmm0, dword ptr [rsp]

    mov   rsp, rbp
    pop   rbp
	ret
__cosf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __sinf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__sinf proc
    push  rbp
    mov   rbp, rsp
    sub   rsp, 4
    
    movss dword ptr [rsp], xmm0
	fld   dword ptr [rsp]
	fsin
    fstp  dword ptr [rsp]
    movss xmm0, dword ptr [rsp]

    mov   rsp, rbp
    pop   rbp
	ret
__sinf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __tanf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__tanf proc
	push  rbp
    mov   rbp, rsp
    sub   rsp, 4
    
    movss dword ptr [rsp], xmm0
	fld   dword ptr [rsp]
	fptan
	fstp  st(0)
	fstp  dword ptr [rsp]
    movss xmm0, dword ptr [rsp]

    mov   rsp, rbp
    pop   rbp
	ret
__tanf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __ctanf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__ctanf proc
	push  rbp
    mov   rbp, rsp
    sub   rsp, 4
    
    movss dword ptr [rsp], xmm0
	fld   dword ptr [rsp]
	fptan
	fdivr
    fstp  dword ptr [rsp]
    movss xmm0, dword ptr [rsp]

    mov   rsp, rbp
    pop   rbp
	ret
__ctanf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __acosf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__acosf proc
	push   rbp
    mov    rbp, rsp
    sub    rsp, 4
    
    movss  dword ptr [rsp], xmm0
	fld    dword ptr [rsp]
	fld    st(0)
	fmul   st(0), st(0)
	fld1
	fsubrp st(1), st(0)
	fsqrt
	fxch
	fpatan
    fstp   dword ptr [rsp]
    movss  xmm0, dword ptr [rsp]

    mov    rsp, rbp
    pop    rbp
	ret
__acosf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __asinf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__asinf proc
	push   rbp
    mov    rbp, rsp
    sub    rsp, 4
    
    movss  dword ptr [rsp], xmm0
	fld    dword ptr [rsp]
	fld    st(0)
	fmul   st(0), st(0)
	fld1
	fsubrp st(1), st(0)
	fsqrt
	fpatan
	fstp   dword ptr [rsp]
    movss  xmm0, dword ptr [rsp]

    mov    rsp, rbp
    pop    rbp
	ret
__asinf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __atanf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__atanf proc
	push   rbp
    mov    rbp, rsp
    sub    rsp, 4
    
    movss  dword ptr [rsp], xmm0
	fld    dword ptr [rsp]
	fld1
	fpatan
	fstp   dword ptr [rsp]
    movss  xmm0, dword ptr [rsp]

    mov    rsp, rbp
    pop    rbp
	ret
__atanf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __actanf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__actanf proc
	push    rbp
    mov     rbp, rsp
    sub     rsp, 4
    
    movss  dword ptr [rsp], xmm0
	fld    dword ptr [rsp]
	fld1
	fpatan
	fchs
	fld    PI_2_32
	fadd
	fstp   dword ptr [rsp]
    movss  xmm0, dword ptr [rsp]

    mov    rsp, rbp
    pop    rbp
	ret
__actanf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __coshf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_exp_for_hyperbolicsf proc
    fld     dword ptr [rsp+8]
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
_exp_for_hyperbolicsf endp

__coshf proc
	push  rbp
    mov   rbp, rsp
    sub   rsp, 4

    movss dword ptr [rsp], xmm0
	call  _exp_for_hyperbolicsf
    fld   dword ptr [rsp]
    fchs
    fstp  dword ptr [rsp]
	call  _exp_for_hyperbolicsf
	fadd
	fld   TWO_32
	fdiv
    fstp  dword ptr [rsp]
    movss xmm0, dword ptr [rsp]

	mov   rsp, rbp
	pop   rbp
	ret
__coshf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __sinhf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__sinhf proc
	push  rbp
    mov   rbp, rsp
    sub   rsp, 4

    movss dword ptr [rsp], xmm0
	call  _exp_for_hyperbolicsf
    fld   dword ptr [rsp]
    fchs
    fstp  dword ptr [rsp]
	call  _exp_for_hyperbolicsf
	fsub
	fld   TWO_32
	fdiv
    fstp  dword ptr [rsp]
    movss xmm0, dword ptr [rsp]

	mov   rsp, rbp
	pop   rbp
	ret
__sinhf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __tanhf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__tanhf proc
	push   rbp
	mov    rbp, rsp
	sub    rsp, 4
	
    movss xmm1, xmm0
	call  __sinhf
    movss dword ptr [rsp], xmm0
    fld   dword ptr [rsp]
    movss xmm0, xmm1
	call  __coshf
    movss dword ptr [rsp], xmm0
    fld   dword ptr [rsp]
	fdiv
    fstp  dword ptr [rsp]
    movss xmm0, dword ptr [rsp]

	mov   rsp, rbp
	pop   rbp
	ret
__tanhf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __ctanhf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__ctanhf proc
	push  rbp
	mov   rbp, rsp
	sub   rsp, 4
	
    movss xmm1, xmm0
	call  __coshf
    movss dword ptr [rsp], xmm0
    fld   dword ptr [rsp]
    movss xmm0, xmm1
	call  __sinhf
    movss dword ptr [rsp], xmm0
    fld   dword ptr [rsp]
	fdiv
    fstp  dword ptr [rsp]
    movss xmm0, dword ptr [rsp]

	mov   rsp, rbp
	pop   rbp
	ret
__ctanhf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __acoshf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__acoshf proc
	push   rbp
	mov    rbp, rsp
    sub    rsp, 4

    movss  dword ptr [rsp], xmm0
	fld    dword ptr [rsp]
	fld    st(0)
	fmul   st(0), st(0)
	fld1
	fsub
	fsqrt
	fadd
	fldln2
	fxch
	fyl2x
    fstp   dword ptr [rsp]
    movss  xmm0, dword ptr [rsp]

	mov    rsp, rbp
	pop    rbp
	ret
__acoshf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __asinhf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__asinhf proc
	push   rbp
	mov    rbp, rsp
    sub    rsp, 4

    movss  dword ptr [rsp], xmm0
	fld    dword ptr [rsp]
	fld  st(0)
	fmul st(0), st(0)
	fld1
	fadd
	fsqrt
	fadd
	fldln2
	fxch
	fyl2x
	fstp   dword ptr [rsp]
    movss  xmm0, dword ptr [rsp]

	mov    rsp, rbp
	pop    rbp
	ret
__asinhf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __atanhf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__atanhf proc
	push   rbp
	mov    rbp, rsp
    sub    rsp, 4

    movss  dword ptr [rsp], xmm0
	fld    dword ptr [rsp]
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
    fstp   dword ptr [rsp]
    movss  xmm0, dword ptr [rsp]

	mov    rsp, rbp
	pop    rbp
	ret
__atanhf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __actanhf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__actanhf proc
	push   rbp
	mov    rbp, rsp
    sub    rsp, 4

    movss  dword ptr [rsp], xmm0
	fld    dword ptr [rsp]
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
    fstp   dword ptr [rsp]
    movss  xmm0, dword ptr [rsp]

	mov    rsp, rbp
	pop    rbp
	ret
__actanhf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __logf(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__logf proc
    push   rbp
	mov    rbp, rsp
    sub    rsp, 4

    movss  dword ptr [rsp], xmm0
	fldln2
	fld    dword ptr [rsp]
	fyl2x
	fstp   dword ptr [rsp]
    movss  xmm0, dword ptr [rsp]

	mov    rsp, rbp
	pop    rbp
	ret
__logf endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __log2f(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__log2f proc
    push   rbp
	mov    rbp, rsp
    sub    rsp, 4

    movss  dword ptr [rsp], xmm0
	fld1
	fld    dword ptr [rsp]
	fyl2x
	fstp   dword ptr [rsp]
    movss  xmm0, dword ptr [rsp]

	mov    rsp, rbp
	pop    rbp
	ret
__log2f endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f32 __cdecl __log10f(f32 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__log10f proc
    push   rbp
	mov    rbp, rsp
    sub    rsp, 4

    movss  dword ptr [rsp], xmm0
	fldlg2
	fld    dword ptr [rsp]
	fyl2x
	fstp   dword ptr [rsp]
    movss  xmm0, dword ptr [rsp]

	mov    rsp, rbp
	pop    rbp
	ret
__log10f endp

endif
end
