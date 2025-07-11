%include "printf32.asm"
extern printf

section .bss
	product_answer resw 1
	answer resb 24

section .data
	playlist db 0x42, 0x75, 0x76, 0x45, 0x25, 0x79, 0x54, 0x62, 0x94, 0x35, 0x6D, 0x6E, 0x45, 0x4D, 0x7A, 0x14, 0x25, 0x57, 0x94, 0x4C, 0x55, 0x42, 0x78, 0x4B
	playlist_len equ 24

	answer_len equ 12

section .text
global main

main:
    push ebp
    mov ebp, esp


    ; TODO a:
	; Faceti produsul dintre numarul de caractere din vector mai mici decat 'K'
	; si cel al caracterelor mai mari sau egale decat 'K'.
	; Puneti in product_answer rezultatul. (ATENTIE! product_answer asteapta
	; un word (short).
	xor eax, eax ; < K
	xor ebx, ebx ; >= K
	xor ecx, ecx
	xor edx, edx

count_K:
	mov dl, BYTE[playlist + ecx]
	cmp edx, 75
	jl lower

	inc ebx
	jmp next

lower:
	inc eax
	jmp next

next:
	inc ecx
	cmp ecx, playlist_len
	jne count_K

	mul bx
	mov WORD[product_answer], ax

	; Instructiune de afisare! NU MODIFICATI!
	a_print:
	PRINTF32 `%d\n\x0`, [product_answer]


    ; TODO b:
	; Pentru fiecare element din playlist, puneti in vectorul answer restul
	; impartirii lui la 41.

	xor eax, eax
	xor ebx, ebx
	xor ecx, ecx
	xor edx, edx
	mov bl, 41

remainder:
	mov al, BYTE[playlist + ecx]
	idiv ebx
	mov BYTE[answer + ecx], dl
	xor eax, eax
	xor edx, edx
	inc ecx
	cmp ecx, playlist_len
	jne remainder

	; Instructiune de afisare! NU MODIFICATI!
b_print:
	xor ecx, ecx
b_print_loop:
	PRINTF32 `%hhd \x0`, [answer + ecx]
	inc ecx
	cmp ecx, playlist_len
	jb b_print_loop
	PRINTF32 `\n\x0`


    ; TODO c:
	; Pentru elementele de pe indici multiplii de 3 sau de 4, inversati
	; nibbles. Fiecare rezultat va fi pus in vectorul answer.

	xor eax, eax
	xor ebx, ebx
	xor ecx, ecx ; contor playlist
	xor edx, edx
	xor esi, esi ; contor answer
	xor edi, edi

fizzbuzz_aiurea:
	mov eax, ecx
	mov edi, 3
	idiv edi
	cmp edx, 0
	je add_answer

	xor eax, eax
	xor edx, edx
	xor edi, edi

	mov eax, ecx
	mov edi, 4
	idiv edi
	cmp edx, 0
	je add_answer

	jmp not_answer

add_answer:
	mov al, BYTE[playlist + ecx]
	mov bl, al
	shr bl, 4
	shl al, 4
	or al, bl
	PRINTF32 `%hhd\n\x0`, eax
	mov BYTE[answer + esi], al
	inc esi
	xor ebx, ebx

not_answer:

	xor eax, eax
	xor edx, edx
	inc ecx
	cmp ecx, playlist_len
	jne fizzbuzz_aiurea


	; Instructiune de afisare! NU MODIFICATI!
c_print:
	xor ecx, ecx

c_print_loop:
	PRINTF32 `%c\x0`, [answer + ecx]
	inc ecx
	cmp ecx, answer_len
	jb c_print_loop
	PRINTF32 `\n\x0`

    ; Return 0.
    xor eax, eax
    leave
    ret
