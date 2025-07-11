# **Tema 1 APD - Dumitrache Adrian-George [334CC]**

## **Explicatie solutie**

Am paralelizat algoritmul prin impartirea muncii functiilor rescale_image,
sample_grid si march intre mai multe thread-uri. Fiecare thread va computa o
parte din imaginea rescalata (daca e cazul), va genera o parte din matricea de
puncte si va parcurge punctele generate pentru a produce bucata din imaginea
finala corespunzatoare thread-ului.

Toate thread-urile isi pornesc executia in acelasi timp si primesc ca argument o
structura ce contine cam tot ce au nevoie pentru a rula cei 3 pasi paralelizati.
Daca e nevoie, fiecare thread incepe sa rescaleze cate o bucata din imagine,
apoi asteapta la o bariera deoarece exista posibilitatea ca un thread sa
aibe nevoie de pixeli pe care nu i-a generat inca alt thread la urmatorul pas.
Urmeaza ca fiecare thread sa genereze linii din grid[][], lucrul interesant aici
e ca generam o linie in plus fata de cate trebuie deoarece march acceseaza si
punctele dedesubtul liniei curente, deci si cele dedesubtul ultimei linii care
sunt generate de alt thread. Acest lucru evita un posibil race condition fara sa
mai suferim overhead-ul unei bariere in plus cu foarte putina redundanta
adaugata. La final, fiecare thread aplicat functia march pe zona sa de grid[][]
si genereaza parte din imaginea finala.

Ultima problema de sincronizare ar fi ca avem nevoie ca toate thread-urile sa
isi termine munca inainte de a scrie imaginea pe disk. Pentru simplitatea, doar
asteptam finalizarea thread-urilor cu join (ceea ce trebuia sa facem oricum).

## **Proces de gandire**

Prima data am vazut for-urile din functiile sample_grid si march si mi s-au
activat putin neuronii, asa ca am inceput sa paralelizez cele doua functii.
Evident, acest lucru nu prea a ajutat performanta programului pe imaginile de la
testele 6 si 7, fiindca operatia de rescale este mult mai scumpa din punct de
vedere al complexitatii decat celelalte.

Deci, lesson number 1: Paralelizeaza ce dureaza mai mult, presupun ca era
evident, dar ma gandeam ca macar o sa creasca perfomanta putin si paralelizarea
celorlalte functii. A avut dreptate Mogos, O(n^7) tot O(n^7) e. GG

Am paralelizat si rescale_image si am inceput sa vad rezultate, mai exact
punctaj maxim. yay.

Intuitiv m-am gandit ca avem nevoie de o bariera dupa rescale_image, dar nu
am reusit sa demonstrez de ce doar ruland algoritmul in mod normal (nici dupa
foarte multe rulari). Smecheria pe care am facut-o a fost sa pun un sleep pe un
singur thread, ceea ce a aratat ca exista defapt un race condition si ca bariera
e necesara.

Am facut acelasi lucru si ca sa vad daca exista vreun race condition intre
sample_grid si march, dar nu pare sa fie cazul. De asemenea, am confirmat ca e
necesar sa generez o linie in plus la pasul de sample_grid (evident, puteam si
sa pun o bariera, in loc sa fac asta).

## **Concluzie**

Mai complicat decat la lab, acum cand scriu astea pare ca mi-a
luat o ora :)))

Anyway, sper ca e ok. Pe data viitoare.
