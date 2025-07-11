~20 ore pentru rezolvarea temei, ~1 ora compunere README

Problema 1:
~2 ore implementare, formatare, optimizare si comentarii

Solutia implementata implica utilizarea a trei structuri: un vector ce
reprezinta gradele perechilor si 2 matrice de caractere ce contin cuvintele
aflate in perechi. Astfel, o pereche indexata i are gradul grade[i] si este
formata din words1[i] si words2[i]. Pentru a sorta descrescator si a obtine
rezultatul dorit pe parcursul citirii adaugam valorile in structuri prin metoda
insertiei directe pe baza gradului perechiei, cat si a ordinii lexicografice a
primelor cuvinte din perechi in caz de egalitate de grad.
In legatura cu formatarea, exista mici incosistente in cazul liniilor foarte
lungi, precum antetul functiei directInsertion si while-ul cuprins in aceasta
(cat si in problema 2), din cauza faptului ca a fost nevoie sa sparg liniile
respective pentru lizibilitate. Astfel, am considerat ca e nevoie sa schimb
stilul de pozitionare al parantezelor in acest caz pentru a evita confuzii
chiar daca e inconsistent cu restul programului.

Problema 2:
~6 ore implementare, formatare, optimizare si comentarii

Rezolvarea implementata se foloseste de doua structuri pentru a reprezenta
datele de intrare, o matrice [N][2] ce reprezinta pozitia pe tabla a fiecarui
nebun si o matrice [M][M] ce reprezinta tabla de sah in sine. Pentru a
determina numarul de perechi de nebuni ce se ataca, folosim o functie care
verifica daca nebunii se afla pe aceeasi diagonala 1 cate 1. In cazul in care
exista o singura pereche ce se ataca, determinam indicii celor 2 nebuni si
verificam toate mutarile posibile ale acestora pana gasim una in care nu se mai
ataca nici un nebun sau pana epuizam toate mutarile.

Problema 3:
~8 ore implementare, formatare, optimizare si comentarii

La baza implementarii acestei solutii sta reprezentarea cubului rubik printr-un
tablou tridimensional [6][3][3], adica [fete][linii][coloane], cat si
codificarea culorilor in cifre de la 0 la 5. Astfel, convertim datele de
intrare in formatul numeric pentru a putea lucra mai usor cu acestea. Cand
efectuam mutarile vom modifica tabloul tridimensional, iar la final acesta va
fi convertit in formatul initial si afisat drept rezultat al problemei.
Initial, am vrut sa rezolv problema folosiind doar 2 functii pentru mutari
care primeau ca parametru de intrare o fata a cubului rubik si efectuau rotirea
ceasornica/trigonometrica, insa nu am reusit sa fac acest lucru, motiv pentru
care am abordat o solutie mai lunga si a fost problema care a durat cel mai
mult sa o rezolv. Sper totusi ca ideea mea e posibila :)

Problema 4:
~4 ore implementare, formatare, optimizare si comentarii

Implementarea acestei solutii determina cele 3 matrice si afiseaza conform
cerintei matricea cu cel mai mare numar de puncte convertita in baza 10.
Majoritatea operatiilor realizate sunt modularizate prin functii ce sunt deja
explicate in comentarii, dar exista cateva concepte ce sunt aplicate in mod
frecvent in cadrul programului:
1. Utilizarea ordinii codurilor ASCII pentru eficientizare, e.g. in cadrul
functiilor dec_to_bin si afisareMatriceZecimal.
2. Parcurgerea diagonalelor unei matrice folosind formulele a[i][i] pentru
diagonala principala si a[i][n-1-i] pentru diagonala secundara adaptate pentru
matricea impartita in 4.