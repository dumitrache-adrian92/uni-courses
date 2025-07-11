# Fusion

1) Care este o eroare valida de ERC in Fusion?

a. suprapunerea a 2 trace-uri cu semnale diferite pe pcb <- eroare de drc

b. incalcarea layer-ului de keep out <- warning, nu eroare

c. rutarea inafara layer-ului de dimension <- eroare de drc

d. pin de alimentare care nu este legat la VCC <- corect pentru ca ERC

2) Pentru ce este folosit un vias fence?

a. Izolarea unei linii de inalta frecventa <- corect

b. Legare la masa a sursei de alimentare <- cplm

c. Face ca electronii sa nu iasa din perimetrul PCB-ului <- la misto

d. Toate variantele <- salut

3) Pe ce ne putem pune componente?

a. doar Top

b. doar bottom

c. top si bottom <- corect

d. silkscreen

# Git

1) Pe branchul master exista 11111 si 22222 atat remote cat si local. Local a fost adaugat 33333 si 44444, dar nu au fost inca upstream-uite.
Unul dintre maintaineri mai adauga comitul 55555 pe remote.
Care va fi ordinea commiturilor locala dupa ce se ruleaza comanda `git pull --rebase`? (primul commit este ultimul adaugat si nu exista conflicte)

Raspuns: 44444, 33333, 55555, 22222, 11111

2) Este rulata comanda git bisect --binary-search pe ultimele 9 commit-uri, care este numarul maxim de git bisect pentru a gasi commit-ul care nu merge?
Raspuns: 3

3) Cum modifici mesajul unui commit?
--amend

4) Ce face `git --rebase`?

# Unit testing 1

1) Care marker ne ajuta sa validam ca un test o sa esueze?

a. skip

b. parametrize

c. custom

d. xFail <- corect

2) Care dintre urmatoarele moduri de testare este de tipul white box? (am acces la cod si docs)

a. testarea unitara             <- corect

b. testarea sistemului

c. testare beta

d. testare statica

# Unit testing 2

1) Care este diferenta principala dintre un mock si un fake?

a. Un fake ofera abilitatea de a urmari apelurile functiilor spre deosebire de mock

b. Un fake contine date si rezultate statice ce nu pot fi modificate                    <- corect

c. Un mock ofera abilitatea de a urmari apelurile functiilor spre deosebire de fake

d. Nu exista diferenta

# CI/CD and Documentation

1) Unde sunt puse fisierele de configurare pentru GitHub actions?

a. github/actions

b. git/actions

c. git/workflows

d. github/workflows <- corect

2) Cum poate fi configurat un pipeline de GitHub actions?

a. la fiecare commit

b. fiecare pull request

c. pentru crearea unui tag nou

d. toate variantele <- corect

# Integration testing

1) Care dintre urmatoarele strategii de testare de integrare sunt de tip incremental?

a. bottom-up, big bang

b. bottom-down, bottom-up, big bang

c. big bang

d. bottom-up, bottom-down, mixed     <- corect

# Regression, system and fuzz testing

1) Ce face un fuzzer?

a. Face codul pufos

b. Transforma o conditie binara intr-o conditie cu proportie de adevar <- corect

c. Genereaza automat input gresit <- corect

d. Ajuta la testarea securitatii unui sistem <- corect

# Static checking

1) Cand ar trebui sa realizam verificari ale calitatii codului?

a. La fiecare salvare a fisierului

b. Inainte de fiecare commit

c. Inainte de fiecare push

d. Toate cele de sus <- corect
