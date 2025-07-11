%include "utils/printf32.asm"

section .data
    num dd 3453235129

section .text
global main
extern printf

main:
    push ebp
    mov ebp, esp

    ;TODO a: print least significant 2 bits of the second most significant byte of num
    mov eax, [num]
    shr eax, 16
    mov ecx, eax
    shr ecx, 1

    and ecx, 1
    PRINTF32 `%d\x0`, ecx
    and eax, 1
    PRINTF32 `%d\n\x0`, eax

    ;TODO b: print number of bits set on odd positions
    xor ecx, ecx
    xor eax, eax
    mov eax, [num]
    ; shr eax, 1
odd_positions:
    test eax, 1
    jz bit_off
    inc ecx
bit_off:
    shr eax, 2
    cmp eax, 0
    jne odd_positions
    PRINTF32 `%d\n\x0`, ecx

    ;TODO c: print number of groups of 3 consecutive bits set
    xor esi, esi
    xor ecx, ecx
    xor eax, eax
    mov eax, [num]
bit_traversal:
    test eax, 1
    jz reset_counter
    inc ecx
    jmp no_reset
reset_counter:
    xor ecx, ecx
no_reset:
    cmp ecx, 3
    jl short_group
    inc esi
short_group:
    shr eax, 1
    cmp eax, 0
    jne bit_traversal
    PRINTF32 `%d\n\x0`, esi

    xor eax, eax
    leave
    ret
