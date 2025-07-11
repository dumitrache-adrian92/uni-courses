extern strlen
extern printf


section .rodata
    test_str db "hell, it's about time", 0
    format db "length = %d", 10, 0

section .text
global main

string_length:
    push ebp
    mov ebp, esp

    mov edx, [ebp + 8]
    cmp BYTE [edx], 0

    je end
    inc eax
    inc edx
    push edx
    call string_length
    add esp, 4
end:
    leave
    ret

main:
    push ebp
    mov ebp, esp

    push test_str
    call strlen
    add esp, 4

    push eax
    push format
    call printf
    add esp, 8

    ; TODO a: Implement strlen-like functionality using a RECURSIVE implementation.
    xor eax, eax
    push test_str
    call string_length
    add esp, 4

    push eax
    push format
    call printf
    add esp, 8

    ; Return 0.
    xor eax, eax
    leave
    ret
