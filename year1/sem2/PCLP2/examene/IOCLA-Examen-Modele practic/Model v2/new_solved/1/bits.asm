%include "utils/printf32.asm"

extern printf

section .data
    num dd 3453235129

section .text
global main

main:
    push ebp
    mov ebp, esp

    ;TODO a: print least significant 2 bits of the second most significant byte of num
    mov eax, [num]

    ; 00000000 00000000 00000000 00000001
    mov ebx, 1

    ; 00000000 00000001 00000000 00000000
    shl ebx, 17

    test ebx, eax
    jz print_zero

    PRINTF32 `%d\x0`, 1
    jmp end_first

print_zero:
    PRINTF32 `%d\x0`, 0

end_first:

    shr ebx, 1

    test ebx, eax
    jz print_zero_2

    PRINTF32 `%d\x0`, 1
    jmp end_snd

print_zero_2:
    PRINTF32 `%d\x0`, 0

end_snd:
    PRINTF32 `\n\x0`

    ;TODO b: print number of bits set on odd positions
    xor eax, eax
    xor ebx, ebx

    mov eax, [num]
    mov ebx, 1
    mov ecx, 0

count_1s:
    test eax, ebx

    jz skip
    inc ecx

skip:
    shl ebx, 2
    cmp ebx, 0
    jnz count_1s

    PRINTF32 `%d\n\x0`, ecx

    ;TODO c: print number of groups of 3 consecutive bits set
    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx

    mov eax, [num]
    mov ebx, 1
    mov ecx, 0 ; group count
    mov edx, 0 ; consecutive 1s count

count_groups:
    test eax, ebx

    jz reset_counter

incr_count:
    inc edx
    cmp edx, 3
    jl go_next
    inc ecx
    jmp go_next

reset_counter:
    mov edx, 0

go_next:
    shl ebx, 1
    cmp ebx, 0
    jnz count_groups

    PRINTF32 `%d\n\x0`, ecx

    xor eax, eax
    leave
    ret
