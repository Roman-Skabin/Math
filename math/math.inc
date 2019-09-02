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
