section .text
	global cmmmc
;; int cmmmc(int a, int b)
;
;; calculate least common multiple fow 2 numbers, a and b
cmmmc:
	; echivalent enter 0, 0
	push ebp
	push esp
	pop ebp

	; extragem datele de intrare
	push DWORD[ebp + 8]
	push DWORD[ebp + 12]
	pop edx ; a
	pop eax ; b

	push eax
	pop ecx ; b

	imul eax, edx ; a * b

	; calculeaza cmmdc prin scaderi repetate si pune rezultatul
	; in registrele edx si ecx
cmmdc:
	cmp edx, ecx
	jl lower
	; a > b
	sub edx, ecx
	jmp skip
lower: ; a < b
	sub ecx, edx
skip:
	cmp edx, ecx
	jne cmmdc

	; (a * b) / cmmdc(a, b) = cmmmc(a, b)
	; am facut impartirea asa pentru ca e mai rapid decat sa caut cum
	; functioneaza div si oricum stiu ca va da un numar natural
	xor edi, edi
division:
	sub eax, edx
	inc edi
	cmp eax, 0
	jne division

	; punem rezultatul impartirii in eax pentru a il returna
	push edi
	pop eax

	; echivalent leave
	push ebp
	pop esp
	pop ebp
	ret
