%include "utils/printf32.asm"

extern printf

section .data
    test_str db "ce faci coaie", 0
    num dd 55555123
    arr_b db 1, 2, 3, 4, 5
    arr_w dw 0, 0, 0, 0, 0, 0
;;  TODO d: declare byte_array so that PRINT_HEX shows babadac
    byte_array db 172, 173, 171, 11

section .text
global main
extern puts

; TODO b: implement array_reverse
array_reverse:
    push ebp
    mov ebp, esp
    push ebx

    mov ecx, DWORD[ebp + 12]
    mov eax, ecx
    xor edx, edx
    mov ebx, 2
    idiv DWORD ebx

    mov ebx, DWORD[ebp + 8]
    xor edx, edx
rev_loop:
    xor esi, esi
    mov esi, ecx
    dec esi
    sub esi, edx
    push ecx
    push eax
    mov cl, BYTE[ebx + esi]
    mov al, BYTE[ebx + edx]
    mov BYTE[ebx + esi], al
    mov BYTE[ebx + edx], cl
    pop eax
    pop ecx
    inc edx
    cmp edx, eax
    jne rev_loop

    pop ebx
    leave
    ret

; TODO c: implement pow_arraypowArray
pow_array:
    push ebp
    mov ebp, esp
    push ebx

    mov eax, DWORD[ebp + 8]
    mov ebx, DWORD[ebp + 12]
    mov ecx, DWORD[ebp + 16]

    xor esi, esi
e_putere:
    xor edx, edx
    mov dl, BYTE [eax + esi]
    push ecx
    mov cx, dx
    imul cx, dx
    mov WORD[ebx + 2 * esi], cx
    pop ecx
    inc esi
    cmp esi, ecx
    jne e_putere

    pop ebx
    leave
    ret

main:
    push ebp
    mov ebp, esp

    ;TODO a: allocate on array of 20 byte elements and initializate it incrementally starting from 'A'
    sub esp, 20
    mov BYTE[esp], 65
    xor esi, esi
    xor eax, eax
    inc esi
init_array:
    mov al, [esp + esi - 1]
    mov [esp + esi], al
    inc BYTE[esp + esi]

    inc esi
    cmp esi, 20
    jne init_array

    mov eax, esp

    mov ecx, 0
p_array:
    PRINTF32 `%c\x0`, BYTE [eax + ecx]
    inc ecx
    cmp ecx, 19
    jle p_array

    PRINTF32 `\n\x0`

    ;TODO b: call array_reverse and print reversed array
    push 13
    push test_str
    call array_reverse
    add esp, 8

    PRINTF32 `%s\n\x0`, test_str
    ;TODO c: call pow_array and print the result array
    mov ecx, 5
    push ecx
    push arr_w
    push arr_b
    call pow_array
    add esp, 12

    xor eax, eax
    mov eax, arr_w
    mov ecx, 5
    xor esi, esi
print_array:
    PRINTF32 `%hd\n\x0`, WORD[eax + 2 * esi]
    inc esi
    cmp esi, ecx
    jne print_array

	;;  TODO d: this print of an uint32_t should print babadac
	PRINT_HEX [byte_array]

    xor eax, eax
    leave
    ret
