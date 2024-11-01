#include <stdio.h>
#include <linux/if_ether.h>
#include <linux/if.h>
#include <linux/ip.h>
#include <linux/ipv6.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <math.h>

#include <iostream>

#include "packet.h"
#include "display_packet.h"

using namespace std;

#define MAX_SZ 20000

vector<packet> packets;

int open_socket(int* sock) {
    *sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if(*sock < 0) {
        perror("open socket for getting packets");
        return -1;
    }
    return 0;
}

int get_prev_len(struct packet* packet, int layer) {
    if(layer == L_NETWORK) return 0;
    if(layer == L_INTERNET) return packet->get_l2hdr_len();
    if(layer == L_TRANSPORT) return packet->get_l2hdr_len() + packet->get_l3hdr_len();
    if(layer == L_APPLICATION) return packet->get_l2hdr_len() + packet->get_l3hdr_len() + packet->get_l4hdr_len();
    return -1;
}

void get_packet(char* buffer, packet* packet, int id, int buflen) {

    packet->id = id;
    packet->total_length = buflen;

    int l2hdr_tag = L2_UNKNOWN, l2hdr_len = -1;
    int l3hdr_tag = L3_UNKNOWN, l3hdr_len = -1;
    int l4hdr_tag = L4_UNKNOWN, l4hdr_len = -1;
    int payload_len = -1;

    int prev_len = 0;

    l2hdr_tag = L2_ETH;
    l2hdr_len = sizeof(struct ethhdr);
    struct ethhdr* eth_hdr = (struct ethhdr*) buffer;

    if (eth_hdr->h_proto == ETH_IP_DEC) {
        l3hdr_tag = L3_IP;
        l3hdr_len = sizeof(struct iphdr);
    }

    if (eth_hdr->h_proto == ETH_IPV6_DEC) {
        l3hdr_tag = L3_IPV6;
        l3hdr_len = sizeof(struct ipv6hdr);
    }

    prev_len += l2hdr_len;

    if (l3hdr_tag == L3_IP) {
        struct iphdr* ip_hdr = (struct iphdr*) (buffer + prev_len);
        if (ip_hdr->protocol == IPPROTO_TCP) {
            l4hdr_tag = L4_TCP;
            l4hdr_len = sizeof(struct tcphdr);
        }

        if (ip_hdr->protocol == IPPROTO_UDP) {
            l4hdr_tag = L4_UDP;
            l4hdr_len = sizeof(struct udphdr);
        }
    }

    if (l3hdr_tag == L3_IPV6) {
        struct ipv6hdr* ipv6_hdr = (struct ipv6hdr*) (buffer + prev_len);
        if (ipv6_hdr->nexthdr == IPPROTO_TCP) {
            l4hdr_tag = L4_TCP;
            l4hdr_len = sizeof(struct tcphdr);
        }

        if (ipv6_hdr->nexthdr == IPPROTO_UDP) {
            l4hdr_tag = L4_UDP;
            l4hdr_len = sizeof(struct udphdr);
        }
    }

    prev_len += l3hdr_len;

    prev_len += l4hdr_len;

    if(l4hdr_tag == L4_TCP || l4hdr_tag == L4_UDP) {
        payload_len = packet->total_length - prev_len;
    }

    packet->l2hdr_tag = l2hdr_tag;
    packet->l3hdr_tag = l3hdr_tag;
    packet->l4hdr_tag = l4hdr_tag;
    packet->payload_len = payload_len;
    packet->buffer = buffer;
}

void get_packets() {
    int sock_r;
    if(open_socket(&sock_r) == -1) return;

    // cout << "sock_r = " << sock_r << '\n'; 

    while(1) {
        char* buffer = new char[BUF_SZ];
        memset(buffer, 0, BUF_SZ);
        
        struct sockaddr saddr;
        int saddr_len = sizeof(saddr);

        //copy network packet to a buffer
        //buffer contains payload + l2, l3, l4 header
        int buflen = recvfrom(sock_r, buffer, BUF_SZ, 0, &saddr, (socklen_t*)&saddr_len);
        
        if(buflen < 0) {
            perror("recv loopback packet from sock_r");
            close(sock_r);
            return;
        }

        struct packet recv_packet;
        recv_packet.id = packets.size() + 1;
        recv_packet.total_length = buflen;
        
        get_packet(buffer, &recv_packet, packets.size() + 1, buflen);

        display_packet_general(&recv_packet);

        packets.push_back(recv_packet);
    }
    close(sock_r);
}