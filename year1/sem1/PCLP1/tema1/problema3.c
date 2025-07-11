#include <stdio.h>
#include <string.h>

void citireFata (int a[][3], char culori[][11]);
void copiereFata (int copie[][3], int a[][3]);
void rotireClockwise (int a[][3]);
void rotireAntiClockwise (int a[][3]);
void clockwiseF (int cub[][3][3]);
void antiClockwiseF (int cub[][3][3]);
void clockwiseB (int cub[][3][3]);
void antiClockwiseB (int cub[][3][3]);
void clockwiseU (int cub[][3][3]);
void antiClockwiseU (int cub[][3][3]);
void clockwiseD (int cub[][3][3]);
void antiClockwiseD (int cub[][3][3]);
void clockwiseR (int cub[][3][3]);
void antiClockwiseR (int cub[][3][3]);
void clockwiseL (int cub[][3][3]);
void antiClockwiseL (int cub[][3][3]);
void afisare (int cub[][3][3], char culori[][11]);

int main() {
	/*folosim o matrice de caractere pentru a memora numele celor 6 culori cat
	si pentru a le conferi o numerotare ce ne va ajuta in reprezentare cubului
	rubik*/
	char culori[6][11], mutare[3];
	/*cubul rubik este reprezentat printr-un tablou tridimensional, astfel
	putem reprezenta cele 6 fete ale cubului, fiecare cu 3 linii si 3 coloane,
	unde valoarea fiecarui element=x reprezinta culoarea culori[x];
	pentru ordinea fetelor este folosita cea din enunt: F B U D L R*/
	int cub[6][3][3], m, i;
	for (i=0; i<=5; i++)
		scanf ("%s", culori[i]);
	/*citim fiecare fata a cubului si memoram fata convertita numeric in
	structura de cub*/
	for (i=0; i<=5; i++)
		citireFata (cub[i], culori);
	scanf ("%d", &m);
	for (i=0; i<m; i++) {
		scanf ("%s", mutare);
		switch (mutare[0]) {
			case 'F':
				if (mutare[1]=='\0')
					clockwiseF (cub);
				else
					antiClockwiseF (cub);
				break;
			case 'B':
				if (mutare[1]=='\0')
					clockwiseB (cub);
				else
					antiClockwiseB (cub);
				break;
			case 'U':
				if (mutare[1]=='\0')
					clockwiseU (cub);
				else
					antiClockwiseU (cub);
				break;
			case 'D':
				if (mutare[1]=='\0')
					clockwiseD (cub);
				else
					antiClockwiseD (cub);
				break;
			case 'R':
				if (mutare[1]=='\0')
					clockwiseR (cub);
				else
					antiClockwiseR (cub);
				break;
			case 'L':
				if (mutare[1]=='\0')
					clockwiseL (cub);
				else
					antiClockwiseL (cub);
				break;
		}
	}
	afisare (cub, culori);
	return 0;
}

/*functia citeste si converteste cele trei siruri oferite ca date de intrare,
reprezentand liniile unei fete ale cubului, intr-un format numeric ce este
memorat in structura de cub din cadrul careia primeste ca parametru de intrare
doar una dintre fete*/
void citireFata (int a[][3], char culori[][11]) {
	char linie[33], *p;
	int i, j, k;
	for (i=0; i<=2; i++) {
		scanf ("%s", linie);
		//folosim strtok pentru a separa culoriile din sirul de caractere
		p=strtok (linie, ".");
		for (j=0; j<3; j++) {
			k=0;
			//cautam indicele culorii gasite
			while (strcmp (p, culori[k])!=0)
				k++;
			a[i][j]=k;
			p=strtok (NULL, ".");
		}
	}
}

//copiaza matricea a primita ca parametru de intrare in alta matrice
void copiereFata (int copie[][3], int a[][3]) {
	for (int i=0; i<=2; i++)
		for (int j=0; j<=2; j++)
			copie[i][j]=a[i][j];
}

/*roteste o matrice primita ca parametru de intrare 90 de grade in sensul
acelor de ceasornic*/
void rotireClockwise (int a[][3]) {
	int copie[3][3], i, j;
	copiereFata (copie, a);
	for (j=0; j<=2; j++)
		for (i=2; i>=0; i--)
			a[j][2-i]=copie[i][j];
}

/*roteste o matrice primita ca parametru de intrare 90 de grade in sens
trigonometric*/
void rotireAntiClockwise (int a[][3]) {
	int copie[3][3], i, j;
	copiereFata (copie, a);
	for (j=0; j<=2; j++)
		for (i=2; i>=0; i--)
			a[i][j]=copie[j][2-i];
}

