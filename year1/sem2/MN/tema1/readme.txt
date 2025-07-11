Tema 1 - Metode Numerice
Dumitrache Adrian-George - 314CC

Salut! In general imi place sa fac README-uri bazate in jurul fiecarei functii scrise si
la un nivel destul de general, lucru pentru care compensez prin comentarii care detaliaza
fiecare sectiune a codului. Asa ca, in caz ca este ceva neclar in acest README, cel mai
probabil este explicat in comentarii. Multumesc!

0 - Maruntisuri despre implementare

Am preferat sa fac citirea fisierelor cu dlmread pentru ca nu-mi place cititul linie cu linie
(ce implica si convertire din string) si element cu element n-am stiu sa fac cand am inceput tema.

Algoritmii care stiam ca pot sa ii iau din lab-uri (G-S, SST), au fost luati din lab-uri aproape
identic.

Totul a fost rulat si testat cu Octave pe Linux nativ, posibil sa se planga Matlab-ul de unele
chestii.

Sunt obisnuit cu termenii din liceu cand vine vorba de teoria grafurilor deci pe aceea i-am folosit
in mare.

0.1 - Construirea matricei de adiacenta si a matricei stocastice

Parcurgerea din care rezulta matricea de adiacenta si matricea K, atat pentru metoda iterativa,
cat si cea algebrica, decurge astfel:
    - se ia elementul de pe prima linie ca fiind numarul de noduri = N
    - pentru urmatoarele N linii, se ia primul element ca fiind nodul pentru care
citim informatii = current, al doilea ca fiind gradul exterior = k(current, current) si restul
elementelor ca fiind noduri catre care nodul curent are muchie
    - acest lucru este marcat in matricea de adiacenta prin valoarea 1 pe pozitia (current, nrVecin)
    - deoarece dlmread umple cu zerouri liniile mai scurte, ignoram orice valoare de 0 in
a 3-a etapa a citirii de linie
    - iar daca o muchie se duce spre nodul de la care pleaca, nu notam acest lucru si
decrementam gradul exterior deoarece aceste legaturi nu se iau in calcul conform cerintei

Pentru a obtine matricea stocastica folosim formula data in articolul Wikipedia: M = (k^(-1) * adiac)'

1 - Iterative

Aici am aplicat formula matriceala pentru aproximarea vectorului PR (luata de pe Wikipedia) plecand
cu valoarea initiala de 1/N. Formula este aplicata pana cand valoarea absoluta dintre diferenta
iteratiilor este mai mica decat eps. Rezultatul pe procesorul meu e diferit fata de exemplu cu valori
de mai putin de 0.0001, deci pare ok.

2 - Algebraic

Cea mai grea parte e deducerea formulei. Odata ce am avut-o si am inversat si matricea din formula
respectiva nu a mai fost nimic de facut. In legatura cu inversarea matrice totusi:

    2.1 - PR_Inv

    Functia descompune QR matricea primita prin algoritmul Gram-Schmidt si determina inversa prin
    prelucrarea formulei A = QR si calcularea inversei prin rezolvarea a N sisteme superior
    triunghiulare (realizat de functia SST facuta in lab 2).
    Nu am fost foarte incantat de faptul ca am fost obligati (din cauza faptului ca cerinta mentioneaza N
    sisteme) sa folosim metoda asta totusi, la fel de bine puteam sa facem astfel:
    A = QR;
    A^(-1) = R^(-1) * Q^t
    Si cum R este triunghiulara, putem determina usor inversa din relatia R * R^(-1) = In

    2.2 - SST

    Practic plecam de la ultima linie de unde putem determina instant ultima valoarea a vectorului x
    si continuam asa, celelalte valori depinzand de valori calculate anterior.

3 - PageRank

De abia prin zona asta mi-am dat seama cum sta treaba cu citirea din fisiere. Probabil cel mai ciudat
lucru la Octave e natura sa high level cand vine vorba de calcul numeric si exact opusul in lucrul
cu orice altceva (chiar am crezut ca pot aduna string-uri ca in JavaScript). Am folosit strcat ca sa
fac numele fisierului de output si am inceput sa afisez fiecare lucru cerut: numarul de elemente,
PR prin metoda iterativa, PR prin metoda algebrica si am trecut la rezolvarea subpunctului in sine.

Pentru sortarea vectorului si retinerea pozitiilor initiale m-am folosit de primele 2 output-uri
ale functiei sort (genial), am apelat functia care-mi creaza vectorul cu apartenente si am afisat.

    3.1 - Apartenenta

    Am dedus formulele pentru a si b astfel incat functia sa fie continua si am pus returnat
    valoarea functiei u prin y.

Concluzie:

Tema cred ca e bine, parerea mea despre ea:
Mi-a placut mult subiectul abordat, destul de cunoscut incat sa starneasca curiozitatea si destul de
complex incat sa merite pus la portofoliu. Nu sunt mare fan al cerintei totusi, mi s-a parut greoaie
alocuri, cel mai enervant lucru a fost totusi faptul ca nu era clar care era metoda iterativa din acel
articol (am aflat de pe forum) si nici ce ar trebui sa facem pentru metoda algebrica (un simplu "trebuie
sa deduceti formula" ar fi fost de ajutor, in loc sa ne mai chinuim, din nou, pe forum). De asemenea, tema
s-a suprapus perfect cu cea de la SD pentru seria CC, stiu ca materia aceasta e la comun cu toata facultatea
dar se putea comunica cu restul echipelor pentru a evita asta.
Nu stiu daca a fost intentionat (si oricum a afectat doar un sfert de facultate presupun), dar a fost buna
continuitatea cu cursul de ALGAED de semestrul trecut al seriei CC unde ne-a fost prezentat algoritmul cat de
cat ca exemplu de aplicatie al algebrei liniare in lumea reala, ideea de materii conectate e ceva ce trebuie
aplicata cat mai mult in opinia mea.