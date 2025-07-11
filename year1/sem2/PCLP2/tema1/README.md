Tema 1 IHS / IOCLA / PCLP2 / aveti probleme - Dumitrache Adrian-George (314CC, elita)

0 - Precizari
Unele idei au fost implementate prost, precum, si nu limitate la, "sistemul" de bancnote
si faptul ca m-am chinuit mult prea mult sa nu fac 2 functii care au acelasi scop dar pentru
subpuncte diferite. In rest cred ca a fost ok.

Update in ultima zi de deadline: Am crezut ca len-ul lui arr reprezinta numarul de octeti al
lui arr in loc de numarul de elemente. Motiv pentru care metoda aplicata este destul de... mda.
Am decis sa schimb din dorinta de a nu fi depunctat pentru neintelegerea cerintei si nu pot spune
ca e o solutie foarte eleganta (cel putin se putea face mai modular).

Practic nu am schimbat rezolvarea aproape deloc, doar ca acum numar cate elemente am si folosesc
o functie care imi numara octetii lui arr si restul este rezolvat exact la fel.

Imi pare rau, daca in VMChecker se poate vedea istoricul de upload-uri o sa vedeti solutia initiala,
mult mai buna, in care folosesc len-ul lui arr ca si numar de octeti. Pur si simplu nu mai am timp
sa fac altceva chiar daca am cateva idei (cum ar fi o functie care numara octetii pana la un index
si modificarea tuturor functiilor).

0.1 - Functii comune intre subpuncte

sizeofType(unsigned char x)

    Calculeaza si returneaza lungimea in octeti ale celor doua bancnote pentru tipurile 1, 2 si 3.

charToInt_8/16/32(char* a)

    Converteste sirul de caractere in formatul de int al functiei, ulterior am realizat ca
as fi putut sa fac acest lucru cu o singura functie si mai putina bataie de cap. Totusi, atat
m-a dus capul atunci si am incercat deja odata sa repar si nu mi-a iesit, deci ramane asa pentru
ca seria CC a decis sa suprapuna 3 teme.

create_data_structure(data_structure *aux, char *input)

    Functia parseaza argumentele aflate in sirul de caractere input cu strtok si modifica datele
aflate la adresa pointerului aux. Astfel, la finalul functiei, avem un element pregatit sa fie
adaugat in vectorul generic arr. Aici apare multa tractoreala legata de tipuri din pacate,
existand instructiuni separate pentru fiecare tip de element.
    Procesul de baza este acesta:
- sarim peste primul token, acesta fiind insert (pt. functia add_last) sau indexul (pt. functia
add_at, se sare peste insert_at din apelul functiei)
- punem tipul elementului in header si trecem la urmatorul token
- restul argumentelor din input sunt memorate intr-o variabila apropiata (dedicator, bancnota1 si
bancnota2 de tipul cerut, dedicat) si apoi copiate in vectorul generic data din structura,
se foloseste lungimea fiecarui element pentru a concatena corect datele

byteCount(void *arr, int len)

    Parcurge tot vectorul arr printr-un header auxiliar si prin numararea octetilor.

0.2 - Main

    In main sunt declarate variabilele in care sunt extrase informatii din inputuri, cum ar fi
data_structure-ul ce trebuie adaugat in arr sau indexul elementelor de cautat/eliminat.
Urmeaza sa fie citite input-uri pana la introducerea comenzii "exit". Modul in care este decis
ce fel de operatie reprezinta input-ul este cu ajutorul functiei strstr care verifica daca
inputul incepe cu anumite siruri de caractere, urmand sa fie parcurs restul input-ului.

1 - add_last

    Aloca/Realoca memoria vectorului generic arr pentru a avea loc noul element la exactitate, se
copiaza octetii header-ului la adresa arr+oct (finalul vectorului), fiind usor de importat la loc
deoarece nu are elemente alocate dinamic, si apoi se copiaza octetii din data la adresa
arr+oct+sizeof(head). La final este incrementata valoarea lui len astfel incat sa reprezinte noua
marime a lui arr.

2 - add_at

    Aici apare prima data procesul de parcurgere a vectorului arr in care este folosit un header
auxiliar pentru a determina lungimea fiecarui element si a sari peste fiecare pana se ajunge
la indexul dorit. Daca indexul este mai mare decat len, se returneaza -1 ceea ce semnaleaza
in main ca trebuie apelata functia add_last (asa este tratat cazul in care se da un index prea
mare). Urmeaza alocarea/realocarea memoriei la exactitate si mutarea octetilor aflati dupa indexul
unde vrem sa inseram noul element la dreapta cu lungimea acestui nou element si sunt introdusi
octetii lui la adresa gasita dupa parcurgere.

3 - find

    Este aplicat un proces similar cu functia anterioara de parcurgere pana la indexul dat, acest
fiind urmat de copierea datelor in elemente auxiliare si afisarea lor in formatul cerut.

4 - delete_at

    Acelasi proces este aplicat pentru determinarea adresei elementului de la indexul dorit.
Se determina lungimea elementului de eliminat si se aloca memorie pentru un vector generic auxiliar
pentru a copia datele pana la si dupa elementul ce va fi sters. Ulterior, vectorul arr este realocat
si datele din vectorul auxiliar sunt copiate in el.

5 - print

    Din nou, este aplicata parcurgerea lui arr cu un header si memorarea datelor in variabile
auxiliare. La fiecare pas ne folosim de proprietati precum castul lui arr la char pentru a extrage
rapid numele celor doi corespondenti in dedicatii si datele din header pentru bancnote, urmand sa
fie afisate in formatul cerut.

6 - exit

    Daca este citit acest input, loop-ul se opreste si se trece la dezalocarea memoriei.

7 - memory management

    Toate structurile si sirurile de caractere au fost alocate dinamic si eliberate odata ce nu a
mai fost nevoie de ele, toate testele fiind parcurse fara erori in valgrind.

Concluzie:
    Tema rezolvata corect, dar nu foarte elegant. Pentru problema bacnotelor de mai multe tipuri,
as fi putut sa consider castarea de la int la ce trebuie, ceea ce ar fi dus la if-uri mai mici,
dar la fel de multe. Solutia finala, prezentata acum, a fost initial temporara, am cazut oarecum
in plasa proverbului "Temporary solutions often become permanent problems". Ideea mea initiala
era sa declar variabile de tipul corespunzator cu if-uri, ceea ce nu se poate, apoi am incercat
cu genericitate si #define-uri in if-uri, ceea ce iar nu merge. Motiv pentru care am ajuns la asta.
Cam atat, dedic acest readme lui Bella, cel mai top caine.

Update: si mai putin elegant