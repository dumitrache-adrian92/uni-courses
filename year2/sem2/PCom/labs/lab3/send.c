#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "common.h"
#include "link_emulator/lib.h"
#include <arpa/inet.h>

#define HOST "127.0.0.1"
#define PORT 10000


int main(int argc,char** argv) {
	init(HOST,PORT);

	/* Look in common.h for the definition of l3_msg */
	struct l3_msg t;
	char buf[256];
	int fd = open("test.txt", O_RDWR);

	/* We set the payload */
	sprintf(t.payload, "Hello my World of PC!");
	t.hdr.len = strlen(t.payload) + 1;

	/* Add the checksum */
	/* Note that we compute the checksum for both header and data. Thus
	 * we set the checksum equal to 0 when computing it */
	t.hdr.sum = 0;

	/* Since sum is on 32 bits, we have to convert it to network order */
	/* TODO 2.0: Call crc32 function */

	t.hdr.sum = htonl(crc32((void *) &t, sizeof(struct l3_msg)));

	/* Send the message */
	link_send(&t, sizeof(struct l3_msg));

	/* TODO 3.1: Receive the confirmation */

	link_recv(buf, 2);

	/* TODO 3.2: If we received a NACK, retransmit the previous frame */
	while (strcmp(buf, "N") == 0) {
	 	link_send(&t, sizeof(struct l3_msg));
		link_recv(buf, 2);
	}
	/* TODO 3.3: Update this to read the content of a file and send it as
	 * chunks of that file given a MTU of 1500 bytes */

	int cr;

	do {
		cr = read(fd, t.payload, 1500 - sizeof(struct l3_msg_hdr));

		if (cr == 0)
			break;
		t.hdr.len = cr;
		t.hdr.sum = 0;
		t.hdr.sum = htonl(crc32((void *) &t, sizeof(struct l3_msg)));

		/* Send the message */
		link_send(&t, sizeof(struct l3_msg));

		/* TODO 3.1: Receive the confirmation */

		link_recv(buf, 2);

		/* TODO 3.2: If we received a NACK, retransmit the previous frame */
		while (strcmp(buf, "N") == 0) {
			link_send(&t, sizeof(struct l3_msg));
			link_recv(buf, 2);
		}
	} while (cr);

	link_send("end", 4);

	close(fd);
	return 0;
}
