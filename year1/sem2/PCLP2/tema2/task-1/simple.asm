%include "../include/io.mac"

section .text
    global simple
    extern printf

simple:
    ;; DO NOT MODIFY
    push    ebp
    mov     ebp, esp
    pusha

    mov     ecx, [ebp + 8]  ; len
    mov     esi, [ebp + 12] ; plain
    mov     edi, [ebp + 16] ; enc_string
    mov     edx, [ebp + 20] ; step

    ;; DO NOT MODIFY

    ;; Your code starts here
cipher:
    xor eax, eax
    mov al, [esi] ; luam prima litera de la adresa esi
    cmp al, 0
    jz skip ; daca e caracter null nu ii mai schimbam valoarea
    add eax, edx ; crestem caracterul cu step'
    ; daca valoarea caracterului a trecut de Z in ASCII, scadem 26
    ; ca sa ne rotim prin alfabet
    cmp eax, 90
    jle skip
    sub eax, 26
skip:
    mov [edi], al ; mutam caracterul obtinut in enc_string
    inc esi ; trecem mai departe in cei 2 vectori
    inc edi
    cmp al, 0 ; daca cifra verificata a fost egala cu \0, ne oprim
    jnz cipher
    ;; Your code ends here

    ;; DO NOT MODIFY

    popa
    leave
    ret

    ;; DO NOT MODIFY
