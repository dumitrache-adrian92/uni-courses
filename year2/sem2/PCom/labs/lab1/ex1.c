#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

struct Packet
{
    char payload[100];
    int sum;
    int size;
};

int main()
{
    struct Packet *p = malloc(2 * sizeof(struct Packet));
    int fd = open("ex3.txt", O_RDONLY);

    if (fd < 0)
        perror("open");

    int rd;
    char buf[sizeof(struct Packet)];
    int i = 0;

    do {
        rd = 0;
        int rem = sizeof(struct Packet);
        int n = 0;

        while (rem > 0) {
            int b = read(fd, buf + rd, sizeof(struct Packet));

            if (b < 0)
                perror("read");

            if (b == 0)
                break;

            rem -= b;
            rd += b;
        }

        if (rd) {
            memcpy(&p[i] , buf, sizeof(struct Packet));
            i++;
        }
    } while (rd);

    for (int i = 0; i < 2; i++)
    {
        puts(p[i].payload);
        printf("%d %d\n", p[i].size, p[i].sum);
    }

    free(p);
    close(fd);

    return 0;
}