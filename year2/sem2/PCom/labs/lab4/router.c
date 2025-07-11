#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include "lib.h"
#include "protocols.h"

/* Routing table */
struct route_table_entry *rtable;
int rtable_len;

/* Mac table */
struct mac_entry *mac_table;
int mac_table_len;

/*
 Returns a pointer (eg. &rtable[i]) to the best matching route, or NULL if there
 is no matching route.
*/
struct route_table_entry *get_best_route(uint32_t ip_dest) {
	/* TODO 2.2: Implement the LPM algorithm */
	/* We can iterate through rtable for (int i = 0; i < rtable_len; i++). Entries in
	 * the rtable are in network order already */
	uint32_t prefix_max = 0;
	int j = -1;

	for (int i = 0; i < rtable_len; i++) {
		if (ntohs(rtable[i].prefix) == (ntohs(ip_dest) & ntohs(rtable[i].mask)))
			if (j == -1 || prefix_max < ntohs(rtable[i].prefix)) {
				prefix_max = ntohs(rtable[i].prefix);
				j = i;
			}
	}
	if (j == -1)
		return NULL;
	return rtable + j;
}

struct mac_entry *get_mac_entry(uint32_t ip_dest) {
	/* TODO 2.4: Iterate through the MAC table and search for an entry
	 * that matches ip_dest. */
	for (int i = 0; i < mac_table_len; i++)
		if (mac_table->ip == ip_dest)
			return mac_table + i;
	/* We can iterate thrpigh the mac_table for (int i = 0; i <
	 * mac_table_len; i++) */
	return NULL;
}

int main(int argc, char *argv[])
{
	int interface;
	char buf[MAX_LEN];
	int len;

	/* Don't touch this */
	init();

	/* Code to allocate the MAC and route tables */
	rtable = malloc(sizeof(struct route_table_entry) * 100);
	/* DIE is a macro for sanity checks */
	DIE(rtable == NULL, "memory");

	mac_table = malloc(sizeof(struct  mac_entry) * 100);
	DIE(mac_table == NULL, "memory");

	/* Read the static routing table and the MAC table */
	rtable_len = read_rtable("rtable.txt", rtable);
	mac_table_len = read_mac_table(mac_table);

	while (1) {
		/* We call get_packet to receive a packet. get_packet returns
		the interface it has received the data from. And writes to
		len the size of the packet. */
		interface = recv_from_all_links(buf, &len);
		DIE(interface < 0, "get_message");
		printf("We have received a packet\n");

		/* Extract the Ethernet header from the packet. Since protocols are
		 * stacked, the first header is the ethernet header, the next header is
		 * at m.payload + sizeof(struct ether_header) */
		struct ether_header *eth_hdr = (struct ether_header *) buf;
		struct iphdr *ip_hdr = (struct iphdr *) (buf + sizeof(struct ether_header));

		/* TODO 2.1: Check the ip_hdr integrity using ip_checksum(ip_hdr, sizeof(struct iphdr)) */
		uint16_t old = ntohs(ip_hdr->check);
		ip_hdr->check = 0;

		// if bad checksum skip
		if (ip_checksum((uint16_t *) ip_hdr, sizeof(struct iphdr)) != old)
			continue;
		/* TODO 2.2: Call get_best_route to find the most specific route, continue; (drop) if null */
		struct route_table_entry *destination = get_best_route(ip_hdr->daddr);
		if (destination == NULL)
			continue;

		/* TODO 2.3: Check TTL >= 1. Update TLL. Update checksum using the incremental forumla  */
		if (ip_hdr->ttl < 1)
			continue;

		ip_hdr->ttl--;

		ip_hdr->check = ~(~old +  ~((uint16_t)ip_hdr->ttl) + (uint16_t)ip_hdr->ttl + 1) - 1;
		ip_hdr->check = htons(ip_hdr->check);

		/* TODO 2.4: Update the ethernet addresses. Use get_mac_entry to find the destination MAC
		 * address. Use get_interface_mac(m.interface, uint8_t *mac) to
		 * find the mac address of our interface. */
		struct mac_entry *next = get_mac_entry(ntohs(destination->next_hop));

		if (next == NULL)
			continue;

		uint8_t *host = malloc(6);
		get_interface_mac(interface, host);
		memcpy(eth_hdr->ether_dhost, next->mac, 6);
		memcpy(eth_hdr->ether_shost, host, 6);


		// Call send_to_link(best_router->interface, packet, len);
		send_to_link(interface, buf, len);
	}
}
