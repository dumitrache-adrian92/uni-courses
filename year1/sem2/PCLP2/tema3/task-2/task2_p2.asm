section .text
	global par

;; int par(int str_length, char* str)
;
; check for balanced brackets in an expression
par:
	; schema ieftina pentru ca nu pot sa dau mov la vector ca un om normal
	add esp, 4
	pop ecx ; str_length
	pop edx ; str
	sub esp, 12

    ; practic tinem un contor pentru paranteze pe care il incrementam pentru
    ; fiecare paranteza deschisa si il decrementam pentru fiecare paranteza
    ; inchisa, determinam raspunsul astfel:
    ; daca in aceasta numaratoare contorul devine negativ atunci
    ; secventa este incorecta
    ; daca dupa parcurgerea intregii secvente contorul e diferit de 0, atunci
    ; secventa este incorecta
    ; daca este egal cu 0, atunci secventa este corecta
	xor edi, edi ; contor pentru numarul de paranteze
verify_expression:
    ; determinam ce fel de paranteza si incrementam/decrementam corespunzator
	cmp BYTE [edx], 40
    je open_paranthesis
    jmp closed_paranthesis

open_paranthesis:
    inc edi
    jmp skip
closed_paranthesis:
    dec edi

    ; trecem la urmatorul caracter
skip:
    inc edx
    ; verificam daca contorul e negativ, daca da, stim ca secventa e gresita
    cmp edi, 0
    jl exit
    loop verify_expression

    ; verificam daca contorul e egal cu 0
exit:
    xor eax, eax
    cmp edi, 0
    jne false
    inc eax
false:
	ret
