#include <stdio.h>

int abs (int x);
int nrAtac (int nebuni[][2], int N);
void cautaPerechea (int nebuni[][2], int N, int *x, int *y);
int mutari (int nebuni[][2], int tabla[][100], int N, int M, int a);

int main() {
	int M, N, i, totalAtac, x, y;
	scanf ("%d", &M);
	scanf ("%d", &N);
	/*matricea nebuni reprezinta linia=nebuni[][0] si coloana=nebuni[0][1]
	fiecarui nebun aflat pe tabla de sah, iar matricea tabla reprezinta tabla
	de sah, unde daca tabla[i][j]=1 inseamna ca un nebun exista pe aceea
	pozitie*/
	int nebuni[10000][2], tabla[100][100];
	for (i=0; i<N; i++) {
		scanf ("%d%d", &nebuni[i][0], &nebuni[i][1]);
		tabla[nebuni[i][0]][nebuni[i][1]]=1;
	}
	totalAtac=nrAtac (nebuni, N);
	printf ("%d\n", totalAtac);
	if (totalAtac!=1)
		printf ("NU\n");
	else {
		//determinam care este unica pereche ce se ataca
		cautaPerechea (nebuni, N, &x, &y);
		/*verificam daca exista o posibila mutare pentru unul din nebuni
		astfel incat sa nu se mai atace niciun nebun*/
		if (mutari(nebuni, tabla, N, M, x))
			printf ("DA\n");
		else if (mutari (nebuni, tabla, N, M, y))
			printf ("DA\n");
		else
			printf ("NU\n");
	}
	return 0;
}

//returneaza valoarea absoluta a parametrului de intrare x
int abs (int x) {
	if (x<0)
		return -x;
	else
		return x;
}

/*returneaza numarul de perechi de nebuni aflati in stare de atac folosiind
faptul ca doua piese se afla pe aceeasi diagonala daca valorile absolute a
diferentei dintre coordonatele lor sunt egale*/
int nrAtac (int nebuni[][2], int N) {
	int nr;
	nr=0;
	for (int i=0; i<N-1; i++)
		for (int j=i+1; j<N; j++)
			if (abs (nebuni[i][0]-nebuni[j][0])==
			abs (nebuni[i][1]-nebuni[j][1]))
				nr++;
	return nr;
}

/*scopul functiei este sa salveze indicii primei perechi de nebuni pe care o
gaseste prin cei doi pointeri primiti ca parametrii de intrare x si y,
in cadrul problemei o sa fie apelata doar atunci cand stiim ca avem exact o
pereche de nebuni care se ataca pe toata tabla*/
void cautaPerechea (int nebuni[][2], int N, int *x, int *y) {
	for (int i=0; i<N-1; i++)
		for (int j=i+1; j<N; j++)
			if (abs (nebuni[i][0]-nebuni[j][0])==
			abs (nebuni[i][1]-nebuni[j][1]))
			{
				*x=i;
				*y=j;
				return;
			}
}

/*functia parcurge toate mutarile posibile ale nebunului cu indicele a si
returneaza 1 cand gaseste una pentru care nu mai exista nebuni care se ataca
sau 0 daca au fost parcurse toate mutarile fara sa fie gasita una valida, este
luat in considerare si faptul ca doi nebuni nu se pot afla pe aceeasi pozitie*/
int mutari (int nebuni[][2], int tabla[][100], int N, int M, int a) {
	int cp[2]={nebuni[a][0], nebuni[a][1]};
	for (int i=0; i<M; i++)
		for (int j=0; j<M; j++)
			if (tabla[i][j]!=1)
			{
				nebuni[a][0]=i;
				nebuni[a][1]=j;
				if (nrAtac(nebuni, N)==0)
					return 1;
			}
	nebuni[a][0]=cp[0];
	nebuni[a][1]=cp[1];
	return 0;
}