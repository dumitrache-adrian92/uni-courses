#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Usage: ./cat <filename>\n");
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);

    if (fd < 0) {
        printf("File not found.\n");
        return 1;
    }

    char buffer[1024];
    int rc = 0;
    int rc2 = 0;

    do {
        rc = read(fd, buffer, 1024);

        if (rc < 0)
            perror("read");

        do {
            rc2 += write(STDOUT_FILENO, buffer + rc2, rc);
            if (rc2 < 0)
                perror("write");
        } while (rc2 < rc);
    } while (rc);

    rc2 = write(STDOUT_FILENO, "\n", 2);
    if (rc2 < 0)
        perror("write");

    return 0;
}