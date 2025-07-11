# Tema 1 SCD - Adrian-George Dumitrache [342C1]

Noroc, urmeaza sa descriu aceasta solutia mea pentru aceasta tema in detaliu.

## Chestiuni generale

Am rezolvat integral cerinta temei, implementand toate functionalitatile
cerute.

Am folosit `libtirpc` si `rpcgen` pentru generarea codului si compilarea
serverului si clientului, deci `Makefile`-ul foloseste aceste doua tool-uri.
Se pot inlocui cu `lnsl` dupa preferinta.

Am adaugat `\n` la finalul fiecarui ref, permis conform cerintei, pentru a
evita diff-uri banale in checker care ar fi doar de la lipsa newline-ului.

## Interfata RPC

Server-ul expune urmatorul API cu proceduri care intorc structuri continand un
cod de retur si diverse campuri.

Formatul este:

`<(output, ?optional_output, ...)> PROCEDURE_NAME(input1, input2, ...)`:

### API

* `(return_code, ?request_token) REQUEST_AUTHORIZATION(user_id)`
    *  Unde `return_code`:
        * `OK` - daca s-a generat cu succes token-ul, care este returnat in `request_token`
        * `USER_NOT_FOUND` - daca `user_id` nu exista
* `(return_code, ?access_token, ?lifetime, ?refresh_token) REQUEST_ACCESS_TOKEN(request_token, user_id, request_refresh)`
    *  Unde `return_code`:
        * `OK` - daca s-a generat cu succes token-ul, care este returnat in `access_token`
        * `USER_NOT_FOUND` - daca `user_id` nu exista
        * `REQUEST_DENIED` - daca `request_token` nu este semnat
* `(return_code, request_token) APPROVE_REQUEST_TOKEN(request_token)`
    *  Unde `return_code`:
        * `SIGNED` - daca `request_token` a fost semnat
        * `NOT_SIGNED` - daca `request_token` nu a fost semnat
* `(return_code) VALIDATE_DELEGATED_ACTION(user_id, resource, action, action_name, access_token)`
    *  Unde `return_code`:
        * `PERMISSION_GRANTED` - daca actiunea este permisa
        * `OPERATION_NOT_PERMITTED` - daca `access_token` nu are permisiunea necesara
        * `RESOURCE_NOT_FOUND` - daca resursa nu exista
        * `TOKEN_EXPIRED` - daca token-ul a expirat
        * `PERMISSION_DENIED` - daca token-ul nu apartine user-ului
        * `USER_NOT_FOUND` - daca `user_id` nu exista
    * Unde `action`:
        * `READ`
        * `INSERT`
        * `MODIFY`
        * `DELETE`
        * `EXECUTE`
        * `ERROR` (pentru actiuni ce nu exista)

### Server

Server-ul incepe prin a parsa fisierele de intrare si a stoca toate
informatiile in structura principala a serverului: `OauthDatabase`. Aceasta
contine toate informatiile despre useri, tokeni (de cerere, acces si refresh),
resurse si permisiuni, cat si metode ce permit interogarea acestor date si
adaugarea de noi date.

Structura acesteia este un set de permisiuni si unul de useri. Urmand ca tokenii
sa fie asociati userilor, iar permisiunile asociate tokenilor. Managementul
acestor obiecte este facut prin idiome RAII pentru un management al memorie usor.

Cu ajutorul acestei abstractii, implementarile procedurilor expuse de catre
server ajung sa fie foarte simple. In principiu doar apeleaza cateva metode ale
bazei de date pentru a verifica validitatea input-urilor, adauga
noi tokeni/permisiuni in aceasta si returneaza rezultatul, afisand pe parcurs
diverse mesaje de status.

### Client

Implementarea clientului este relativ mai simpla, avand doar cateva structuri de
date simple ce retin asocieri intre utilizatori si diversele tipuri de tokeni +
valabilitatea lor.

Acesta incepe prin parsarea fisierului de intrare, executand fiecare comanda
data. Comenzile sunt impartite in doua categorii:

* `REQUEST`
* `ACTION`

O comanda de tip request duce la 3 apeluri RPC:

1. `REQUEST_AUTHORIZATION` pentru a obtine un token de cerere.
2. `APPROVE_REQUEST_TOKEN` pentru a semna token-ul de cerere.
3. `REQUEST_ACCESS_TOKEN` pentru a obtine un token de acces si, optional, unul
   de refresh.

O comanda de tip action duce la un singur apel RPC: `VALIDATE_DELEGATED_ACTION`,
mai putin in cazurile in care access token-ul folosit pentru aceasta actiune a
expirat si are asociat un refresh token, caz in care se va executa un apel RPC
suplimentar: `REQUEST_ACCESS_TOKEN` pentru a obtine un nou access token
utilizand refresh token-ul.
