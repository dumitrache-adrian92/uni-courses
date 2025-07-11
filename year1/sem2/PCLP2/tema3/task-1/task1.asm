section .text
	global sort
	extern printf

; struct node {
;     	int val;
;    	struct node* next;
; };

;; struct node* sort(int n, struct node* node);
; 	The function will link the nodes in the array
;	in ascending order and will return the address
;	of the new found head of the list
; @params:
;	n -> the number of nodes in the array
;	node -> a pointer to the beginning in the array
; @returns:
;	the address of the head of the sorted list
sort:
	enter 0, 0
	push ebx ; fiindca ebx trebuie prezervat
	push esi
	push edi

	mov ecx, DWORD [ebp + 8] ; numarul de noduri
	mov eax, DWORD [ebp + 12] ; vector cu n elemente din structurile

	; gasim offsetul minimului inainte sa incepem sortarea propriu zisa
	xor edi, edi
	inc edi
	mov ebx, 0
minimum:
	xor esi, esi
	mov esi, DWORD [eax + ebx]
	cmp esi, DWORD [eax + edi * 8]
	jle no_new_minimum
	xor ebx, ebx
	mov ebx, edi
	imul ebx, 8
no_new_minimum:
	inc edi
	cmp edi, ecx
	jl minimum

	; sortare bazata pe gasirea unui minim mai mare decat minimul gasit
	; la pasul anterior, minimul se va schimba la fiecare pasa si vom gasi
	; altul in functie de el
	xor edx, edx ; contor de pasi
	; o sa avem n - 1 pasi
	mov esi, ecx
	dec esi
	push ebx ; o sa avem nevoie de cel mai mic mai tarziu
min_sort:
	xor edi, edi ; contor pentru parcurgerea vectorului
new_minimum:
	; eliberam niste registre ca nu ne-a facut bil gaitz mai multe
	push ecx
	xor ecx, ecx
	push edx
	xor edx, edx
	push esi
	xor esi, esi
	; daca nodul curent este nodul minim curent, trecem la urmatorul pas
	mov ecx, edi
	imul ecx, 8
	cmp ecx, ebx
	je next_step
	; daca nodul curent este mai mic decat nodul minim curent, trecem la
	; urmatorul pas
	mov edx, DWORD [eax + ecx] ; val nod curent
	cmp edx, DWORD [eax + ebx]
	jl next_step
	; verificam ce se afla in pointerul next al elementului minim
	; daca este NULL si restul testelor au trecut, inseamna ca am gasit un nou
	; minim, insa daca nu este NULL, trebuie sa comparam valoarea elementului
	; next cu valoarea elementului curent pentru a decide daca trebuie schimbat
	mov esi, DWORD [eax + ebx + 4]
	cmp esi, 0
	je change_pointer
	; verificam daca valoarea curenta este mai mica sau nu decat ce avem deja
	push ecx
	xor ecx, ecx
	mov ecx, DWORD [esi]
	mov esi, ecx
	pop ecx
	cmp esi, edx
	jl next_step

	; instructiuni care schimba valoarea de next a nodului minim
change_pointer:
	xor esi, esi
	mov esi, eax
	add esi, ecx
	mov DWORD [eax + ebx + 4], esi

	; instructiuni pentru restaurarea registrelor si trecerea la urmatorul pas,
	; daca este cazul pentru primul "for"
next_step:
	inc edi
	pop esi
	pop edx
	pop ecx
	cmp edi, ecx
	jl new_minimum

	; schimbam nodul minim pentru a il gasi pe urmatorul
	push esi
	xor esi, esi
	mov esi, DWORD [eax + ebx + 4]
	sub esi, eax
	mov ebx, esi
	pop esi

	; trecerea la urmatorul pas pentru al doilea for
	inc edx
	cmp edx, esi
	jl min_sort

	; restauram in ebx offsetul nodului cu valoarea cea mai mica din toate
	; punctele de vedere pentru a ii schimba valoarea lui eax cu scopul
	; de return
	pop ebx
	add eax, ebx

	; restauram registrele ce trebuie prezervate
	pop edi
	pop esi
	pop ebx
	leave
	ret

	; concluzie: n-am avut viziune pentru ca acum as face altfel ngl,
	; cred ca solutia intended (si mult mai simpla), era sa caut urmatorul
	; nod pentru fiecare nod; aceeasi complexitate, mai putina tractoreala