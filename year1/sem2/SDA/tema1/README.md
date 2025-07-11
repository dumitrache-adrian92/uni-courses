Tema 1 - Structuri de Date si Algoritmi

0 - Reprezentarea datelor, functiile de baza si structura programului
    Inainte de a incepe rezolvarea cerintelor propriu zise am decis ca e important
sa am implementarea unei liste dublu inlantuite pregatita si testata corespunzator.
Am ales sa folosesc o lista necirculara deoarece nu am observat vreun avantaj in
contextul temei, iar varianta cu santinela mi se pare mai mare bataie de cap fata
de tratarea tuturor cazurilor la adaugarea unui nou nod (am mers oarecum pe ideea ca
prefer sa fie mai grea implementarea decat sa fie mai complicat lucrul cu lista in
sine). Lista este oarecum reprezentata de structura *dlist* care contine cate un pointer
catre inceputul si sfarsitul liste, cat si numarul de elemente din lista (fiind data de
intrare/iesire, sincer nu prea m-am folosit de ea pentru a rezolva, mai mult m-a incurcat).
Structura unui nod este relativ standard pentru cerinta noastra, dar am decis sa folosesc
si variabila *toRemove*, initializata cu 0 la adaugarea unui nou nod, pentru o rezolvare
mai eleganta a primului subpunct.
    Pentru citirea unei liste intregi am scris functia readList, care se ocupa cu citirea
datelor de intrare de la tastatura, cat si apelarea altor functii care au rolul de a
initializa lista, respectiv de a adauga noduri noi in lista. Am scris doua functii de adaugare
de noduri: *pushTail* si *pushAfterNode*. La citirea initiala o folosesc doar pe prima, pastrand
astfel ordinea de citire a nodurilor, a doua functie a avut un rol important in rezolvarea
subpunctului 4. Functia *emptyList* verifica doar daca o lista e goala sau nu, am facut-o pentru
ca era data ca exemplu in curs si ma facea sa ma simt foarte matur sa am o functie exclusiv
pentru asta, dar cred ca am uitat de ea pe la jumatatea temei :). Avem de asemenea o functie
pentru afisarea intregii liste, una pentru eliberarea memoriei, dar si pentru eliminarea
unui singur nod.
    Programul are structurile si toate functiile declarate intr-un fisier header, respectiv
functiile scrise in alt fisier C fata de main. In cadrul main-ului avem citirea initiala a
datelor de intrare urmata de parcurgerea argumentele date in linia de comanda pentru a
determina ce operatii se vor realiza asupra listei. Urmeaza sa fie afisat rezultatul final
si memoria eliberata.
    De mentionat: toate functiile lucreaza pe o lista sau un nod, deci nu am simtit ca e necesar
sa tot mentionez parametrii de intrare ai fiecarei functii.

1 - Eliminare de exceptii folosind metode statistice (e1)
    La primirea acestui argument este apelata functia *removeExceptions* care parcurge
toate elementele eligibile pentru eliminare (toate inafara de primele si ultimele int(k/2)
elemente, deci intervalul de mijloc dintre ele, se folosesc 2 pointeri pentru a determina
acest interval) si determina pentru fiecare nod media si deviatia standard a ferestrei de
k elemente prin functiile *windowMean*, respectiv *standardDeviation* pentru a afla daca
un nod trebuie eliminat sau nu. Daca da, acest lucru este marcat prin variabila *toRemove*
din structura de nod. La final se parcurge toata lista si se elimina nodurile care au
toRemove = 1 prin functia *removeNode*. Acest lucru este necesar pentru ca, desi am putea
elimina nodul imediat ce aflam ca nu indeplineste conditiile, urmatoarele noduri au nevoie
de valoarea initiala a nodului ce trebuie eliminat pentru calculul mediei si deviatiei.

2.1 - Eliminare de zgomot folosind filtrare mediana (e2)
    Este apelata functia *medianFilter* si sunt parcurse toate nodurile care sunt
eligibile (toate inafara de ultimele k-1). Pentru fiecare nod se apeleaza functia
*medianNode* si se determina timestamp-ul elementului din mijloc, cat si a int(k/2)+1
valoare (prin metoda de numarare) si se adauga un nod nou cu cele doua valori determinate.
La finalul functiei sunt eliminate toate nodurile initiale, rezultand in lista filtrata
median.

2.2 - Eliminare de zgomot folosind filtrare prin media aritmetica (e3)
    Ideea de baza este aceeasi ca la subpunctul anterior, atat ca am acum noile noduri
se adauga folosind functia windowMean.

3 - Uniformizarea frecventei de timp a datelor (u)
    Solutia este destul de simplista, se apeleaza functia *equalize* si se parcurg toate
nodurile, verificand daca diferenta de timp intre nodul respectiv si cel anterior este
cuprinsa in intervalul dat sau nu. Daca da, se face media aritmetica intre ambele valori
ale nodului si sunt puse in nodul curent.

4 - Completarea datelor (c)
    Se parcurg toate elementele si de fiecare data cand se gaseste un element care are
o diferenta mai mare de o secunda fata de urmatorul nod (se face conversia de la milisecunde)
se adauga elemente intre cele doua noduri folosind formulele date la intervale de 200 de
milisecunde.

5 - Statistici (stδ)
    Ideea mea intuitiva a fost sa folosesc un vector de frecventa ca in probleme de bac din
liceu, dar ar fi trebuit sa fac acest lucru utilizand liste ceea ce pare haos. Am ajuns pana la urma la o solutie care determina minimul si maximul functiei si le foloseste pentru a determina intervalul
de multiplii a lui delta in care se afla toate valorile listei. Dupa care parcurg lista
pentru fiecare interval si determin cate elemente apartin acestuia, daca numarul e diferit de o,
afisez intervalul in formatul din cerinta.

Observatie:
    Am realizat ulterior ca recursivitatea ar fi usurat cu mult o mare parte din subpuncte,
in special e1-3, dar din pacate nu mai am timp sa mai modific, fiind presat de alte teme si partiale.
