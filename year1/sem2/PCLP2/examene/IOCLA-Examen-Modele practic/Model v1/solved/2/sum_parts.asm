%include "utils/printf32.asm"

section .bss
pos1: resd 1
pos2: resd 1

section .data
    uint_format    db "%zu", 0
    uint_format_newline    db "%zu", 10, 0
    pos1_str    db "Introduceti prima pozitie: ", 0
    pos2_str   db "Introduceti a doua pozitie: ", 0
    sum_str db "Suma este: %zu", 10, 0
    sum_interval_str db "Suma de la pozitia %zu la pozitia %zu este %zu", 10, 0
    arr     dd 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400

section .text
global main
extern scanf
extern printf

sum:
    push ebp
    mov ebp, esp

    ; TODO b: Implement sum() to compute sum for array.
    push ebx
    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx
    mov ebx, DWORD[ebp + 8]
    mov ecx, DWORD[ebp + 12]
    
    xor edx, edx
sum_of_array:
    add eax, DWORD[ebx + 4 * edx]
    inc edx
    cmp edx, ecx
    jne sum_of_array

    pop ebx

    leave
    ret


sum_interval:
    push ebp
    mov ebp, esp
    push ebx
    ; TODO b: Implement sum_interval() to compute sum for array between two positions.
    xor eax, eax
    mov ebx, [ebp + 8]
    mov ecx, [ebp + 12]
    mov edx, [ebp + 16]
interval_sum_of_array:
    add eax, DWORD[ebx + 4 * ecx]
    inc ecx
    cmp edx, ecx
    jne interval_sum_of_array

    pop ebx
    leave
    ret


main:
    push ebp
    mov ebp, esp

    push dword 14
    push arr
    call sum
    add esp, 8

    push eax
    push sum_str
    call printf
    add esp, 8

    ; TODO b: Call sum_interval() and print result.
    xor esi, esi
    xor edi, edi
    mov esi, 4
    mov edi, 1
    push esi
    push edi
    push arr
    call sum_interval
    add esp, 12
    
    push eax
    push esi
    push edi
    push sum_interval_str
    call printf
    add esp, 16

    ; TODO c: Use scanf() to read positions from standard input.
    push pos1_str
    call printf
    add esp, 4

    push pos1
    push uint_format
    call scanf
    add esp, 8

    push pos2_str
    call printf
    add esp, 4

    push pos2
    push uint_format
    call scanf
    add esp, 8

    push DWORD[pos2]
    push DWORD[pos1]
    push arr
    call sum_interval
    add esp, 12

    push eax
    push DWORD[pos2]
    push DWORD[pos1]
    push sum_interval_str
    call printf
    add esp, 16

    ; Return 0.
    xor eax, eax
    leave
    ret
