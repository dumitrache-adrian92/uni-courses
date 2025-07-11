#include "biju.h"
#include <ncurses.h>
#include <menu.h>

/*afiseaza sirul de caractere primit in input in centrul liniei primite ca
  parametru aflate in fereastra primita tot ca parametru*/
void printCentrat(WINDOW *win, int linie, char *input) {
    mvwprintw(win, linie, (getmaxx(win) - strlen(input)) / 2, "%s", input);
}

/*determina codul culorii pentru fundal cat si pentru text din html-ul primit
  ca parametru de intrare si le transmite prin celelalte 2 variabile
  note: codurile sunt cele folosite in enum-ul din biju.h*/
void color(char *html, int *bgColor, int *color) {
    //declaram un sir de caractere in care o sa facem o copie a html-ului
    char *aux;
    aux = malloc(strlen(html) + 1);
    //verificam daca exista tag p stilizat
    char *p = strstr(html, "<p style=\"");
    //daca da extragem culorile din el, in caz contrar le punem pe cele default
    if (p != NULL) {
        //copiam in aux pentru a nu modifica html-ul in memorie
        strcpy(aux, p);
        /*cautam sfarsitul tagului <p> si il delimitam de restul sirului
          pentru a evita cazurile haotice in care cineva creaza un site in care
          apare secventa "background-color" :) */
        p = strchr(aux, '>');
        aux[p - aux + 1] = '\0';
        /*verificam daca e declarat background-color, daca da,
          determinam culoarea, altfel punem culoarea default*/
        p = strstr(aux, "background-color:");
        if (p != NULL) {
            //stergem "background-color:"
            strcpy(p, p+17);
            /*cautam culoarea care se afla pe prima pozitie a lui p si o
              stergem pentru a usura determinarea culorii de font*/
            if (strstr(p, "white")==p) {
                *bgColor = 7;
                strcpy(p, p+5);
            }
            else if (strstr(p, "black")==p) {
                *bgColor = 0;
                strcpy(p, p+5);
            }
            else if (strstr(p, "red")==p) {
                *bgColor = 1;
                strcpy(p, p+3);
            }
            else if (strstr(p, "green")==p) {
                *bgColor = 2;
                strcpy(p, p+5);
            }
            else if (strstr(p, "blue")==p) {
                *bgColor = 4;
                strcpy(p, p+4);
            }
            else if (strstr(p, "yellow")==p) {
                *bgColor = 3;
                strcpy(p, p+6);
            }
        }
        else
            *bgColor = 7; //alb default
        /*verificam daca e specificata culoarea fontului, de data asta e mai
          simplu fiindca am eliminat posibilitatea de a avea background-color
          mentionat, lucru care putea cauza inversarea culorilor*/
        p = strstr(aux, "color:");
        if (p != NULL) {
            if (strstr(p, "white"))
                *color = 7;
            else if (strstr(p, "black"))
                *color = 0;
            else if (strstr(p, "red"))
                *color = 1;
            else if (strstr(p, "green"))
                *color = 2;
            else if (strstr(p, "blue"))
                *color = 4;
            else if (strstr(p, "yellow"))
                *color = 3;
        }
        else
            *color = 0; //negru default
    } else {
        *bgColor = 7;
        *color = 0;
    }
    //eliberare memorie
    free(aux);
}

