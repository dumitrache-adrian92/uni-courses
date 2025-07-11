#include <stdio.h>
#include <string.h>

int is_anagram (char *s1, char *s2);
double compute_grade (char *s1, char *s2);
void directInsertion (int M, double *grades, char words1[][51],
    char words2[][51], double newGrade, char *newWord1, char *newWord2);

int main() {
	int N, i;
	/*pentru fiecare pereche este memorat gradul acestora in vectorul
	grades in ordine descrescatoare*/
	double grades[1000];
	/*pentru fiecare pereche este memorat primul cuvant in words1 si al doilea
    in words2 sortate in functie de grad si ordinea lexicografica a primului
    cuvant, iar in newWord1 si newWord2 vor fi citite perechile initial*/
	char words1[1000][51], words2[1000][51], newWord1[51], newWord2[51];
	scanf("%d", &N);
	for (i=0; i<N; i++) {
		scanf ("%s%s", newWord1, newWord2);
	    //i-1=indexul ultimului element din cei 3 vectori
		directInsertion(i-1, grades, words1,
			words2, compute_grade(newWord1, newWord2), newWord1, newWord2);
	}
	for (i=0; i<N; i++)
		printf ("%s %s\n", words1[i], words2[i]);
	return 0;
}

/*Pentru a verifica daca doua cuvinte, primite prin parametrii s1 si s2, sunt
anagrame unul pentru celalalt se determina frecventa fiecarei litere pentru
cele doua cuvinte individual. Daca acestea au aceeasi frecventa la fiecare
litera, sunt anagrame si se returneaza 1, in caz contrar, se returneaza 0.*/
int is_anagram (char *s1, char *s2) {
	if (strlen(s1)!=strlen(s2))
		return 0; //daca numarul de litere este diferit nu putem avea anagrame
	/*vectorii reprezinta frecventa literelor in ordinea alfabetului englez
	e.g: alfabet1[25] = frecventa literei 'z' in s1*/
	int alfabet1[26]={0}, alfabet2[26]={0}, i;
	for (i=0; s1[i]!='\0'; i++)
		alfabet1[s1[i]-'a']++; //caracter-'a' = indexul caracterului in alfabet
	for (i=0; s2[i]!='\0'; i++)
		alfabet2[s2[i]-'a']++;
	for (i=0; i<26; i++)
		if (alfabet1[i]!=alfabet2[i])
			return 0; //daca frecventa e diferita, nu sunt anagrame
	return 1;
}

/*Functia determina gradul a 2 cuvinte primite ca parametru prin siruri de
caractere, lucru realizat prin numararea diferentelor de caractere aflate
pe acelasi index in cele 2 cuvinte si impartirea la numarul de caractere.*/
double compute_grade (char *s1, char *s2) {
	double dif;
	if (!is_anagram(s1, s2)) //daca s2 nu este anagram al lui s1, gradul e -1
		return -1;
	dif=0; //numarul de caractere diferite
	for (int i=0; s1[i]!='\0'; i++)
		if (s1[i]!=s2[i])
			dif++;
	return dif/strlen(s1);
}

/*Pentru a sorta descrescator cele 3 structuri solutie pe parcursul citirii
este aplicat un algoritm de insertie directa in functie de grad si, in caz de
egalitate de grad, de ordinea lexicografica a primelor cuvinte din fiecare
pereche*/
void directInsertion (int M, double *grades, char words1[][51],
    char words2[][51], double newGrade, char *newWord1, char *newWord2)
{
    while (M>=0 && (grades[M]<newGrade ||
        (grades[M]-newGrade<0.001 && strcmp(words1[M], newWord1)<0)))
	{
		grades[M+1]=grades[M];
		strcpy(words1[M+1], words1[M]);
		strcpy(words2[M+1], words2[M]);
		M--;
	}
	grades[M+1]=newGrade;
	strcpy(words1[M+1], newWord1);
	strcpy(words2[M+1], newWord2);
}