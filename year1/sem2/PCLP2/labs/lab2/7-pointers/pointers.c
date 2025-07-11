#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int my_strcmp(const char *s1, const char *s2) {
    for (int i = 0; *(s1+i) != '\0' || *(s2+i) != '\0'; i++)
        if (*(s1+i) != *(s2+i))
            return *(s1+i) - *(s2+i);
}

void *my_memcpy(void *dest, const void *src, size_t n) {
	char *d = dest;
  	const char *s = src;
	while (n--)
		*d++ = *s++;
	return dest;
}

char *my_strcpy(char *dest, const char *src) {
	int i = 0;
	do {
		*(dest+i) = *(src+i);
		i++;
	} while (*(src+i) != '\0');
	return dest;
}

int main() {
    char s1[] = "Abracadabra";
    char s2[] = "Abracababra";
    char src[] = "Learn IOCLA, you must!";
    char *dest = malloc(sizeof(src));
    /*
    Decomentati pe rand cate un assert pe masura ce implementati o functie.
    Daca functia voastra este implementata corect atunci asertia se va realiza
    cu succes. In caz contrar, programul va crapa.
    */
    assert(my_strcmp(s1, s2) == strcmp(s1, s2));
    assert(my_memcpy(dest, src, sizeof(src)) == memcpy(dest, src, sizeof(src)));
    assert(my_strcpy(dest, src) == strcpy(dest, src));
    free(dest);

    return 0;
}
