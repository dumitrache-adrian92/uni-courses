%include "../include/io.mac"

struc point
    .x: resw 1
    .y: resw 1
endstruc

section .text
    extern printf
    global points_distance

points_distance:
    ;; DO NOT MODIFY

    push ebp
    mov ebp, esp
    pusha

    mov ebx, [ebp + 8]      ; points
    mov eax, [ebp + 12]     ; distance
    ;; DO NOT MODIFY

    ;; Your code starts here
    xor ecx, ecx
    xor edx, edx
    mov cx, [ebx] ; x primul punct
    mov dx, [ebx + 4] ; x al doilea punct

    cmp cx, dx
    jne yAxisEqual ; daca nu sunt egale, atunci dreapa e paralela cu Oy
xAxisEqual:
    mov cx, [ebx + 2] ; y primul punct
    mov dx, [ebx + 6] ; y al doilea punct
    ; urm instructiuni interschimba cele 2 valori astfel incat maximul sa se
    ; in edx
    cmp dx, cx
    jge end
    push dx
    mov dx, cx
    pop cx
    jmp end
yAxisEqual:
    ; urm instructiuni interschimba cele 2 valori astfel incat maximul sa se
    ; in edx
    cmp dx, cx
    jge end
    push dx
    mov dx, cx
    pop cx
end:
    ; scadem cei doi indici pentru a obtine distanta
    mov [eax], edx
    sub [eax], ecx
    ;; Your code ends here
    ;; DO NOT MODIFY
    popa
    leave
    ret

    ;; DO NOT MODIFY