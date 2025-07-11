// Protocoale de comunicatii
// Laborator 10 - DNS
// dns.c

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int usage(char* name)
{
	printf("Usage:\n\t%s -n <NAME>\n\t%s -a <IP>\n", name, name);
	return 1;
}

// Receives a name and prints IP addresses
void get_ip(char* name)
{
	int ret;
	struct addrinfo *result, *p;
	struct addrinfo hints;

	// TODO: set hints
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;

	// TODO: get addresses
	getaddrinfo(name, NULL, &hints, &result);

	// TODO: iterate through addresses and print them
	p = result;

	while (p != NULL) {
		struct sockaddr_in *x = (struct sockaddr_in *) p->ai_addr;
		puts(inet_ntoa(x->sin_addr));
		p = p->ai_next;
	}

	// TODO: free allocated data

}

// Receives an address and prints the associated name and service
void get_name(char* ip)
{
	int ret;
	struct sockaddr_in addr;
	char host[1024];
	char service[20];

	memset(&addr, 0, sizeof(struct sockaddr_in));

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_port = htons(80);

	ret = getnameinfo(&addr, sizeof(struct sockaddr_in), host, 1024, service, 20, 0);
	if (ret < 0) {
		perror("getnameinfo");
		exit(1);
	}

	puts(host);
	puts(service);
}

int main(int argc, char **argv)
{
	if (argc < 3) {
		return usage(argv[0]);
	}

	if (strncmp(argv[1], "-n", 2) == 0) {
		get_ip(argv[2]);
	} else if (strncmp(argv[1], "-a", 2) == 0) {
		get_name(argv[2]);
	} else {
		return usage(argv[0]);
	}

	return 0;
}
