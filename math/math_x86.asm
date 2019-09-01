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

if _X86

.code

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; s32 __vectorcall __ceil(f64 value);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__ceil@@8 proc
	roundsd  xmm0, xmm0, ROUND_UP
	cvtsd2si eax , xmm0
	ret
__ceil@@8 endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; s32 __vectorcall __floor(f64 value);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__floor@@8 proc
	roundsd  xmm0, xmm0, ROUND_DOWN
	cvtsd2si eax , xmm0
	ret
__floor@@8 endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; s32 __vectorcall __round(f64 value);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__round@@8 proc
	roundsd  xmm0, xmm0, ROUND_NEAREST
	cvtsd2si eax , xmm0
	ret
__round@@8 endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __exp(f64 power);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___exp proc
    fld     qword ptr [esp+4]
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
___exp endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __pow(f64 base, f64 power);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___pow proc
	push ebp
	mov  ebp, esp

	fld    qword ptr [ebp+16]
	fld    qword ptr [ebp+8]
	fyl2x
	fld1
	fld    st(1)
	fprem
	f2xm1
	fadd
	fscale
	fxch
	fstp   st(0)

	mov esp, ebp
	pop ebp
	ret
___pow endp

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

___root proc
	push ebp
	mov  ebp, esp
	
	fld qword ptr [ebp+16]
	fld1
	fdivr
	fld qword ptr [ebp+8]
	fyl2x
	fld1
	fld    st(1)
	fprem
	f2xm1
	fadd
	fscale
	fxch
	fstp   st(0)

	mov  esp, ebp
	pop  ebp
	ret
___root endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __cos(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___cos proc
	fld  qword ptr [esp+4]
	fcos
	ret
___cos endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __sin(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___sin proc
	fld  qword ptr [esp+4]
	fsin
	ret
___sin endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __tan(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___tan proc
	fld   qword ptr [esp+4]
	fptan
	fstp  st(0)
	ret
___tan endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __ctan(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___ctan proc
	fld   qword ptr [esp+4]
	fptan
	fdivr
	ret
___ctan endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __acos(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___acos proc
	fld    qword ptr [esp+4]
	fld    st(0)
	fmul   st(0), st(1)
	fld1
	fsubrp st(1), st(0)
	fsqrt
	fxch
	fpatan
	ret
___acos endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __asin(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___asin proc
	fld    qword ptr [esp+4]
	fld    st(0)
	fmul   st(0), st(1)
	fld1
	fsubrp st(1), st(0)
	fsqrt
	fpatan
	ret
___asin endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __atan(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___atan proc
	fld    qword ptr [esp+4]
	fld1
	fpatan
	ret
___atan endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __actan(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___actan proc
	fld    qword ptr [esp+4]
	fld1
	fpatan
	fchs
	fldpi
	fld1
	fadd  st(0), st(0)
	fdiv
	fadd
	ret
___actan endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __cosh(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___cosh proc
	push   ebp
	mov    ebp, esp

	sub    esp, 8
	vmovsd xmm0, qword ptr [ebp+8]
	vmovsd qword ptr [esp], xmm0
	call   ___exp
	fld    qword ptr [esp]
	fchs
	fstp   qword ptr [esp]
	call   ___exp
	add    esp, 8
	fadd
	fld1
	fadd  st(0), st(0)
	fdiv

	mov    esp, ebp
	pop    ebp
	ret
___cosh endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __sinh(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___sinh proc
	push   ebp
	mov    ebp, esp

	sub    esp, 8
	vmovsd xmm0, qword ptr [ebp+8]
	vmovsd qword ptr [esp], xmm0
	call   ___exp
	fld    qword ptr [esp]
	fchs
	fstp   qword ptr [esp]
	call   ___exp
	add    esp, 8
	fsub
	fld1
	fadd   st(0), st(0)
	fdiv

	mov    esp, ebp
	pop    ebp
	ret
___sinh endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __tanh(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___tanh proc
	push   ebp
	mov    ebp, esp
	
	sub    esp, 8
	vmovsd xmm0, qword ptr [ebp+8]
	vmovsd qword ptr [esp], xmm0
	call   ___sinh
	call   ___cosh
	add    esp, 8
	fdiv

	mov    esp, ebp
	pop    ebp
	ret
___tanh endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __ctanh(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___ctanh proc
	push   ebp
	mov    ebp, esp
	
	sub    esp, 8
	vmovsd xmm0, qword ptr [ebp+8]
	vmovsd qword ptr [esp], xmm0
	call   ___cosh
	call   ___sinh
	add    esp, 8
	fdiv

	mov    esp, ebp
	pop    ebp
	ret
___ctanh endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __acosh(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___acosh proc
	push ebp
	mov  ebp, esp

	fld  qword ptr [ebp+8]
	fld  st(0)
	fmul st(0), st(0)
	fld1
	fsub
	fsqrt
	fadd
	fldln2
	fxch
	fyl2x

	mov  esp, ebp
	pop  ebp
	ret
___acosh endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __asinh(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___asinh proc
	push ebp
	mov  ebp, esp

	fld  qword ptr [ebp+8]
	fld  st(0)
	fmul st(0), st(0)
	fld1
	fadd
	fsqrt
	fadd
	fldln2
	fxch
	fyl2x

	mov  esp, ebp
	pop  ebp
	ret
___asinh endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __atanh(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___atanh proc
	push   ebp
	mov    ebp, esp	

	fld    qword ptr [ebp+8]
	fld    st(0)
	fld1
	fadd   st(1), st(0)
	fsubrp st(2), st(0)
	fdivr
	fldln2
	fxch
	fyl2x
	fld1
	fadd   st(0), st(0)
	fdiv

	mov    esp, ebp
	pop    ebp
	ret
___atanh endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __actanh(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___actanh proc
	push   ebp
	mov    ebp, esp	

	fld    qword ptr [ebp+8]
	fld    st(0)
	fld1
	fadd   st(1), st(0)
	fsubp  st(2), st(0)
	fdivr
	fldln2
	fxch
	fyl2x
	fld1
	fadd   st(0), st(0)
	fdiv

	mov    esp, ebp
	pop    ebp
	ret
___actanh endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __log(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___log proc
	fldln2
	fld    qword ptr [esp+4]
	fyl2x
	ret
___log endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __log2(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___log2 proc
	fld1
	fld   qword ptr [esp+4]
	fyl2x
	ret
___log2 endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; f64 __cdecl __log10(f64 x);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

___log10 proc
	fldlg2
	fld    qword ptr [esp+4]
	fyl2x
	ret
___log10 endp

endif
end
