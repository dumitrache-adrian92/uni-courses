#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "link_emulator/lib.h"

/* Do not touch these two */
#define HOST "127.0.0.1"
#define PORT 10001

#include "common.h"

/* Our unqiue layer 2 ID */
static int ID = 123131;

struct __attribute__((packed)) source_dest {
    int source; /* Identificator SURSĂ */
    int dest; /* Identificator DESTINAȚIE */
};

/* Function which our protocol implementation will provide to the upper layer. */
int recv_frame(char *buf)
{
	enum State state = IDLE;
	char c;
	int i = 0;

	while (1) {
		c = recv_byte();

		if (state == IDLE) {
			if (c == 'D')
				state = START_DLE;
		}
		else if (state == START_DLE) {
			if (c == 'S')
				state = STARTED;
			else
				state = IDLE;
		}
		else if (state == STARTED) {
			if (c == 'D')
				state = ESCAPE;
			else
				buf[i++] = c;
		}
		else if (state == ESCAPE) {
			if (c == 'E')
				break;
			else {
				buf[i++] = c;
				state = STARTED;
			}
		}
	}

	struct source_dest sd;
	memcpy(&sd, buf, sizeof(struct source_dest));

	if (sd.dest != ID) {
		memset(buf, 0, i);
		return 0;
	}
	else
		for (int j = 2; j < i + 2; j++)
			buf[j - 2] = buf[j];


	/* If everything went well return the number of bytes received */
	return i;
}

int main(int argc,char** argv){
	/* Do not touch this */
	init(HOST,PORT);

	/* TODO 1.0: Allocate a buffer and call recv_frame */
	char buffer[100];

	recv_frame(buffer);

	puts(buffer);

	/* TODO 3: Measure latency in a while loop for any frame that contains
	 * a timestamp we receive, print frame_size and latency */

	printf("[RECEIVER] Finished transmission\n");
	return 0;
}