/*despre toate mutarile: pentru fiecare mutare avem o fata principala, dupa
care este numita mutarea, pe care o rotim 90 de grade in sensul acelor de
ceasornic sau trigonometric si 4 alte fete vecine cu cea principala pe care
le-am notat in comentarii sus, dreapta, jos si stanga care schimba valorile
vecine cu fata principala intre ele, modul in care acestea se schimba difera
in functie de mutare si este notat in cadrul fiecarei functii*/
void clockwiseF (int cub[][3][3]) {
	//sus
	int aux[3]={cub[2][2][0], cub[2][2][1], cub[2][2][2]}, i;
	rotireClockwise (cub[0]);
	//sus=stanga
	for (i=0; i<=2; i++)
		cub[2][2][i]=cub[4][2-i][2];
	//stanga=jos
	for (i=0; i<=2; i++)
		cub[4][i][2]=cub[3][0][i];
	//jos=dreapta
	for (i=0; i<=2; i++)
		cub[3][0][i]=cub[5][2-i][0];
	//dreapta=aux (sus)
	for (i=0; i<=2; i++)
		cub[5][i][0]=aux[i];
}

void antiClockwiseF (int cub[][3][3]) {
	//sus
	int aux[3]={cub[2][2][0], cub[2][2][1], cub[2][2][2]}, i;
	rotireAntiClockwise (cub[0]);
	//sus=dreapta
	for (i=0; i<=2; i++)
		cub[2][2][i]=cub[5][i][0];
	//dreapta=jos
	for (i=0; i<=2; i++)
		cub[5][i][0]=cub[3][0][2-i];
	//jos=stanga
	for (i=0; i<=2; i++)
		cub[3][0][i]=cub[4][i][2];
	//stanga=aux (sus)
	for (i=0; i<=2; i++)
		cub[4][i][2]=aux[2-i];
}

void clockwiseB (int cub[][3][3]) {
	//sus
	int aux[3]={cub[2][0][0], cub[2][0][1], cub[2][0][2]}, i;
	rotireClockwise (cub[1]);
	//sus=stanga
	for (i=0; i<=2; i++)
		cub[2][0][i]=cub[5][i][2];
	//stanga=jos
	for (i=0; i<=2; i++)
		cub[5][i][2]=cub[3][2][2-i];
	//jos=dreapta
	for (i=0; i<=2; i++)
		cub[3][2][i]=cub[4][i][0];
	//dreapta=aux (sus)
	for (i=0; i<=2; i++)
		cub[4][i][0]=aux[2-i];
}

void antiClockwiseB (int cub[][3][3]) {
	//sus
	int aux[3]={cub[2][0][0], cub[2][0][1], cub[2][0][2]}, i;
	rotireAntiClockwise (cub[1]);
	//sus=dreapta
	for (i=0; i<=2; i++)
		cub[2][0][i]=cub[4][2-i][0];
	//dreapta=jos
	for (i=0; i<=2; i++)
		cub[4][i][0]=cub[3][2][i];
	//jos=stanga
	for (i=0; i<=2; i++)
		cub[3][2][i]=cub[5][2-i][2];
	//stanga=aux (sus)
	for (i=0; i<=2; i++)
		cub[5][i][2]=aux[i];
}

void clockwiseU (int cub[][3][3]) {
	//sus
	int aux[3]={cub[1][0][0], cub[1][0][1], cub[1][0][2]}, i;
	rotireClockwise (cub[2]);
	//sus=stanga
	for (i=0; i<=2; i++)
		cub[1][0][i]=cub[4][0][i];
	//stanga=jos
	for (i=0; i<=2; i++)
		cub[4][0][i]=cub[0][0][i];
	//jos=dreapta
	for (i=0; i<=2; i++)
		cub[0][0][i]=cub[5][0][i];
	//dreapta=aux (sus)
	for (i=0; i<=2; i++)
		cub[5][0][i]=aux[i];
}

void antiClockwiseU (int cub[][3][3]) {
	//sus
	int aux[3]={cub[1][0][0], cub[1][0][1], cub[1][0][2]}, i;
	rotireAntiClockwise (cub[2]);
	//sus=dreapta
	for (i=0; i<=2; i++)
		cub[1][0][i]=cub[5][0][i];
	//dreapta=jos
	for (i=0; i<=2; i++)
		cub[5][0][i]=cub[0][0][i];
	//jos=stanga
	for (i=0; i<=2; i++)
		cub[0][0][i]=cub[4][0][i];
	//stanga=aux (sus)
	for (i=0; i<=2; i++)
		cub[4][0][i]=aux[i];
}

