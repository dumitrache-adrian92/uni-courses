Metode Numerice Tema 2 - Dumitrache Adrian-George (314CC)

1 - Proximal
In mare a fost nevoie sa inteleg informatiile din cerinta extrem de bine si sa
fiu atent la pasii din schelet. Au fost unele lucruri care m-au bagat in
ceata initial, eu fiind o persoana neinclinata catre matematica, cum ar fi
for-urile cu y si x (care inteleg acum ca au sens in axa xOy).
Alt lucru care a avut de a face cu faptul ca am presupus ca trebuie noi sa
deschidem fisierele. Desigur, puteam sa verific ce primesc prin checker, dar
nu am facut-o.

1.1 - 2x2
Am facut un vector ce contine indicii in forma lor reala (de la 1 la 2 cu
diferente de marimea STEP) si am initializat o matrice nxn (marimea vectorului)
Scheletul cerea sa determin cele 4 puncte, ceea ce am lasat facut insa nu am
folosit intr-un final. Pentru a aplica interpolarea am parcurs matricea finala
si am pentru fiecare index am rotunjit valorile din vectorul de indexuri reale
corespunzatoare fiecarei pozitii din matrice (adica vect[i] si vect[j]) pentru
a determina valorea pixelului din out.

1.2 - Resize
Am calculat factorii scalari adaptati pentru indexarea Octave, am definit
matricea de transformare conform cerintei, am calculat inversa acestei matrici
folosind faptul ca e diagonala (T*T^(-1)=I2 rezulta ca inversa are termenii
nenuli inversati) si am inceput interpolarea.
Pentru fiecare pixel (parcugere facuta cu indexare de la 0 pentru a pastra
punctul 0,0) aflu x_p si y_p inmultind vectorul reprezentat de x, y curent si
ii incrementez pentru a trece la coordonate [1, n]. Valoarea pixelului curent
se afla in imaginea originala la rotunjitul lui (y_p, x_p).

1.3 - Rotate
Am determinat sin si cos de unghiul dat si am calculat cele 2 matrice de
tranformare. Interpolarea este similara punctul anterior, dar dupa ce
determinam x_p si y_p urmeaza sa verificam daca se afla in limitele imaginii
si sa aflam cele 4 puncte inconjuratoare (facut cu floor si ceil). In cazul in
care, dupa determinarea punctelor inconjuratoare, se observa ca avem x_p si/sau
y_p numere naturale, atunci intram in cazuri speciale cu cateva formule deduse.
Daca nu, calculam cei 4 coeficienti prin rezolvarea sistemului dat in cerinta.
Astfel, folosim formula data pentru a calcula valoarea pixelului si trecem mai
departe.

2 - Bicubic
Task relativ mai usor, probabil pentru ca se mai repeta unele idei si se dau
majoritatea formulelor.

2.1 - fx, fy, fxy, coef
Doar functii ce aplica formulele date.

2.2 - precalc_d
Apelam functiile anteriore pentru a calcula toate derivatele necesare,
singurul aspect creativ este cum am abordat derivatele pixelilor aflati la
marginea imaginii, care trebuie sa fie 0. Pentru derivata pe x nu parcurgem
prima si ultima coloana, pe y nu parcugem prima si ultima linie, iar pe xy
ambele deodata. Cum matricele au fost initial nule, acum avem valorile corecte.

2.3 - Resize
Cam la fel ca la task-ul anterior pana cand trebuie sa calculam valoarea
pixelului. Moment in care calculam coeficientii de interpolare cu functia de
mai devreme, trecem coordonatele in patratul unitate si aplicam formula.

1 si 2 - RGB
Am folosit motorul de cautare Google ca sa imi dau seama cum extrag culorile
separate si cum concatenez, restul subpunctului este doar apelul functiei
anterioare pentru fiecare canal, deci trivial.