;
; Copyright 2019 Roman Skabin
;

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

else

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
