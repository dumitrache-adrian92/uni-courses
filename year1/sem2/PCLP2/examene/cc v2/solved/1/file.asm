%include "printf32.asm"

extern printf

section .bss
    results resw 9

section .data
    lap_times dw 0x37E, 0x321, 0x3FD, 0x3A5, 0x357, 0x385, 0x39B, 0x36F, 0x3E5, 0x31A
    lap_times_len equ $ - lap_times
    c_results_len equ 9
    d_results_len equ 8

section .text
global main

main:
    push ebp
    mov ebp, esp

    ; TODO a: Aflați timpul minim și timpul maxim din vectorul lap_times.
    ; Salvați timpul minim pe prima poziție din vectorul results, iar timpul
    ; maxim pe cea de-a doua poziție.

    xor eax, eax ; max
    xor ebx, ebx ; min
    xor esi, esi ; contor
    mov ax, WORD[lap_times]
    mov bx, WORD[lap_times]
    add esi, 2
min_max:
    cmp ax, WORD[lap_times + esi]
    jge not_min
    xor eax, eax
    mov ax, WORD[lap_times + esi]
not_min:
    cmp bx, WORD[lap_times + esi]
    jle next_lap
    xor ebx, ebx
    mov bx, WORD[lap_times + esi]
next_lap:
    add esi, 2
    cmp esi, lap_times_len
    jne min_max

    mov WORD[results], bx
    mov WORD[results + 2], ax


    ; Afișare rezultat pentru subpunctul a). Nu modificați!
    PRINTF32 `%hd %hd\n\x0`, word [results], word [results + 2]


    ; TODO b: Aflați câtul și restul împărțirii sumei timpilor din prima
    ; jumătate de antrenament la suma timpilor din cea de-a doua jumătate de
    ; antrenament.
    ; Salvați câtul împărțirii pe prima poziție din vectorul results, iar restul
    ; împărțirii pe cea de-a doua poziție.
    mov ecx, lap_times_len
    shr ecx, 1 ; lap_times_len/2

    xor eax, eax ;prima jum

    xor esi, esi
sum_first_half:
    add ax, WORD[lap_times + esi]

    add esi, 2
    cmp esi, ecx
    jne sum_first_half
    
    xor ebx, ebx; jum 2

sum_second_half:
    add bx, WORD[lap_times + esi]

    add esi, 2
    cmp esi, lap_times_len
    jne sum_second_half

    xor edx, edx
    idiv bx
    
    mov word[results], ax
    mov word[results + 2], dx

    ; Afișare rezultat pentru subpunctul b). Nu modificați!
    PRINTF32 `%hd %hd\n\x0`, word [results], word [results + 2]


    ; TODO c: Aflați diferențele dintre timpi, doi câte doi.
    ; Plasați rezultatele în vectorul results.

    xor ecx, ecx
    mov ecx, lap_times_len
    sub ecx, 2

    xor esi, esi
dif_two:
    xor eax, eax
    mov ax, WORD[lap_times + esi]
    sub ax, WORD[lap_times + esi + 2]
    mov WORD[results + esi], ax
    add esi, 2
    cmp esi, ecx
    jne dif_two


    ; Afișare rezultat pentru subpunctul c). Nu modificați!
    mov edx, results
    mov ecx, c_results_len

print_c_loop:
    PRINTF32 `%hd \x0`, word [edx]
    add edx, 2
    loop print_c_loop

    PRINTF32 `\n\x0`


    ; TODO d: Aflați în binar numărul de timpi de antrenament care au al treilea
    ; cel mai puțin semnificativ bit setat.
    ; Numărul de timpi de antrenament care au al treilea cel mai puțin
    ; semnificativ bit setat încape garantat într-un octet.
    ; Testați fiecare bit din acest număr și salvați pe poziții succesive în
    ; vectorul "results" valoarea 0 dacă bitul testat este 0, sau valoarea 1
    ; dacă bitul testat este 1.
    ; Cel mai semnificativ bit se va afla pe prima poziție din vectorul results,
    ; iar ce cel mai puțin semnificativ bit se va afla pe cea de-a opta poziție
    ; din vector.

    xor eax, eax; nr

    xor esi, esi 
find_number:
    xor ebx, ebx
    mov bx, WORD[lap_times + esi]
    shr bx, 2
    test ebx, 1
    jz not_set
    inc eax
not_set:
    add esi, 2
    cmp esi, lap_times_len
    jne find_number

    xor ebx, ebx
    mov ebx, 1
    shl bl, 7 ; bitmask

    xor esi, esi

da_result:
    test al, bl
    jz add_zero
    mov WORD[results + esi], 1
    jmp next

add_zero:
    mov WORD[results + esi], 0
    
next:
    add esi, 2
    shr bl, 1
    cmp bl, 0
    jne da_result

    ; Afișare rezultat pentru subpunctul d). Nu modificați!
    mov edx, results
    mov ecx, d_results_len

print_d_loop:
    PRINTF32 `%hd\x0`, word [edx]
    add edx, 2
    loop print_d_loop

    PRINTF32 `\n\x0`

    ; Return 0.
    xor eax, eax
    leave
    ret