int main() {
    int i;
    //initializare ncurses
    initscr();
    cbreak();
    noecho();
    start_color();
    keypad(stdscr, TRUE);
    /*fereastra care va fi folosita pentru a afisa tastele ce pot fi folosite
      in meniul curent*/
    WINDOW *legenda = newwin(2, getmaxx(stdscr), getmaxy(stdscr) - 2, 0);
    //fereastra pentru bara de cautare
    WINDOW *searchBar = newwin(3, getmaxx(stdscr) / 2,
                               getmaxy(stdscr) / 2 + 2, getmaxx(stdscr) / 4);
    printCentrat(stdscr, getmaxy(stdscr) / 2 - 2, "Biju Browser");
    printCentrat(legenda, 0, "C - Cautare   Q - Inchide");
    refresh();
    wrefresh(legenda);
    //primul input care duce la meniul search bar sau inchide programul
    char c, input[100], copieInput[100];
    do
        c = wgetch(legenda);
    while (c != 'q' && c != 'Q' && c != 'c' && c != 'C');
    if (c == 'q' || c == 'Q') {
        endwin();
        return 0;
    }
    //punct de intoarce pentru pagina de rezultate
    cautare:
    //afisam meniul de cautare
    wclear(legenda);
    /*dam clear la search bar fara a avea ceva initializat in el pentru ca ne
      vom intoarce aici la un moment dat si nu vrem sa avem inputul vechi
      ramas in el*/
    wclear(searchBar);
    printCentrat(legenda, 0, "Enter - Cauta");
    wrefresh(legenda);
    box(searchBar, 0, 0);
    wmove(searchBar, 1, 2);
    printCentrat(stdscr, getmaxy(stdscr) / 2 - 2, "Biju Browser");
    refresh();
    wrefresh(searchBar);
    echo();
    //luam un string ca input din search bar
    wgetstr(searchBar, input);
    noecho();
    wclear(legenda);
    printCentrat(legenda, 0,
                 "S - Cautare Simpla     A - Cautare Avansata    Q - Inchide");
    wrefresh(legenda);
    //input pentru cautare, cautare avansata si inchidere program
    do
        c = wgetch(legenda);
    while (c != 'q' && c != 'Q' && c != 's' && c != 'S' &&
        c != 'a' && c != 'A');
    //incarcam baza de date cu site-uri
    site *bijuNet;
    int nrSiteuri;
    citireMaster(&bijuNet, &nrSiteuri);
    //vectorul pentru indexii rezultatelor
    int *filtrate, n;
    filtrate = malloc(10 * sizeof(int));
    /*copiam inputul pentru ca am avut nevoie de el
      mai tarziu si l-am modificat la un moment dat*/
    strcpy(copieInput, input);
    if (c == 's' || c == 'S') {
        cautare(filtrate, &n, bijuNet, nrSiteuri, input);
        sort(comparatieTask2, filtrate, bijuNet, n);
    } else if (c == 'a' || c == 'A') {
        cautareAvansata(filtrate, &n, bijuNet, nrSiteuri, input);
        sort(comparatieTask3, filtrate, bijuNet, n);
    } else {
        endwin();
        return 0;
    }
    //initializam un meniu si o fereastra dedicata meniului
    WINDOW *meniuW;
    ITEM **optiuni;
    MENU *meniu;
    meniuW = newwin(getmaxy(stdscr) / 2, getmaxx(stdscr) / 2,
                    getmaxy(stdscr) / 4, getmaxx(stdscr) / 4);
    keypad(meniuW, TRUE);
    //introducem rezultatele in **optiuni si le introducem in meniu
    optiuni = calloc(n + 1, sizeof(ITEM *));
    for (i = 0; i < n; i++)
        optiuni[i] = new_item(bijuNet[filtrate[i]].titlu,
                                bijuNet[filtrate[i]].url);
    optiuni[n + 1] = (ITEM *)NULL;
    meniu = new_menu(optiuni);
    //setari meniu
    set_menu_mark(meniu, " > ");
    set_menu_win(meniu, meniuW);
    set_menu_sub(meniu, derwin(meniuW, getmaxy(stdscr) / 2 - 4,
                                    getmaxx(stdscr) / 2 - 4, 2, 3));
    set_menu_format(meniu, 5, 1);
    //punct de intoarcere pentru pagina de site
    meniu:
    //afisam pagina de rezultate
    box(meniuW, 0, 0);
    wclear(legenda);
    printCentrat(legenda, 0, "Enter - Deschide      B - Inapoi      Q - Inchide");
    wrefresh(legenda);
    printCentrat(stdscr, getmaxy(stdscr) / 8 - 1, "Search Input:");
    printCentrat(stdscr, getmaxy(stdscr) / 8, copieInput);
    refresh();
    post_menu(meniu);
    wrefresh(meniuW);
    int key;
    /*input pentru selectare site, intoarcere la pagina de cautare
      sau inchidere program*/
    key = wgetch(meniuW);
    while (key != '\n' && key != 'b' && key != 'B' && key != 'q' && key != 'Q') {
        switch (key) {
        case KEY_DOWN:
            menu_driver(meniu, REQ_DOWN_ITEM);
            break;
        case KEY_UP:
            menu_driver(meniu, REQ_UP_ITEM);
            break;
        case KEY_NPAGE:
			menu_driver(meniu, REQ_SCR_DPAGE);
			break;
		case KEY_PPAGE:
			menu_driver(meniu, REQ_SCR_UPAGE);
			break;
        }
        wrefresh(meniuW);
        key = wgetch(meniuW);
    }
    if (key == 'q' || key == 'Q') {
        endwin();
        return 0;
    } else if (key == 'b' || key == 'B') {
        wclear(meniuW);
        wrefresh(meniuW);
        clear();
        goto cautare;
    }
    //inchidere meniu
    unpost_menu(meniu);
    clear();
    //afisare titlu site in bold
    attron(A_BOLD);
    printCentrat(stdscr, 0, bijuNet[filtrate[current_item(meniu)->index]].titlu);
    attroff(A_BOLD);
    //determinare culoarea fundal si font
    int bg, fg;
    color(bijuNet[filtrate[current_item(meniu)->index]].html, &bg, &fg);
    culoare bgC = (culoare)bg, fgC = (culoare)fg;
    init_pair(1, fgC, bgC);
    attron(COLOR_PAIR(1));
    //afisare pagina site
    mvprintw(1, 0, "%s", bijuNet[filtrate[current_item(meniu)->index]].continut);
    attroff(COLOR_PAIR(1));
    refresh();
    printCentrat(legenda, 0, "B - Inapoi      Q - Inchide");
    wrefresh(legenda);
    //input pentru intoarcere la pagina de rezultate sau inchidere program
    key = wgetch(meniuW);
    while (key != 'b' && key != 'B' && key != 'q' && key != 'Q') {
        switch (key) {
        case KEY_DOWN:
            menu_driver(meniu, REQ_DOWN_ITEM);
            break;
        case KEY_UP:
            menu_driver(meniu, REQ_UP_ITEM);
            break;
        }
        wrefresh(meniuW);
        key = wgetch(meniuW);
    }
    if (key == 'q' || key == 'Q') {
        endwin();
        return 0;
    } else if (key == 'b' || key == 'B') {
        clear();
        refresh();
        goto meniu;
    }
    //eliberare memorie
    for (i = 0; i < n + 1; i++)
        free_item(optiuni[i]);
    free_menu(meniu);
    endwin();
    for (i = 0; i < nrSiteuri; i++) {
        free(bijuNet[i].continut);
        free(bijuNet[i].html);
    }
    free(bijuNet);
    free(filtrate);
    return 0;
}