void clockwiseD (int cub[][3][3]) {
	//sus
	int aux[3]={cub[0][2][0], cub[0][2][1], cub[0][2][2]}, i;
	rotireClockwise (cub[3]);
	//sus=stanga
	for (i=0; i<=2; i++)
		cub[0][2][i]=cub[4][2][i];
	//stanga=jos
	for (i=0; i<=2; i++)
		cub[4][2][i]=cub[1][2][i];
	//jos=dreapta
	for (i=0; i<=2; i++)
		cub[1][2][i]=cub[5][2][i];
	//dreapta=aux (sus)
	for (i=0; i<=2; i++)
		cub[5][2][i]=aux[i];
}

void antiClockwiseD (int cub[][3][3]) {
	//sus
	int aux[3]={cub[0][2][0], cub[0][2][1], cub[0][2][2]}, i;
	rotireAntiClockwise (cub[3]);
	//sus=dreapta
	for (i=0; i<=2; i++)
		cub[0][2][i]=cub[5][2][i];
	//dreapta=jos
	for (i=0; i<=2; i++)
		cub[5][2][i]=cub[1][2][i];
	//jos=stanga
	for (i=0; i<=2; i++)
		cub[1][2][i]=cub[4][2][i];
	//stanga=aux (sus)
	for (i=0; i<=2; i++)
		cub[4][2][i]=aux[i];
}

void clockwiseR (int cub[][3][3]) {
	//sus
	int aux[3]={cub[2][0][2], cub[2][1][2], cub[2][2][2]}, i;
	rotireClockwise (cub[5]);
	//sus=stanga
	for (i=0; i<=2; i++)
		cub[2][i][2]=cub[0][i][2];
	//stanga=jos
	for (i=0; i<=2; i++)
		cub[0][i][2]=cub[3][i][2];
	//jos=dreapta
	for (i=0; i<=2; i++)
		cub[3][i][2]=cub[1][2-i][0];
	//dreapta=aux (sus)
	for (i=0; i<=2; i++)
		cub[1][i][0]=aux[2-i];
}

void antiClockwiseR (int cub[][3][3]) {
	//sus
	int aux[3]={cub[2][0][2], cub[2][1][2], cub[2][2][2]}, i;
	rotireAntiClockwise (cub[5]);
	//sus=dreapta
	for (i=0; i<=2; i++)
		cub[2][i][2]=cub[1][2-i][0];
	//dreapta=jos
	for (i=0; i<=2; i++)
		cub[1][i][0]=cub[3][2-i][2];
	//jos=stanga
	for (i=0; i<=2; i++)
		cub[3][i][2]=cub[0][i][2];
	//stanga=aux (sus)
	for (i=0; i<=2; i++)
		cub[0][i][2]=aux[i];
}

void clockwiseL (int cub[][3][3]) {
	//sus
	int aux[3]={cub[2][0][0], cub[2][1][0], cub[2][2][0]}, i;
	rotireClockwise (cub[4]);
	//sus=stanga
	for (i=0; i<=2; i++)
		cub[2][i][0]=cub[1][2-i][2];
	//stanga=jos
	for (i=0; i<=2; i++)
		cub[1][i][2]=cub[3][2-i][0];
	//jos=dreapta
	for (i=0; i<=2; i++)
		cub[3][i][0]=cub[0][i][0];
	//dreapta=aux (sus)
	for (i=0; i<=2; i++)
		cub[0][i][0]=aux[i];
}

void antiClockwiseL (int cub[][3][3]) {
	//sus
	int aux[3]={cub[2][0][0], cub[2][1][0], cub[2][2][0]}, i;
	rotireAntiClockwise (cub[4]);
	//sus=dreapta
	for (i=0; i<=2; i++)
		cub[2][i][0]=cub[0][i][0];
	//dreapta=jos
	for (i=0; i<=2; i++)
		cub[0][i][0]=cub[3][i][0];
	//jos=stanga
	for (i=0; i<=2; i++)
		cub[3][i][0]=cub[1][2-i][2];
	//stanga=aux (sus)
	for (i=0; i<=2; i++)
		cub[1][i][2]=aux[2-i];
}

/*converteste liniile cubului rubik din formatul numeric in cel folosit in
cerinta si le afiseaza*/
void afisare (int cub[][3][3], char culori[][11]) {
	int i, j, k;
	char s[33];
	for (i=0; i<=5; i++)
		for (j=0; j<=2; j++) {
			strcpy (s, culori [cub[i][j][0]]);
			for (k=1; k<=2; k++) {
				strcat (s, ".");
				strcat (s, culori[cub[i][j][k]]);
			}
			puts (s);
		}
}