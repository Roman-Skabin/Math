;
; Copyright 2019 Roman Skabin
;

include math.inc

.code

if _X64

    _DllMainCRTStartup@20 proc
        mov rax, 1
        ret
    _DllMainCRTStartup@20 endp

    include math_fact.inc
    include math_f64_x64.inc
    include math_f32_x64.inc

else

    _DllMainCRTStartup@12 proc
        mov eax, 1
        ret
    _DllMainCRTStartup@12 endp

    include math_fact.inc
    include math_f64_x86.inc
    include math_f32_x86.inc

endif

end
