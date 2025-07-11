/*
 * Protocoale de comunicatii
 * Laborator 7 - TCP si mulplixare
 * client.c
 */

#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <poll.h>

#include "common.h"
#include "helpers.h"

#define MAX_CONNECTIONS 32


void run_client(int sockfd)
{
    char buf[BUFLEN];

    memset(buf, 0, BUFLEN);

    struct chat_packet sent_packet;
    struct chat_packet recv_packet;

    /* TODO 2.2: Multiplexeaza intre citirea de la tastatura si primirea unui
       mesaj, ca sa nu mai fie impusa ordinea.
    */
    struct pollfd poll_fds[MAX_CONNECTIONS];
    int connection_count = 0;

    poll_fds[connection_count].fd = STDIN_FILENO;
    poll_fds[connection_count].events = POLLIN;
    connection_count++;

    poll_fds[connection_count].fd = sockfd;
    poll_fds[connection_count].events = POLLIN;
    connection_count++;

    while (1) {
        poll(poll_fds, connection_count, -1);

        if (poll_fds[0].revents & POLLIN) {
            fgets(buf, sizeof(buf), stdin);
            sent_packet.len = strlen(buf) + 1;
            strcpy(sent_packet.message, buf);
            send_all(sockfd, &sent_packet, sizeof(sent_packet));
        }

        if (poll_fds[1].revents & POLLIN) {
            int rc = recv_all(sockfd, &recv_packet, sizeof(recv_packet));
            if (rc <= 0)
                break;

            printf("%s", recv_packet.message);
        }
    }
}

int main(int argc, char *argv[])
{
    int sockfd = -1;

    if (argc != 3)
    {
        printf("\n Usage: %s <ip> <port>\n", argv[0]);
        return 1;
    }

    // Parsam port-ul ca un numar
    uint16_t port;
    int rc = sscanf(argv[2], "%hu", &port);
    DIE(rc != 1, "Given port is invalid");

    // Obtinem un socket TCP pentru conectarea la server
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    DIE(sockfd < 0, "socket");

    // Completăm in serv_addr adresa serverului, familia de adrese si portul
    // pentru conectare
    struct sockaddr_in serv_addr;
    socklen_t socket_len = sizeof(struct sockaddr_in);

    memset(&serv_addr, 0, socket_len);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    rc = inet_pton(AF_INET, argv[1], &serv_addr.sin_addr.s_addr);
    DIE(rc <= 0, "inet_pton");

    // Ne conectăm la server
    rc = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    DIE(rc < 0, "connect");

    run_client(sockfd);

    // Inchidem conexiunea si socketul creat
    close(sockfd);

    return 0;
}
