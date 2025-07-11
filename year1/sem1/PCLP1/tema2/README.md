Timp alocat:
    - Dezvoltarea si testarea librariei biju.h: 6 ore
    - Task 1: 5 minute
    - Task 2: 2 ore
    - Task 3: 4 ore
    - Task 4: 3 ore
    - Task 5: nu sunt sigur, 10-15 ore pentru ca am pierdut notiunea timpului
    cand ma uitam la videouri, citeam documentatia pentru ncurses si il
    ascultam pe inegalabilul Cristi Mega (imi pare rau Bijule, pe viitor
    recomand o intoarcere la stilul consacrat in "Nebunia din Mamaia", acela
    fiind mult mai pe inimioara mea)
    - Total: 25-30 de ore

Explicatiile au fost gandite sa fie citite in ordinea README => comentarii cod

biju.h:
Cum a propus si cerinta, am decis sa modularizez functionalitatea comuna a
celor 5 taskuri intr-un fisier .h unde am declarat majoritatea functiilor
folosite, struct-ul ce contine informatiile unui site, enum-ul pentru culori,
cat si cateva librarii uzuale precum stdio.h, functiile fiind mai apoi definite
intr-un fisier numit biju.c introdus la compilarea tuturor programelor.
Cea mai importanta parte a fisierului, fiind comuna pentru toate task-urile,
este citirea datelor de intrare si memorarea acestora intr-un vector de
structuri tip site ce este realizata prin 2 functii detaliate in comentariile
din biju.c.

task1:
Relativ trivial cu functiile de citire deja scrise, doar sunt citite datele si
afisate cele necesare, urmand sa fie eliberata memoria alocata vectorului de
variabile tip structura si componentelor lor.

task2:
Ideea de baza pentru rezolvarea acestui task, cat si a task-ului 3, este
memorarea indexilor fiecarui site care contine input-ul dat intr-un vector.
Avantajul metodei acesteia este ca nu mai avem nevoie sa modificam baza de date
deloc pentru a ajunge la rezultat, astfel avem o functie ce filtreaza prin
site-uri si creaza un vector ce contine indexii site-urilor gasite, o functie
care verifica starea de ordine dintre 2 elemente struct site, cat si o functie
de sortare comuna cu task3 care primeste ca argument functia de ordine.

task3:
Solutia ca si logica este identica cu task2, singura diferenta fiind modul de
filtrare si crieteriul de sortare al site-urilor ce sunt detaliate in
comentariile functiei.

task4:
Programul cauta fiecare site introdus ca input si, daca il gaseste, ii
compara checksum-ul din citire cu cel determinat de functia checksum(),
afisand mesajele aferente rezultatului comparatiei. Acest lucru continua pana
cand este introdus un sir vid.

task5:
Din punct de vedere logic, programul este separat in 4 ecrane principale:
pagina de start, pagina de cautare, pagina de rezultate si cea de afisare a
site-ului ales, in aceasta ordine atat timp cat utilizatorul nu alege sa se
intoarca la un ecran anterior cu tasta B.
Cel mai important aspect al programului, care nu prea este discutat in
comentarii din cauza naturii sale, este faptul ca navigarea inapoi prin meniuri
cu tasta B este realizata cu comanda goto reveniind la un stadiu anterior al
codului, lucru ce am inteles ca nu e recomandat sa fac, dar chiar parea
momentul oportun sa incerc pentru prima data (si nu eram sigur cum sa
implementez functionalitatea de schimbare de ecrane intr-un loop).
Ca design am ales sa centrez totul, fiind usor de implementat si destul de
estetic fata de a lasa totul in stanga. Aveam si vise de a ii pune fata lui
Biju in ASCII pe prima pagina dar am decis ca trebuie sa termin semestrul asta.
Nu sunt sigur care a fost intentia in a ne pune sa folosim enum pentru a
reprezenta culorile, sincer mai mult m-a incurcat. Mai ales pentru ca modul de
alegere a culorilor e destul de restrictiv (trebuie puse in pereche). Cred ca
asta era ideea totusi.
Alt aspect de care nu sunt mandru e lipsa functiilor, decizie luata deoarece
lucrul cu ferestre mi s-a parut deja dificil cand totul era relativ liniar, si
a devenit si mai greu odata cu introducerea acestora.
Cred ca a iesit destul de bine si m-am mai obisnuit cu research-ul librariilor,
deci foarte fain.