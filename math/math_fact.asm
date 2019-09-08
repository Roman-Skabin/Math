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

.data
	FACT_TABLE qword 1                   ; __fact(0) 
			   qword 1                   ; __fact(1) 
			   qword 2                   ; __fact(2) 
			   qword 6                   ; __fact(3) 
			   qword 24                  ; __fact(4) 
			   qword 120                 ; __fact(5) 
			   qword 720                 ; __fact(6) 
			   qword 5040                ; __fact(7) 
			   qword 40320               ; __fact(8) 
			   qword 362880              ; __fact(9) 
			   qword 3628800             ; __fact(10) 
			   qword 39916800            ; __fact(11) 
			   qword 479001600           ; __fact(12) 
			   qword 6227020800          ; __fact(13) 
			   qword 87178291200         ; __fact(14) 
			   qword 1307674368000       ; __fact(15) 
			   qword 20922789888000      ; __fact(16)
			   qword 355687428096000     ; __fact(17)
			   qword 6402373705728000    ; __fact(18)
			   qword 121645100408832000  ; __fact(19)
			   qword 2432902008176640000 ; __fact(20)

.code

if _X86

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; u64 __fastcall __fact(u32 value);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

@__fact@4 proc
		cmp   ecx, 20
		jg    failed
		lea   eax, FACT_TABLE
		movq  mm0, qword ptr [eax + 8*ecx]
		movd  eax, mm0
		psrlq mm0, 32
		movd  edx, mm0
		ret
failed: xor   edx, edx
		xor   eax, eax
		ret
@__fact@4 endp

elseif _X64

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; u64 __fastcall __fact(u32 value);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

__fact proc
		cmp rcx, 20
		jg  failed
		lea rax, FACT_TABLE
		mov rax, qword ptr [rax + 8*rcx]
		ret
failed: xor rax, rax
		ret
__fact endp

endif

end
