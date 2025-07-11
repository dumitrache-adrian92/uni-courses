%include "../include/io.mac"

section .text
    global spiral
    extern printf

; void spiral(int N, char *plain, int key[N][N], char *enc_string);
spiral:
    ;; DO NOT MODIFY
    push ebp
    mov ebp, esp
    pusha

    mov eax, [ebp + 8]  ; N (size of key line)
    mov ebx, [ebp + 12] ; plain (address of first element in string)
    mov ecx, [ebp + 16] ; key (address of first element in matrix)
    mov edx, [ebp + 20] ; enc_string (address of first element in string)
    ;; DO NOT MODIFY
    ;; TODO: Implement spiral encryption
    ;; FREESTYLE STARTS HERE
    push eax
    xor esi, esi
copy: ; loop pentru a copia plain in enc_string
    mov al, [ebx + esi]
    mov BYTE [edx + esi], al
    inc esi
    cmp al, 0
    jne copy

    pop eax

    push ebx

    xor esi, esi
    mov esi, eax
    dec esi
    ; loop care parcurge toate elementele matricei in spirala
    xor edi, edi
printSpiral:
    ; practic parcurgem liniile si coloanele exterioare la matricei si apoi
    ; trecem la al doilea nivel spre interior si tot asa
    ; fiecare loop afiseaza marginea respectiva
    xor ebx, ebx
    mov ebx, edi
    cmp ebx, esi
    jg exitTR
    topRow:
    push esi
    xor esi, esi
    mov esi, edi
    imul esi, eax
    ; mie sa imi faca bil gaetz mai multe registre ca nu mai suport coaie
    add esi, ebx
    imul esi, 4 ; fiindca avem int-uri
    push ebx
    xor ebx, ebx
    mov ebx, DWORD[ecx + esi]
    add BYTE [edx], bl
    inc edx

    pop ebx
    inc ebx
    pop esi
    cmp ebx, esi
    jl topRow
exitTR:

    xor ebx, ebx
    mov ebx, edi
    cmp ebx, esi
    jge exitLC
lastColumn:
    push edi
    xor edi, edi
    mov edi, ebx
    imul edi, eax
    add edi, esi
    imul edi, 4
    push ebx
    xor ebx, ebx
    mov ebx, DWORD[ecx + edi]
    add BYTE [edx], bl
    inc edx

    pop ebx
    pop edi
    inc ebx
    cmp ebx, esi
    jl lastColumn
exitLC:

    xor ebx, ebx
    mov ebx, esi
    cmp ebx, edi
    jle exitBR
bottomRow:
    push edi
    xor edi, edi
    mov edi, esi
    imul edi, eax
    add edi, ebx
    imul edi, 4
    push ebx
    xor ebx, ebx
    mov ebx, DWORD[ecx + edi]
    add BYTE [edx], bl
    inc edx

    pop ebx
    pop edi
    dec ebx
    cmp ebx, edi
    jg bottomRow
exitBR:

    xor ebx, ebx
    mov ebx, esi
    cmp ebx, edi
    jle exitFC
firstColumn:
    push esi
    xor esi, esi
    mov esi, ebx
    imul esi, eax
    add esi, edi
    imul esi, 4
    push ebx
    xor ebx, ebx
    mov ebx, DWORD[ecx + esi]
    add BYTE [edx], bl
    inc edx

    pop ebx
    pop esi
    dec ebx
    cmp ebx, edi
    jg firstColumn
exitFC:

    dec esi
    inc edi
    cmp esi, 0
    jg printSpiral
    pop ebx
    ;; FREESTYLE ENDS HERE
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY
