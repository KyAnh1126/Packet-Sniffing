#pragma once

#include <vector>
using namespace std;

#define BUF_SZ 65536
#define MAC_ADDR_SZ 18

#define ETH_IP_DEC 8
#define ETH_IPV6_DEC 56710
#define ETH_ARP 1544

enum layer {
    E_NETWORK,
    E_INTERNET,
    E_TRANSPORT,
    E_APPLICATION
};

enum l2hdr_tag {
    E_ETH,
    UNKNOWN_L2
};

enum l3hdr_tag {
    E_IP,
    E_IPV6, 
    UNKNOWN_L3
};

enum l4hdr_tag {
    E_TCP,
    E_UDP, 
    UNKNOWN_L4
};

struct packet {
    int id = -1;
    int total_length = -1;
    int l2hdr_tag = UNKNOWN_L2, l2hdr_len = -1;
    int l3hdr_tag = UNKNOWN_L3, l3hdr_len = -1;
    int l4hdr_tag = UNKNOWN_L4, l4hdr_len = -1;
    int payload_len = -1;

    char* buffer;
};

extern vector<packet> packets;

void get_packet(char* buffer, struct packet* packet, int id, int buflen);
void get_packets();

int get_prev_len(struct packet* packet, int layer);


