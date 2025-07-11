%include "../include/io.mac"

section .text
    global is_square
    extern printf

is_square:
    ;; DO NOT MODIFY
    push ebp
    mov ebp, esp
    pusha

    mov ebx, [ebp + 8]      ; dist
    mov eax, [ebp + 12]     ; nr
    mov ecx, [ebp + 16]     ; sq
    ;; DO NOT MODIFY

    ;; Your code starts here

    ; initializeaza tot vectorul sq cu 0
    xor edx, edx
initSQ:
    mov DWORD [ecx + 4 * edx], 0
    inc edx
    cmp edx, eax
    jne initSQ

    xor edx, edx ; indice pentru parcurgerea vectorului dist
distLoop:
    xor esi, esi ; indice pentru parcurgerea numerelor naturale
    xor edi, edi ; unde o sa calculam patratului lui esi
    ; parcurgem numerele naturale pana cand patratul unuia este mai mare decat
    ; decat numarul curent, caz in care nu este patrat perfect, sau patratul
    ; este egal cu numarul, caz in care este patrat perfect
findSQRT:
    mov edi, esi
    imul edi, esi
    cmp edi, DWORD [ebx + edx * 4]
    jne skip
    mov DWORD [ecx + edx * 4], 1 ; notam patratul perfect cu 1
    jmp exitFindSQRT
skip:
    inc esi
    cmp edi, DWORD [ebx + edx * 4]
    jg exitFindSQRT
    cmp edi, DWORD [ebx + edx * 4]
    jl findSQRT

exitFindSQRT:
    inc edx
    cmp edx, eax
    jne distLoop
    ;; Your code ends here

    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY
