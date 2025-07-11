%include "printf32.asm"
extern printf

section .bss
	answer resw 20

section .data
    products dw 0x10AD, 0x234D, 0x03AD, 0x7E00, 0x0AFE, 0x00A1, 0x1B32, 0x0, 0x1, 0xA, 0x00CB, 0xFF, 0x1123, 0xFFFF, 0x64, 0x3FBC, 0x128, 0x341, 0x2345, 0x1AFE
    products_len equ 20
    c_answer_len equ 5

section .text
global main

main:
    push ebp
    mov ebp, esp

    ; TODO a: Afisati restul impartirii la 23, pentru fiecare element.
	; Fiecare rest se va salva in vectorul answer (acesta este tot un vector de
	; words).
    ; ATENTIE la registrele folosite. Un singur octet poate NU fi de ajuns
    ; pentru catul impartirii.
    xor esi, esi
    mov ebx, 23
remainder_23:
    xor eax, eax
    xor edx, edx

    mov ax, WORD[products + esi * 2]
    idiv ebx
    mov WORD[answer + esi * 2], dx

    inc esi
    cmp esi, products_len
    jne remainder_23

    ;; INSTRUCTIUNI AFISARE subpunct a). NU MODIFICATI!
a_print:
    xor ecx, ecx
a_print_loop:
	PRINTF32 `%hd \x0`, [answer + 2 * ecx]
	mov WORD [answer + 2 * ecx], 0
	inc ecx
	cmp ecx, products_len
	jb a_print_loop
	PRINTF32 `\n\x0`

    ; TODO b: Afisati produsul dintre numarul de elemente pare si cel al
    ;  elementelor impare. Rezultatul se va pune pe prima pozitie din vectorul
	; answer.

    xor eax, eax ; even
    xor ebx, ebx ; odd
    xor ecx, ecx ; counter

product:
    xor edx, edx
    mov dx, WORD[products + 2 * ecx]
    ;PRINTF32 `%d\n\x0`, edx
    test edx, 1
    jz even
odd:
    inc ebx
    jmp next
even:
    inc eax
    jmp next
next:
    inc ecx
    cmp ecx, products_len
    jne product

    ;PRINTF32 `%hd\n\x0`, ax
    ;PRINTF32 `%hd\n\x0`, bx
    imul eax, ebx
    mov WORD[answer],ax

    ;; INSTRUCTIUNI AFISARE subpunct b). NU MODIFICATI!
b_print:
	PRINTF32 `%hd\n\x0`, [answer]
	mov word [answer], 0

    ; TODO c: Daca elementul se afla pe o pozitie multiplu de 3 sau de 5,
    ; verificati daca cel mai semnificativ octet este par. Daca este par
    ; faceti-i flip (ii inversati toti bitii). Puneti rezultatul fiecarui flip
	; in vectorul answer.

    xor esi, esi
    xor edi, edi
multiplu:
    xor edx, edx
    xor eax, eax
    mov eax, esi
    mov ebx, 3
    idiv ebx
    cmp edx, 0
    je check_parity

    xor edx, edx
    xor eax, eax
    mov eax, esi
    mov ebx, 5
    idiv ebx
    cmp edx, 0
    je check_parity

no_flip:
    jmp end
check_parity:
    xor eax, eax
    mov ax, WORD[products + 2 * esi]
    shr ax, 8
    test ax, 1
    jnz end 
    not al
    shl ax, 8
    xor ebx, ebx
    mov bx, WORD[products + 2 * esi]
    shl bx, 8
    shr bx, 8
    or eax, ebx
    mov WORD[answer + 2 * edi], ax
    inc edi

end:
    inc esi
    cmp esi, products_len
    jne multiplu
    ;; INSTRUCTIUNI AFISARE subpunct c). NU MODIFICATI!
c_print:
    xor ecx, ecx
c_print_loop:
	PRINTF32 `%hx \x0`, [answer + 2 * ecx]
	inc ecx
	cmp ecx, c_answer_len
	jb c_print_loop
	PRINTF32 `\n\x0`


    ; Return 0.
    xor eax, eax
    leave
    ret
