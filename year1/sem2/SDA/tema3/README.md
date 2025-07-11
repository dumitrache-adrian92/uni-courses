Tema 3 SDA - Dumitrache Adrian-George (314CC)

Cerinta 1:
La baza am folosit algoritmul lui Dijkstra pentru tot, a fost nevoie sa adaug
doar mentinerea unui vector de predecesori cu scopul de a recrea pasii pentru
cel mai scurt drum de la depozit la magazin cu o functie recursiva acest din
dorinta de a nu ii avea trecuti invers.
Practic, pentru fiecare cursa de la un depozit la un magazin, apelez Dijsktra
pentru drumul dus si pentru drumul intors din care imi rezulta lungimile
respective si vectorul lor de predecesori, dupa imi generez cele doua drumuri
in vectori si deja am toate informatiile necesare ca sa afisez informatiile
cerute si adun lungimea celor doua drumuri intr-un total pe care il afiseze
dupa ce am primit toate cursele ce trebuie facute.

Cerinta 2:
ctc = componenta tare conexa
Initial am vrut sa fiu fancy si sa folosesc unul dintre algoritmii mai avansati
pentru determinarea componentelor tare conexe, cum ar fi Tarjan sau Kosaraju,
dar pentru ca nu am asa ceva implementat in C si din dorinta de a termina cele
3 teme suprapuse ca de obicei am decis sa plec de la algoritmul lui Warshall
care transforma matricea de adiacenta intr-o matrice de drumuri, unde mat[i][j]
este egala cu 1 daca exista drum de la i la j si 0 in caz contrar.
Pentru inceput, copiez matricea de adiacenta si elimin muchiile legate de
depozite ca sa ne fie mai usor dupa si aplic Warshall pe ea.
Acum vine partea convenabila, daca mentin un vector de noduri vizitate si
parcurg fiecare nod si fiecare vecin al sau, pot afisa usor totul in ordine
crescatoare cum este cerut. Procedeul este acesta:
    - daca nodul curent a fost vizitat trecem la urmatorul nod
    - pentru restul nodurilor, verificam daca exista drumuri in ambele directii
    daca da, toate nodurile gasite si nodul curent apartin aceluiasi ctc
    si le marcam ca fiind vizitate
Acest procedeu este repetat de 2 ori, tot din lene, odata pentru a numara cate
ctc-uri avem (pentru ca asta trebuie afisat prima data si recursiv nu mai merge
schema) si odata pentru a afisa ctc-urile in sine.

Cerinta 3:
Cu hint-ul din cerinta am modificat Dijkstra astfel incat sa calculam distanta
pe stari cu masca de biti. Practic, avem o matrice cu n linii si 2^n coloane,
unde mat[i][j] este distanta minima de la sursa la nodul i, iar j este masca de
biti ce va reprezenta prin ce noduri s-a trecut. Pentru fiecare serie de noduri
data, am facut o variabila externa de tip firm pentru a stoca doar nodurile
respective alaturi de depozite, urmand sa apelez Dijkstra cu fiecare depozit ca
sursa si sa aleg valoarea minima obtinuta ca solutie. Mi s-a parut mai usor sa
implementez Dijkstra cu cozi de data aceasta asa ca avem 2 cozi, una pentru
nod (i) si alta pentru bitmask(j), fiindca mi-a fost lene sa implementez inca o
structura si oricum n-aveam coada implementata generic, solutii creative in
momente disperate. Conceptele de la Dijkstra sunt aplicate destul de similar,
doar ca luam in considerare mai multe posibilitati si ne jucam cu masti.
Am aplicat cateva "scheme", cum ar fi faptul ca 2^indice nod ne da o masca
doar cu el marcat ca vizitat.
La final, dupa ce s-au generat aceste distante, parcugem incepand cu masca
care contine nodurile dorite si verificam la fiecare pas ca masca "buna" sa fie
prezenta, si actualizam minimul daca este cazul, acesta fiind returnat la final.