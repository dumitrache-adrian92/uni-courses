# Crazyhouse Bot

## Etapa 1

**Echipa**: Address Resolution Protocol

**Membri**:

- Dumitrache Adrian-George
- Ion Vlad-Vasile
- Sandulescu Iulia-Stefania
- Anghel Dragos

### **Instructiuni de compilare**

In terminal, rulati comanda:

```bash
make build
```

Se pot folosi urmatoarele pentru a testa:

```bash
# pentru a juca impotriva botului
xboard -fcp "make run"

# bot vs. bot
xboard -fcp "make run" -scp "make run"
# urmat de setarea modului "Two Machines" in xboard
```

Pentru a sterge toate fisierele generate de Makefile:

```bash
make clean
```

### **Structura proiectului**

In clasa Bot avem parametrii pentru a retine stadiul actual al partidei de sah,
cum ar fi o matrice de perechi de Piece si PlaySide pentru a retine pozitiile
fiecarei piese, vectori pentru a retine ce piese au fost capturate (pentru
drop-in), variabile ce retin daca regii si turele au fost mutate (pentru
rocada), matrice ce marcheaza pozitiile unde se afla piese promovate si ultima
miscare (pentru En Passant). De asemenea, botul are variabile ce reprezinta
directiile de atac ale fiecarei piese pentru a genera usor mutari.

Functia recordMove modifica parametrii legati de stadiul meciului de sah bazat
pe mutarea primita. Aceasta functie merge pentru orice tip de miscare, inclusiv
En Passant, rocada, drop-in, promovare si capturare a unui pion promovat.

Pentru a genera mutarile emise de bot si pentru a ne asigura ca acesta va stii
sa emita o mutare legala intotdeauna (atat timp cat ea chiar exista), botul
genereaza toate mutarile posibile si le pune intr-o coada din care se alege
doar una. Acest lucru este realizat astfel:

1. Generam toate mutarile de tip drop-in.
2. Pentru fiecare piesa de pe tabla, ne folosim de vectorul sau de directie
pentru a genera toate mutarile ce nu ies din tabla, nu sar peste alte piese
(pentru piesele "sliding") si nu aterizeaza peste o piesa de aceeasi culoare.
3. Filtram mutarile astfel incat sa ne asiguram ca nu intram in sah (sau daca
suntem deja, ca iesim din sah), acest lucru este verificat prin a genera toate
mutarile inamicului ca la pasul 2 si a verifica daca vreuna ne poate "captura"
regele.

Pasii acestia asigura o coada cu toate mutarile legale pentru situatia de joc
data. De asemenea, verificam daca este posibila rocada mica/mare si o facem
daca da (pentru ca asta cere cerinta). Verificarea se face prin a vedea daca
n-au fost mutate piesele folosite in rocada (avem variabile speciale pentru
asta), daca sunt libere casutele dintre rege si tura si daca sunt atacate
casutele prin care trece regele (generam toate mutarile inamicului si vedem ce
ataca).

### Abordarea algoritmica

Pentru etapa aceasta nu am folosit vreun algoritm anume, iar ce si cum am
imbinat este descris in sectiunea anterioara. Cat despre complexitate, functia
recordMove este O(1), iar functia calculateNextMove este aproximativ
O(numarul_de_piese_aliate * max_mutari_posibile * numarul_de_piese_inamice *
max_mutari_posibile)

### Surse de inspiratie

- https://alexanderameye.github.io/notes/chess-engine/
- https://peterellisjones.com/posts/generating-legal-chess-moves-efficiently/

### Responsabilitatea membrilor

Nu am impartit de la inceput ce o sa faca fiecare in mod special. Am pus
issue-uri pe GitHub si fiecare a facut ce a vrut. Din amintiri, ne-am ocupat
fiecare de urmatoarele:

1. Dumitrache Adrian-George: reprezentare status meci de sah (as schimba
multe...), functie care verifica daca o mutare duce in sah, rocada mica/mare,
mecanism ca sa se retina ce piese sunt promovate, generare mutari drop-in
2. Ion Vlad-Vasile: reprezentare status meci de sah, vectori directii piese,
generarea tuturor mutarilor standard, tool de debug, debugging care a salvat
proiectul, randomizare miscari ca sa putem testa mai bine
3. Sandulescu Iulia-Stefania: generare mutari promovare, generare mutari
drop-in, en passant, ne-a explicat chestii de sah ca la prosti
4. Anghel Dragos: testat bot, sursa de explicatii pentru sah, propuneri de
abordari