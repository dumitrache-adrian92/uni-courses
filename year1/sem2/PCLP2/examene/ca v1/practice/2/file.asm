extern printf
extern scanf
extern strrchr
extern calloc
extern read
extern free

section .rodata
  scanf_str: db "%s", 0
  printf_str: db "%s", 0
  printf_int: db "%d", 0xA, 0xD, 0

section .data
    search_char: db 'a'

section .bss
  ptr_s resd 1


section .text
global main

; TODO a: Implementati functia char* read_string(int len) care citeste de la
;         tastatură un sir de caractere alfabetic de lungime maxima len
;         (inclusiv terminatorul de sir) si il stochează intr-o zonă
;         de memorie alocată dinamic pe heap de aceeasi lungime.
;
;         Apelati functia in programul principal si afișați sirul de caractere
;         introdus.
;
;         Hint: Se poate utiliza functia "read" a crărei apel echivalent ı̂n C este
;               read(0, str, 128); pentru a citi un sir de maxim 128 de caractere.
;
;         Observatie: Functiile de biblioteca modifca o parte din registre - CDECL
read_string:
  ret


; TODO b: Implementati functia a carei antent ı̂n C este:
;         int get_char_pos(char*str, char chr). Functia intoarce indexul ultimei
;         aparitii a caracterului chr ı̂n sirul str. In cazul ı̂n care caracterul
;         nu există ı̂n sir, functia va ı̂ntoarce valoarea -1.
;
;         Apelati functia in progmaul principal pentru sirul citit de la tastatura
;         si variabila search_char, apoi afisati rezultatul acesteia pe o line separată.
;
;         Hint: Pentru a obtine un pointer către ultima aparitie a unui caracter
;               dintr-un sir puteti utiliza functia strrchr care arecu apelul
;               echivalent ı̂n C: char *p = strrchr(str, search_char);
;
;         Observatie: Functiile de biblioteca modifca o parte din registre - CDECL
get_char_pos:
    ret

; TODO c: Implementati functia a carei antent ı̂n C este:
;         void upper_to_pos(char *str, char chr).
;         Functia transforma in-place caracterele sirului str ı̂n litere mari
;         pana la ultima apararitie a caracterului chr, inclusiv, iar restul
;         le lasa neschimbate.
;
;         Observatie: Functiile de biblioteca modifca o parte din registre - CDECL

upper_to_pos:
  ret

main:
    push ebp
    mov ebp, esp

    ; TODO a: Apelati functia read_string pentru o lungime maxima de 64 de caractere
    ;         si afișați sirul de caractere introdus.

    ; TODO b: Apelati functiaget_char_pos pentru sirul citit de la tastatura
    ;         si variabila search_char, apoi afisati rezultatul acesteia pe o
    ;         line separată.

    ; TODO d: Apelati functia void upper_to_pos(char *str, char chr) pentru sirul
    ;         citit de la tastatură si variabila search_char.
    ;
    ;         Afisati sirul rezultat pe o line separata si de-alocati corespunzator
    ;         sirul anterior alocat pe heap.


    ; Return 0.
    xor eax, eax
    leave
    ret
