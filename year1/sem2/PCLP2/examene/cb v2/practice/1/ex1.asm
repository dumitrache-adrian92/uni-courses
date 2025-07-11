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

	xor eax, eax ; < 'K'
	xor ebx, ebx ; >= 'K'
	xor ecx, ecx ; index
	xor edx, edx

count_lower_higher:
	cmp ecx, playlist_len
	je stop_count_lower_higher

	mov dl, [playlist + ecx]

	cmp dl, 75
	jae higher

	inc eax

	inc ecx
	jmp count_lower_higher

higher:
	inc ebx

	inc ecx
	jmp count_lower_higher

stop_count_lower_higher:

	mul bl

	mov [product_answer], ax

	; Instructiune de afisare! NU MODIFICATI!
	a_print:
	PRINTF32 `%d\n\x0`, [product_answer]


    ; TODO b:
	; Pentru fiecare element din playlist, puneti in vectorul answer restul
	; impartirii lui la 41.

	xor ecx, ecx


mod_41:
	cmp ecx, playlist_len
	jge stop_mod41

	xor eax, eax
	mov al, [playlist + ecx]
	mov bl, 41

	div bl

	shr ax, 8

	mov [answer + ecx], al

	inc ecx
	jmp mod_41
stop_mod41:

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
	xor ecx, ecx
	xor esi, esi

invert_nibble:
	cmp ecx, playlist_len
	je stop_invert_nibble

	xor edx, edx
	xor eax, eax
	xor ebx, ebx

	mov eax, ecx
	mov ebx, 3
	div ebx

	cmp edx, 0
	je invert

	xor edx, edx
	xor eax, eax

	mov eax, ecx
	mov ebx, 4
	div ebx

	cmp edx, 0
	je invert

	jmp skip

invert:
	mov al, [playlist + ecx]
	mov bl, al
	shr al, 4
	shl bl, 4

	or al, bl

	mov [answer + esi], al
	inc esi
skip:
	inc ecx
	jmp invert_nibble
stop_invert_nibble:

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
