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

ROUND_DOWN    equ 1
ROUND_UP      equ 2
ROUND_NEAREST equ 3
