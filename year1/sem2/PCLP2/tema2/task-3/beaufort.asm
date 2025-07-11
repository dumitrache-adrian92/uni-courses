%include "../include/io.mac"

section .text
    global beaufort
    extern printf

; void beaufort(int len_plain, char *plain, int len_key, char *key, char tabula_recta[26][26], char *enc) ;
beaufort:
    ;; DO NOT MODIFY
    push ebp
    mov ebp, esp
    pusha

    mov eax, [ebp + 8]  ; len_plain
    mov ebx, [ebp + 12] ; plain (address of first element in string)
    mov ecx, [ebp + 16] ; len_key
    mov edx, [ebp + 20] ; key (address of first element in matrix)
    mov edi, [ebp + 24] ; tabula_recta
    mov esi, [ebp + 28] ; enc
    ;; DO NOT MODIFY
    ;; TODO: Implement spiral encryption ??? hai jet
    ;; FREESTYLE STARTS HERE

    ; proces prin care obtinem key-ul repetat pana la lungimea lui plain
    push edi ; n-avem nevoie de ele deocamdata
    push esi
    xor edi, edi ; contor plain
    xor esi, esi
    mov esi, ecx ; lungimea originala a lui key
lenghtenKey:
    ; punem in eax litera pe care vrem sa o concatenam
    push eax
    xor eax, eax
    mov al, BYTE [edx + edi]
    mov BYTE [edx + ecx], al
    ; resetam contorul daca am parcurs tot plain-ul
    inc edi
    cmp edi, esi
    jne skipReset
    mov edi, 0
skipReset:
    inc ecx ; crestem numarul de litere a lui key ca sa concatenam si urm val
    pop eax
    cmp ecx, eax
    jl lenghtenKey

    mov BYTE [edx + ecx], 0 ; adaugam terminator de sir
    pop esi ; recuperam din stiva valorile
    pop edi

    mov ecx, 0
encrypt:
    push eax
    push esi
    xor eax, eax
    xor esi, esi
    mov al, BYTE [ebx + ecx]
    sub al, 65 ; indicele in tabel al coloanei reprezentate de litera curenta
    push ebx
    ; parcurgem pana gasim litera din key
tabulaRecta:
    xor ebx, ebx
    add esi, eax
    mov bl, BYTE [edi + esi]
    cmp bl, BYTE [edx + ecx]
    je exit

    sub esi, eax
    add esi, 26 ; sarim o linie
    jmp tabulaRecta
exit:
    pop ebx
    sub esi, eax

    push eax
    xor eax, eax
    ; calculam indicele liniei gasite cu o impartire antica
divide:
    sub esi, 26
    inc eax
    cmp esi, 0
    jne divide
    pop esi
    pop esi
    ; criptarea propriu-zisa
    mov BYTE [esi + ecx], 65
    add BYTE [esi + ecx], al
    pop eax
    inc ecx
    cmp ecx, eax
    jne encrypt

    ;; FREESTYLE ENDS HERE
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY