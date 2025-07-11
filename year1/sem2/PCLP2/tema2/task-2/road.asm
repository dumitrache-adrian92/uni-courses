%include "../include/io.mac"

struc point
    .x: resw 1
    .y: resw 1
endstruc

section .text
    global road
    extern printf
    extern points_distance

road:
    ;; DO NOT MODIFY
    push ebp
    mov ebp, esp
    pusha

    mov eax, [ebp + 8]      ; points
    mov ecx, [ebp + 12]     ; len
    mov ebx, [ebp + 16]     ; distances
    ;; DO NOT MODIFY

    ;; Your code starts here

    dec ecx ; ca sa avem len - 1 pasi
vectorLoop:
    push ebx ;adresa unde vrem sa punem distanta rezultata
    push eax ;adresa din vectorul de puncte, vor fi verificate primele 2 puncte
    call points_distance
    add esp, 8
    add ebx, 4 ; trecem la urmatoarea adresa pentru distanta
    add eax, 4 ; trecem la urmatorul punct
    loop vectorLoop

    ;; Your code ends here

    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY