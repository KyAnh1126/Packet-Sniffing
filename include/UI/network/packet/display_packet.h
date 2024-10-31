#pragma once
#include <packet.h>

void display_packet_ETH(struct ethhdr* eth_hdr);

void display_packet_IP(struct iphdr* ip_hdr);
void display_packet_IPv6(struct ipv6hdr* ipv6_hdr);

void display_packet_TCP(struct tcphdr* tcp_hdr);
void display_packet_UDP(struct udphdr* udp_hdr) ;

void display_packet_l2hdr(struct packet* packet);
void display_packet_l3hdr(struct packet* packet);
void display_packet_l4hdr(struct packet* packet);

void display_packet_payload(struct packet* packet);

void display_packet_detail_pk(packet* packet);
void display_packet_detail_id(int id);

void display_packet_general(packet* packet);



