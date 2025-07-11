#include "dlist.h"
#include <string.h>

int main(int argc, char **argv) {
    int ok = 1;
    dlist dataStream;
    readList(&dataStream);
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--e1"))
            removeExceptions(&dataStream, 5);
        else if (!strcmp(argv[i], "--e2"))
            medianFilter(&dataStream, 5);
        else if (!strcmp(argv[i], "--e3"))
            meanFilter(&dataStream, 5);
        else if (!strcmp(argv[i], "--u"))
            equalize(&dataStream);
        else if (!strcmp(argv[i], "--c"))
            dataCompletion(&dataStream, 3);
        else if (strstr(argv[i], "--st") != NULL) {
            ok = 0;
            statistics(&dataStream, stringToInt(argv[i] + 4));
        }
    }
    if (ok)
        printList(dataStream);
    freeList(&dataStream);
}