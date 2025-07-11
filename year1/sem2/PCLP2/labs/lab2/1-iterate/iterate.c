#include <stdio.h>

/**
 * Afisati adresele elementelor din vectorul "v" impreuna cu valorile
 * de la acestea.
 * Parcurgeti adresele, pe rand, din octet in octet,
 * din 2 in 2 octeti si apoi din 4 in 4.
 */

int main() {
    int v[] = {0xCAFEBABE, 0xDEADBEEF, 0x0B00B135, 0xBAADF00D, 0xDEADC0DE};
    unsigned char *char_ptr = (unsigned char *) v;
    while ((int *)char_ptr < v+5) {
        printf("%p -> 0x%X\n", char_ptr, *char_ptr);
        char_ptr = char_ptr + 1;
    }
    char_ptr = (unsigned char *) v;
    while ((int *)char_ptr < v+5) {
        printf("%p -> 0x%X\n", char_ptr, *char_ptr);
        char_ptr = char_ptr + 2;
    }
    char_ptr = (unsigned char *) v;
    while ((int *)char_ptr < v+5) {
        printf("%p -> 0x%X\n", char_ptr, *char_ptr);
        char_ptr = char_ptr + 4;
    }
    return 0;
}
