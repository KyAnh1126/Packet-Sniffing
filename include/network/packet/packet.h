#pragma once

#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/ipv6.h>
#include <linux/tcp.h>
#include <linux/udp.h>

#include <vector>
using namespace std;

#define BUF_SZ 65536
#define MAC_ADDR_SZ 18

#define ETH_IP_DEC 8
#define ETH_IPV6_DEC 56710
#define ETH_ARP 1544

enum layer {
    L_NETWORK,
    L_INTERNET,
    L_TRANSPORT,
    L_APPLICATION
};

enum l2hdr_tag {
    L2_ETH,
    L2_UNKNOWN
};

enum l3hdr_tag {
    L3_IP,
    L3_IPV6, 
    L3_UNKNOWN
};

enum l4hdr_tag {
    L4_TCP,
    L4_UDP, 
    L4_UNKNOWN
};

struct packet {
    int id = -1;
    int total_length = -1;
    int l2hdr_tag = L2_UNKNOWN;
    int l3hdr_tag = L3_UNKNOWN;
    int l4hdr_tag = L4_UNKNOWN;
    int payload_len = -1;

    char* buffer;

    int get_l2hdr_len() {
        if(l2hdr_tag == L2_ETH) return sizeof(struct ethhdr);
        if(l2hdr_tag == L2_UNKNOWN) return -1;
        return -1;
    }

    int get_l3hdr_len() {
        if(l3hdr_tag == L3_IP) return sizeof(struct iphdr);
        if(l3hdr_tag == L3_IPV6) return sizeof(struct ipv6hdr);
        if(l3hdr_tag == L3_UNKNOWN) return -1;
        return -1;
    }

    int get_l4hdr_len() {
        if(l4hdr_tag == L4_TCP) return sizeof(struct tcphdr);
        if(l4hdr_tag == L4_UDP) return sizeof(struct udphdr);
        if(l4hdr_tag == L4_UNKNOWN) return -1;
        return -1;
    }

    int get_payload_len() {
        return total_length - (get_l2hdr_len() + get_l3hdr_len() + get_l4hdr_len());
    }
};

extern vector<packet> packets;

void get_packet(char* buffer, struct packet* packet, int id, int buflen);
void get_packets();

int get_prev_len(struct packet* packet, int layer);


