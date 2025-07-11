%include "utils/printf32.asm"

extern printf
extern puts

section .data
    num dd 55555123
;;  TODO d: declare byte_array so that PRINT_HEX shows babadac
    byte_array db 172, 173, 171, 11
    test_string db "ABCDEFGHIJKLMNOPQRST", 0
    input_array db 1, 2, 3, 4, 5, 6
    input_len dd 6
    output_array dw 0, 0, 0, 0, 0, 0

section .text
global main

; TODO b: implement array_reverse
array_reverse:
    push ebp
    mov ebp, esp

    mov eax, [ebp + 8]   ; sirul de caractere
    mov ebx, [ebp + 12]  ; numarul de caractere

    mov ecx, ebx
    shr ecx, 1
    dec ecx

    mov esi, 0
    mov edi, ebx
    dec edi

    push ebx
rev:
    mov dl, BYTE [eax + esi]    ;aux
    mov bl, BYTE [eax + edi]
    mov BYTE [eax + esi], bl
    mov BYTE [eax + edi], dl

    dec edi
    inc esi
    cmp esi, ecx
    jle rev

    pop ebx

    leave
    ret


; TODO c: implement pow_arraypowArray
pow_array:
    push ebp
    mov ebp, esp

    mov eax, [ebp + 8]  ; array input, BYTES
    mov ebx, [ebp + 12] ; length array
    mov edi, [ebp + 16] ; array output, WORDS

    mov esi, 0
power:
    xor edx, edx
    xor ecx, ecx

    mov dl, [eax + esi]
    mov cl, dl
    imul cx, dx

    mov WORD[edi + 2 * esi], cx

    inc esi
    cmp esi, ebx
    jl power

    leave
    ret

main:
    push ebp
    mov ebp, esp

    ;TODO a: allocate on array of 20 byte elements and initializate it incrementally starting from 'A'
    sub esp, 20

    mov eax, esp
    mov ebx, 'A'
    mov ecx, 0

init_array:
    mov BYTE[eax], bl

    inc eax
    inc ebx
    inc ecx
    cmp ecx, 20
    jl init_array

    mov eax, esp
    mov ecx, 0
print_letters:
    PRINTF32 `%c\x0`, BYTE[eax]

    inc eax
    inc ecx
    cmp ecx, 20
    jl print_letters
    PRINTF32 `\n\x0`

    ;TODO b: call array_reverse and print reversed array
    push 20
    push test_string
    call array_reverse
    add esp, 8

    push test_string
    call puts
    add esp, 4

    ;TODO c: call pow_array and print the result array
    push output_array
    push DWORD [input_len]
    push input_array
    call pow_array
    add esp, 12

    mov ecx, 0
print_array:
    PRINTF32 `%hd \x0`, WORD[output_array + 2 * ecx]

    inc ecx
    cmp ecx, [input_len]
    jl print_array

    PRINTF32 `\n\x0`

	;;  TODO d: this print of an uint32_t should print babadac
	PRINTF32 `%x\n\x0`, DWORD [byte_array]

    xor eax, eax
    leave
    ret
