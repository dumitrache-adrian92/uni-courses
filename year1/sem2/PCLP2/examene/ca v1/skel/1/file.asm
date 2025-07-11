%include "printf32.asm"
extern printf

section .data

M dw 1000
N dw 700

arr1 dw 1000, 1000, 30, 40, 50, 60, 70, 80, 90, 100
arr2 dw 90, 100, 90, 50, 40, 30, 20, 10, 60, 100
len equ 10

section .bss

; TODO c: Alocati memorie pentru vectorul `res` cu elemente de tip double word si dimensiunea egala cu `len`

section .text

global main

main:
    push ebp
    mov ebp, esp

    ; TODO a: Calculati si afisati produsul numerelor reprezentate pe 2 octeti (word) M si N.
    ; Sugestie: Pentru inmultire puteti folosi instructiunea `mul` care:
    ;   - primeste primul operand in registrul AX
    ;   - primeste al doilea operand intr-un registru pe 16 biti / memorie de 16 biti
    ;   - intoarce rezultatul in DX:AX
    ;   - pe scurt, DX : AX = AX * r/m16.




    ; TODO b: Calculati si afisati produsul scalar al vectorilor arr1 si arr2
    ;   - P = arr1[0] * arr2[0] + arr1[1] * arr2[1] + ... arr1[i] * arr2[i] + ...
    ;   - este garantat ca P nu depaseste dimensiunea unui double word (4 octeti)




    ; TODO c: Completati vectorul `res` cu elemente de tip double word de dimensiune `len`  astfel incat
    ; fiecare element sa fie egal cu produsul elementelor corespunzatoare din vectorii `arr1` si `arr2`.
    ; - e.g: res[i] = arr1[i] * arr2[i]




    ; TODO d: Afisati vectorul `res` cu elemente de tip double word de dimensiune `len` calculat la punctul c)




    ; Return 0.
    xor eax, eax
    leave
    ret
