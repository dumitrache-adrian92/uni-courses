# Subiectul 1

a. Completați funcția `mergeAAs()` din fișierul `s1_a.d` astfel încăt aceasta să primească 2 array-uri asociative (hashtable-uri) ale căror chei sunt de tip `string`, iar valorile de tip `int` și să întoarcă **reuniunea** acestora.
Definim reuniunea a două hashtable-uri ca fiind un nou hashtable ce conține toate cheile din hashtable-uril, împreună cu valorile acestora din dicționarele inițiale.
În cazul in care o cheie se găsește în ambele dicționare, reuniunea va conține valoarea din **cel de-al 2-lea parametru al funcției `mergeAAs()`**.
Urmăriți exemplele din blocul `unittest` pentru a înțelege mai bine funcționalitatea dorită.

b. Analizați funcția `foo()` și blocul `unittest` din fișierul `s1_b.d`.
Completați **doar definițiile variabilelor `a` și `b`** din `unittest` astfel încât `assert()`-ul din acesta să nu genereze erori.
Nu este permisă modificarea funcției `foo()` sau a `assert()`-ului.

c. Modificați semnătura și completați funcția `checkNumbers()` din fișierul `s1_c.d` astfel încăt aceasta să întoarcă un nou vector.
Elementele acestui vector vor fi:

- cele mai mici puteri ale lui 2 **mai mari** decât elementele vectorului primit ca parametru dacâ tipul elementelor acestora este unul numeric (`int`, `long`, `char` etc.)
- vectorul primit ca parametru inversat în caz contrar.

Urmăriți exemplele din blocul `unittest` pentru a înțelege mai bine funcționalitatea dorită.
Folosiți cât mai multe funcții din biblioteca standard [Phobos](https://dlang.org/phobos/).
