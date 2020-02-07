;
; Copyright 2019 Roman Skabin
;

ifdef rax
    _X64 equ 1
    _X86 equ 0
else
    _X64 equ 0
    _X86 equ 1
endif

if _X86
	.686
    .387
    .xmm
    .model flat
endif

MM_ROUND_NEAREST     equ 0 ; to nearest even
MM_ROUND_DOWN        equ 1
MM_ROUND_UP          equ 2
MM_ROUND_TOWARD_ZERO equ 3
MM_ROUND_DEFAULT     equ 4

MM_ROUND_NEAREST_NO_EXC     equ 8 ; to nearest even
MM_ROUND_DOWN_NO_EXC        equ 9
MM_ROUND_UP_NO_EXC          equ 10
MM_ROUND_TOWARD_ZERO_NO_EXC equ 11
MM_ROUND_DEFAULT_NO_EXC     equ 12

.data
    HALF_32 real4 0.5
    HALF_64 real8 0.5

    TWO_32  real4 2.0
    TWO_64  real8 2.0

    E_64    real8 2.718281828459045
    PI_2_64 real8 1.570796326794896

    E_32    real4 2.7182818
    PI_2_32 real4 1.5707963

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
