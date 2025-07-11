# Algoritmul lui Prim - Tema 1 si 2

## Echipa

- Adrian-George Dumitrache
- Andrei Petrea

## Rulare

Nota: testele pe care le-am folosit sunt destul de mari, motiv pentru care nu
sunt incluse in arhiva. Ele pot fi generate astfel:

```shell
python3 generate_test_suite.py # poate dura destul de mult
```

Testele include grafuri de diverse dimensiuni, intervale de greutati si grade
de densitate.

Compilare si rulare:

```shell
cd Etapa{1,2}
make
make run_{openmp,mpi,pthreads,hybrid_mpi}
```

## Abordare generala

Am pornit de la varianta secventiala din `serial_prim.cpp`. Analizand
algoritmul, se observa ca bucla principala nu poate fi paralelizata, deoarece
fiecare pas depinde de rezultatul pasilor anteriori. Insa, bucla interna, cea
care parcurge vecinii nodului adaugat in arbore, poate fi paralelizata destul
de usor. Paralelizarea acestei bucle ar ajuta in mod special in cazul unui graf
des, in care numarul de noduri adiacente unui nod este foarte mare.

Alta optimizare se poate face la citirea grafului din fisier, utilizand un
thread principal care citeste datele si le trimite catre celelalte threaduri
pentru a le procesa, se poate reduce timpul de citire a datelor. Aceasta abordare
este mai eficienta decat citirea paralela din fisier (fiecare thread e
responsabil de o parte din linii) din motive de disk caching si overhead de
sincronizare.

## OpenMP

Am paralelizat bucla interna utilizand task-uri OpenMP. Motivatia este de a
utiliza task-uri in loc de paradigma clasica fork-join pentru a evita
overhead-ul de creare si distrugere a thread-urilor, lucru ce s-ar intampla la
fiecare pas al buclei principale. Utilizand task-uri, cream thread-urile o
singura data la inceput, iar master-ul creeaza task-urile cand are nevoie.

Similar, am utilizat task-uri pentru a procesa linii citite din fisier in
timp ce thread-ul principal citeste in continuare din fisier.

Rezultatele sunt destul de bune, in special pentru grafuri dense, trecand de
la ~10s la ~2.5s pentru un graf des de 10000 de noduri.

## MPI

Am paralelizat bucla interna distribuind lista de adiacenta a nodului curent
catre toate procesele. Fiecare proces parcurge partea sa a listei de adiacenta
si trimite inapoi catre procesul master nodurile descoperite.

Rezultatele (aproximativ acelasi timp de rulare) ne arata ca problema nu se
preteaza foarte bine la paralelizare folosind MPI, deoarece comunicarea intre
procese este incredibil de costisitoare, fiind nevoiti sa comunicam o cantitate
destul de mare de date la fiecare pas al buclei principale.

Abordari alternative precum comunicarea intregului graf inainte de a incepe
algoritmul si apoi paralelizarea buclei principale nu au dat rezultate mai bune.

## Pthreads

Abordarea este similara cu cea de la OpenMP. Ca inlocuitor pentru task-urile
din OpenMP, am implementat un Thread Pool si am procedat in acelasi fel.

Rezultatele sunt putin mai bune decat la OpenMP (aproximativ 2s pentru un graf
des de 10000 de noduri).

## MPI + OpenMP

Aceasta varianta preia optimizarile facute la OpenMP si le aplica pe MPI. Fiecare
proces MPI paraleliaza partea sa a listei de adiacenta. In plus, am adaptat si
citirea din fisier facuta in OpenMP.

Din pacate, rezultatele nu sunt inspira prea multa incredere, in continuare
programul petrece mult prea mult timp in comunicare.
