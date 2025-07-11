#include <stdio.h>

void dec_to_bin (int n, char *s);
int bin_to_dec (char *s);
void transpusa (int A[][8], int AT[][8]);
void inmultireMatrice (int A[][8], int B[][8], int C[][8]);
int sum_X_0 (int m[][8]);
void afisareMatriceZecimal (int a[][8]);

int main() {
	//AT=A transpusa; AAT=A*A transpusa; AA=A*A
	int A[8][8], AT[8][8], AAT[8][8], AA[8][8], x, i, j;
	char s[9];
	//citire valori si convertire in baza 2 pentru determinarea matricei A
	for (i=0; i<8; i++) {
		scanf ("%d", &x);
		dec_to_bin (x, s);
		for (j=0; j<8; j++)
			A[i][j]=s[j]-'0';
	}
	//determinare celelalte matrice
	transpusa (A, AT);
	inmultireMatrice (A, AT, AAT);
	inmultireMatrice (A, A, AA);
	//determinare maxim de puncte dintre cele 3 matrice si afisare in baza 10
	if (sum_X_0 (A)>=sum_X_0 (AAT))
		if (sum_X_0 (A)>=sum_X_0 (AA))
			afisareMatriceZecimal (A);
		else
			afisareMatriceZecimal (AA);
	else if (sum_X_0 (AAT)>=sum_X_0 (AA))
			afisareMatriceZecimal (AAT);
		else
			afisareMatriceZecimal (AA);
	return 0;
}

/*primeste ca parametru de intrare un numar n care este convertit in baza 2 in
format de 8 biti si memorat ca sir de caractere in parametrul s*/
void dec_to_bin (int n, char *s) {
	s[8]='\0';
	for (int i=7; i>=0; i--) {
		s[i]='0'+n%2; // n%2=0 sau 1, deci s[i]='0' sau '1'
		n=n/2;
	}
}

/*primeste ca parametru de intrare un sir de caractere ce reprezinta un numar
scris in baza 2 si returneaza valoarea numarului in baza 10*/
int bin_to_dec(char *s) {
	int dec, pow;
	dec=0;
	pow=1;
	for (int i=7; i>=0; i--) {
		dec+=pow*(s[i]-'0');
		pow*=2;
	}
	return dec;
}

/*primeste ca parametru de intrare doua matrice patratice 8x8, A si B, pe care
le inmulteste conform logicii booleene, rezultatul fiind memorat in matricea C
data ca parametru de intrare*/
void inmultireMatrice (int A[][8], int B[][8], int C[][8]) {
	for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
        {
            C[i][j]=0;
            for (int k=0; k<8; k++)
				/*operatorii || si && sunt echivalenti cu + si * din logica
				booleana asa ca folosim expresii pentru a calcula elementele
				matricei*/
				C[i][j]=(C[i][j] || (A[i][k] && B[k][j]));
        }
    }
}

/*primeste matricea 8x8 A ca parametru de intrare si determina transpusa
ei in matricea AT*/
void transpusa (int A[][8], int AT[][8]) {
	for (int i=0; i<8; i++)
		for (int j=0; j<8; j++)
			AT[j][i]=A[i][j];
}

/*returneaza numarul de puncte al unei matrice 8x8 primite ca parametru de
intrare prin intermediul m, acest lucru este realizat prin parcurgerea fiecarui
patrat 4x4 pe linii, coloane si diagonale si incrementarea unei variabile
pentru fiecare dintre acestea ce este formata doar din 1*/
int sum_X_0 (int m[][8]) {
	/*de fiecare data cand parcurgem o noua linie/coloana/diagonala,
	presupunem ca aceasta este completa (ok=1) pana dovedim opusul (ok=0)*/
	int ok, i, j, scor;
	scor=0;
	//patrat stanga sus
	//linii
	for (i=0; i<4; i++) {
		ok=1;
		for (j=0; j<4; j++)
			if (m[i][j]!=1)
				ok=0;
		scor+=ok;
	}
	//coloane
	for (j=0; j<4; j++) {
		ok=1;
		for (i=0; i<4; i++)
			if (m[i][j]!=1)
				ok=0;
		scor+=ok;
	}
	//diagonala principala
	ok=1;
	for (i=0; i<4; i++)
		if(m[i][i]!=1)
			ok=0;
	scor+=ok;
	//diagonala secundara
	ok=1;
	for (i=0; i<4; i++)
		if (m[i][3-i]!=1)
			ok=0;
	scor+=ok;

	//patrat dreapta sus
	//linii
	for (i=0; i<4; i++) {
		ok=1;
		for (j=4; j<8; j++)
			if (m[i][j]!=1)
				ok=0;
		scor+=ok;
	}
	//coloane
	for (j=4; j<8; j++) {
		ok=1;
		for (i=0; i<4; i++)
			if (m[i][j]!=1)
				ok=0;
		scor+=ok;
	}
	//diagonala principala
	ok=1;
	for (i=0; i<4; i++)
		if(m[i][i+4]!=1)
			ok=0;
	scor+=ok;
	//diagonala secundara
	ok=1;
	for (i=0; i<4; i++)
		if (m[i][7-i]!=1)
			ok=0;
	scor+=ok;

	//patrat stanga jos
	//linii
	for (i=4; i<8; i++) {
		ok=1;
		for (j=0; j<4; j++)
			if (m[i][j]!=1)
				ok=0;
		scor+=ok;
	}
	//coloane
	for (j=0; j<4; j++) {
		ok=1;
		for (i=4; i<8; i++)
			if (m[i][j]!=1)
				ok=0;
		scor+=ok;
	}
	//diagonala principala
	ok=1;
	for (i=4; i<8; i++)
		if(m[i][i-4]!=1)
			ok=0;
	scor+=ok;
	//diagonala secundara
	ok=1;
	for (i=4; i<8; i++)
		if (m[i][7-i]!=1)
			ok=0;
	scor+=ok;

	//patrat dreapta jos
	//linii
	for (i=4; i<8; i++) {
		ok=1;
		for (j=4; j<8; j++)
			if (m[i][j]!=1)
				ok=0;
		scor+=ok;
	}
	//coloane
	for (j=4; j<8; j++) {
		ok=1;
		for (i=4; i<8; i++)
			if (m[i][j]!=1)
				ok=0;
		scor+=ok;
	}
	//diagonala principala
	ok=1;
	for (i=4; i<8; i++)
		if(m[i][i]!=1)
			ok=0;
	scor+=ok;
	//diagonala secundara
	ok=1;
	for (i=4; i<8; i++)
		if (m[i][11-i]!=1)
			ok=0;
	scor+=ok;
	return scor;
}

/*converteste liniile matricei a primite ca parametru de intrare din baza 2 in
in baza 10 si le afiseaza*/
void afisareMatriceZecimal (int a[][8]) {
	char s[9];
	s[8]='\0';
	for (int i=0; i<8; i++) {
		for (int j=0; j<8; j++)
			s[j]='0'+a[i][j];
		printf ("%d\n", bin_to_dec(s));
	}
}