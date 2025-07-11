#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "common.h"
#include "utils.h"
#include "queue.h"

/* Max size of the datagrams that we will be sending */
#define CHUNKSIZE 1024
#define SENT_FILENAME "file.bin"
#define SERVER_IP "172.16.0.100"

/* Queue we will use for datagrams */
queue datagram_queue;

// connection
struct sockaddr_in servaddr;
int sockfd, rc;

void send_file(int sockfd, struct sockaddr_in server_address, char *filename)
{
    int fd = open(filename, O_RDONLY);
    DIE(fd < 0, "open");
    int rc;

    /* TODO 2.1: Increase window size to a value that optimally uses the link */
    int window_size = 50000 / 1500;

    while (1)
    {
        /* TODO: 1.1 Read all the data of the and add it as datagrams in datagram_queue */
        /* Reads the content of a file */
        struct seq_udp *d = malloc(sizeof(struct seq_udp));
        int n = read(fd, d->payload, sizeof(d->payload));
        DIE(n < 0, "read");
        d->len = n;
        queue_enq(datagram_queue, d);

        if (n == 0) // end of file
            break;
    }

    /* TODO 2.2: Send window_size packets from the queue. Don't forget to free the data. */
    for (int i = 0; i < window_size; i++)
    {
        struct seq_udp *t = queue_deq(datagram_queue);

        rc = sendto(sockfd, t, sizeof(struct seq_udp), 0,
                    (struct sockaddr *)&servaddr, sizeof(servaddr));
        DIE(rc < 0, "sendto");
    }

    int ack;

    while (!queue_empty(datagram_queue))
    {
        /* TODO 2.2: On ACK, slide the window by popping the queue and sending the next datagram. */

        rc = recvfrom(sockfd, &ack, sizeof(ack), 0, NULL, NULL);
        DIE(rc < 0, "recvfrom");

        struct seq_udp *t = queue_deq(datagram_queue);

        rc = sendto(sockfd, t, sizeof(struct seq_udp), 0,
                    (struct sockaddr *)&servaddr, sizeof(servaddr));
    }

    for (int i = 0; i < window_size; i++)
         rc = recvfrom(sockfd, &ack, sizeof(ack), 0, NULL, NULL);
}

int main(int argc, char *argv[])
{

    /* We use this structure to store the server info. IP address and Port.
     * This will be written by the UDP implementation into the header */

    /* Queue that we will use when implementing sliding window */
    datagram_queue = queue_create();

    // Creating socket file descriptor. SOCK_DGRAM for UDP
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    DIE(sockfd < 0, "socket");

    // Fill the information that will be put into the IP and UDP header to
    // identify the target process (via PORT) on a given host (via SEVER_IP)
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    inet_aton(SERVER_IP, &servaddr.sin_addr);

    struct seq_udp d;
    strcpy(d.payload, "Hello world!");
    d.len = strlen("Hello world!");

    /* Send a UDP datagram. Sendto is implemented in the kernel (network stack of
     * it), it basically creates a UDP datagram, sets the payload to the data we
     * specified in the buffer, and the completes the IP header and UDP header
     * using the sever_address info.*/
    rc = sendto(sockfd, &d, sizeof(struct seq_udp), 0,
                (struct sockaddr *)&servaddr, sizeof(servaddr));

    DIE(rc < 0, "send");

    /* Receive the ACK. recvfrom is blocking with the current parameters */
    int ack;
    rc = recvfrom(sockfd, &ack, sizeof(ack), 0, NULL, NULL);

    /* TODO 1.0: comment the previous code and implement send_file using
     * stop-and-wait aka window size = 1 */
    send_file(sockfd, servaddr, SENT_FILENAME);

    close(sockfd);

    return 0;
}
