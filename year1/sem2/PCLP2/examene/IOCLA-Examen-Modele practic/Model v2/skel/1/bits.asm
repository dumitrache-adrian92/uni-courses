%include "utils/printf32.asm"

section .data
    num dd 55555123

section .text
global main

main:
    push ebp
    mov ebp, esp

    ;TODO a: print least significant 2 bits of the second most significant byte of num

    ;TODO b: print number of bits set on odd positions

    ;TODO c: print number of groups of 3 consecutive bits set

    xor eax, eax
    leave
    ret
