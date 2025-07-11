#ifndef __COMMON_H__
#define __COMMON_H__

#include <stddef.h>
#include <stdint.h>

int send_all(int sockfd, void *buff, size_t len);
int recv_all(int sockfd, void *buff, size_t len);

#define MSG_MAXSIZE 1024

struct chat_packet {
  uint16_t len;
  uint32_t destination;
  char message[MSG_MAXSIZE + 1];
};

#endif