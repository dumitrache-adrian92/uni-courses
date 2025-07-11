extern printf
extern calloc
extern scanf

section .data
    arr dd 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    N dd 10
    P dd 400
    Q dd 850
    fmt_int db "%u ", 0
    fmt_fmm db "%u", 0
    fmt_null db "", 0
    fmt_newline db 10, 0

section .text
global main

;TODO a: Implementati functia `void print_array(unsigned int *a, int N)` pentru a afisa
;   elementele vectorului `a` de dimensiune `N` pe o singura linie separate de cate un spatiu.
;
;   Afisarea se va face folosind functia `int printf(const char *format, ...);` din biblioteca standard C.
;
;   ATENTIE: Functia `printf` poate modifica registerele EAX, ECX si EDX. Pentru simplitate puteti folosi
;   instructiunile `pusha`, `popa` pentru a salva respectiv restaura toate registrele modificate de un apel de biblioteca.

print_array:
    push ebp
    mov ebp, esp
    pusha

    mov eax, [ebp + 8]
    mov ecx, [ebp + 12]

    xor esi, esi

print_all:
    xor edx, edx
    mov edx, DWORD [eax + 4 * esi]
    pusha

    push edx
    push fmt_int
    call printf
    add esp, 8

    popa

    inc esi
    cmp esi, ecx
    jne print_all

    push fmt_newline
    call printf
    add esp, 4

    popa
    leave
    ret

;TODO b: Implementati functia `int* alloc_array(int N)` care aloca memorie (dinamic) pentru `N` intregi. Memoria alocata va trebui zeroizata.
;   Pentru alocare de memorie puteti folosi functiile:
;   - `void *malloc(int size)`, care aloca `size` octeti. Memoria alocata nu este zeroizata.
;  SAU
;   - `void *calloc(size_t nmemb, size_t size)`, care aloca `nmemb` elemente fiecare de dimensiune `size`. Memoria alocata este zeroizata.
;
;   RECOMANDARE: folositi functia `calloc`
alloc_array:
    push ebp
    mov ebp, esp
    push ebx

    mov ebx, [ebp + 8]

    push DWORD 4
    push ebx
    call calloc
    add esp, 8

    pop ebx
    leave
    ret

;TODO c: Implementati functia `void read_array(unsigned int *a, int N)` care citeste de la intrarea standard
;   un vector `a` de `N` numere intregi fara semn.
;
;   Citirea de la intrarea standard se va face folosind functia `int scanf(const char *format, ...);` din biblioteca standard C.
;   e.g pentru citirea unui intreg
;       unsigned int elem;
;       scanf("%u", &elem);

read_array:
    push ebp
    mov ebp, esp
    pusha

    mov eax, [ebp + 8]
    mov ecx, [ebp + 12]

    xor esi, esi

scanf_loop:
    pusha
    push eax
    push fmt_fmm
    call scanf
    add esp, 8
    popa

    add eax, 4
    inc esi
    cmp esi, ecx
    jne scanf_loop

    popa
    leave
    ret

; TODO d: Implementati functia void update_interval(int *a, int N, int P, int Q)` care
;   va face urmatoarele operatii asupra sirului de elemente intregi fara semn `a` de dimensiune `N`"
;
;   a[i] = 2 * a[i], daca elementul a[i] se gaseste in intervalul [P, Q]
;   a[i] = a[i] / 2, daca elemente a[i] se gaseste in afara intervalului [P, Q]
;
; ATENTIE: este garantat ca P <= Q pentru toate apelurile functiei `update_interval`.

update_interval:
    push ebp
    mov ebp, esp
    pusha

    mov ecx, DWORD[ebp + 8]
    
    xor esi, esi
array_traversal:
    xor eax, eax
    xor edx, edx
    xor ebx, ebx
    mov eax, DWORD[ecx + 4 * esi]
    cmp eax, DWORD[ebp + 16]
    jl divide
    cmp eax, DWORD[ebp + 20]
    jg divide

double:
    mov edx, 2
    imul eax, edx
    mov DWORD[ecx + 4 * esi], eax
    jmp next
divide:
    mov ebx, 2
    idiv ebx
    mov DWORD[ecx + 4 * esi], eax
next:
    inc esi
    cmp esi, DWORD[ebp + 12]
    jne array_traversal

    popa
    leave
    ret

main:
    push ebp
    mov ebp, esp

    ; TODO a: Apelati functia `print_array(int *a, int N)` pentru a afisa vectorul `arr` de dimensiune `N` definit in sectiunea `.data`

    push DWORD[N]
    push arr
    call print_array
    add esp, 8

    ; TODO b: Alocati memorie pentru un vector de N intregi fara semn, apeland functia `alloc_array`
    ; si apoi afisati vectorul apeland functia `print_array`.

    push DWORD[N]
    call alloc_array
    add esp, 4

    push DWORD[N]
    push eax
    call print_array
    add esp, 8

    ; TODO c: Cititi de la intrarea standard un vector de `N` intregi apeland functia `read_array`
    ; si apoi afisati vectorul folosind functia `print_array`.

    push DWORD[N]
    call alloc_array
    add esp, 4

    push DWORD[N]
    push eax
    call read_array
    add esp, 8

    push DWORD[N]
    push eax
    call print_array
    add esp, 8

    ; TODO d: Transformati vectorul `a` de `N` elemente intregi fara semn citit la TODO c) apeland functia
    ; `update_array` si apoi afisati vectorul folosind functia `print_array`.
    ; Functia `update_array` va fi apelata astfel:
    ; `update_array(a, N, P, Q)` unde N, P si Q se gasesc in sectiunea `.data` iar vectorul `a` este cel citit la TODO c;

    push DWORD[Q]
    push DWORD[P]
    push DWORD[N]
    push eax
    call update_interval
    add esp, 16

    push DWORD[N]
    push eax
    call print_array
    add esp, 8

    ; Return 0.
    xor eax, eax
    leave
    ret
