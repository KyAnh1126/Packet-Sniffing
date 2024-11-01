#include <iostream>
#include <vector>
#include <linux/if_ether.h>
#include <linux/if.h>
#include <linux/ip.h>
#include <linux/ipv6.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <math.h>
#include <cstring>

#include "packet.h"
#include "display_packet.h"

using namespace std;

void display_packet_ETH(struct ethhdr* eth_hdr) {
    cout << "\n*********************************ETHERNET HEADER*********************************\n";

    char* source_MAC = new char[MAC_ADDR_SZ];
    char* dest_MAC = new char[MAC_ADDR_SZ];
    int h_proto = eth_hdr->h_proto;

    snprintf(source_MAC, MAC_ADDR_SZ, "%.2X:%.2X:%.2X:%.2X:%.2X:%.2X", eth_hdr->h_source[0],eth_hdr->h_source[1],eth_hdr->h_source[2],eth_hdr->h_source[3],eth_hdr->h_source[4],eth_hdr->h_source[5]);
    snprintf(dest_MAC, MAC_ADDR_SZ, "%.2X:%.2X:%.2X:%.2X:%.2X:%.2X", eth_hdr->h_dest[0],eth_hdr->h_dest[1],eth_hdr->h_dest[2],eth_hdr->h_dest[3],eth_hdr->h_dest[4],eth_hdr->h_dest[5]);

    cout << "source MAC address: " << source_MAC << '\n';
    cout << "destination MAC address: " << dest_MAC << '\n';
    cout << "next layer protocol: " << h_proto << '\n';
    cout << '\n';

    delete[] source_MAC;
    delete[] dest_MAC;
}

void display_packet_l2hdr(struct packet* packet) {
    struct ethhdr* eth_hdr = (ethhdr*) (packet->buffer + get_prev_len(packet, L_NETWORK));
    display_packet_ETH(eth_hdr);
}

void display_packet_IP(struct iphdr* ip_hdr) {
    char* src_IP = new char[INET_ADDRSTRLEN];
    char* dest_IP = new char[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &ip_hdr->saddr, src_IP, INET_ADDRSTRLEN);
    inet_ntop(AF_INET, &ip_hdr->daddr, dest_IP, INET_ADDRSTRLEN);

    cout << "\n***********************************IPV4 HEADER***********************************\n\n";
    cout << "version: " << (int)ip_hdr->version << '\n';
    cout << "header length: " << (int)ip_hdr->ihl << " (bytes: " << (int)ip_hdr->ihl * 4 << ")\n";
    cout << "total length: " << ntohs(ip_hdr->tot_len) << '\n';
    cout << "identification: " << ntohs(ip_hdr->id) << '\n';
    cout << "TTL: " << (int)ip_hdr->ttl << '\n';
    cout << "protocol: " << (int)ip_hdr->protocol << '\n';
    cout << "header checksum: " << ntohs(ip_hdr->check) << '\n';
    cout << "source IP address: " << src_IP << '\n';
    cout << "destination IP address: " << dest_IP << '\n';

    cout << "tos: " << (int)ip_hdr->tos << '\n';
    cout << "flag offset: " << ntohs(ip_hdr->frag_off) << '\n';

    cout << '\n';

    delete[] src_IP;
    delete[] dest_IP;
}

void display_packet_IPv6(struct ipv6hdr* ipv6_hdr) {
    char* src_IPv6 = new char[INET6_ADDRSTRLEN];
    char* dest_IPv6 = new char[INET6_ADDRSTRLEN];

    inet_ntop(AF_INET6, &ipv6_hdr->saddr, src_IPv6, INET6_ADDRSTRLEN);
    inet_ntop(AF_INET6, &ipv6_hdr->daddr, dest_IPv6, INET6_ADDRSTRLEN);

    cout << "\n***********************************IPV6 HEADER***********************************\n";
    cout << "version: " << (int)ipv6_hdr->version << '\n';
    cout << "priority: " << (int)ipv6_hdr->priority << '\n';
    cout << "header length: " << sizeof(struct ipv6hdr) << " bytes\n";
    cout << "payload length: " << ntohs(ipv6_hdr->payload_len) << '\n';
    cout << "next header: " << (int)ipv6_hdr->nexthdr << '\n';
    cout << "hop limit (TTL): " << (int)ipv6_hdr->hop_limit << '\n';
    cout << "source IPv6 address: " << src_IPv6 << '\n';
    cout << "destination IPv6 address: " << dest_IPv6 << '\n';

    cout << '\n';

    delete[] src_IPv6;
    delete[] dest_IPv6;
}

void display_packet_l3hdr(struct packet* packet) {
    int prev_len = get_prev_len(packet, L_INTERNET);

    if(packet->l3hdr_tag == L3_IP) {
        struct iphdr* ip_hdr = (iphdr*) (packet->buffer + prev_len);
        display_packet_IP(ip_hdr);
    }

    if(packet->l3hdr_tag == L3_IPV6) {
        struct ipv6hdr* ipv6_hdr = (ipv6hdr*) (packet->buffer + prev_len);
        display_packet_IPv6(ipv6_hdr);
    }
}

void display_packet_TCP(struct tcphdr* tcp_hdr) {
    cout << "\n***********************************TCP HEADER***********************************\n";
    cout << "header length: " << sizeof(struct tcphdr) << '\n';
    cout << "source port: " << ntohs(tcp_hdr->source) << '\n';
    cout << "destination port: " << ntohs(tcp_hdr->dest) << '\n';
    cout << "seq: " << ntohs(tcp_hdr->seq) << '\n';
    cout << "ack_seq: " << ntohs(tcp_hdr->ack_seq) << '\n';
    cout << "checksum: " << ntohs(tcp_hdr->check) << '\n';
    cout << "window: " << ntohs(tcp_hdr->window) << '\n';

    cout << '\n';
}

void display_packet_UDP(struct udphdr* udp_hdr) {
    cout << "\n***********************************UDP HEADER***********************************\n";
    cout << "header length: " << sizeof(udphdr) << '\n';
    cout << "source port: " << ntohs(udp_hdr->source) << '\n';
    cout << "destination port: " << ntohs(udp_hdr->dest) << '\n';
    cout << "len: " << ntohs(udp_hdr->len) << '\n';
    cout << "checksum: " << ntohs(udp_hdr->check) << '\n';

    cout << '\n';
}

void display_packet_l4hdr(struct packet* packet) {
    int prev_len = get_prev_len(packet, L_TRANSPORT);

    if(packet->l4hdr_tag == L4_TCP) {
        struct tcphdr* tcp_hdr = (tcphdr*) (packet->buffer + prev_len);
        display_packet_TCP(tcp_hdr);
    }

    if(packet->l4hdr_tag == L4_UDP) {
        struct udphdr* udp_hdr = (udphdr*) (packet->buffer + prev_len);
        display_packet_UDP(udp_hdr);
    }
}

void display_packet_payload(struct packet* packet) {
    int prev_len = get_prev_len(packet, L_APPLICATION);

    char* data = packet->buffer + prev_len;
    char* binary_data;
    char* tmp;
    int payload_len;

    payload_len = packet->payload_len;

    int binary_data_len = payload_len * 3 + (int)ceil((double)(payload_len / 16)) + 3;

    binary_data = new char[binary_data_len];
    cout << "\n******************************USER APPLICATION DATA******************************\n";
    cout << "payload len: " << payload_len << '\n';
    cout << "actual data: \n\n";

    int pos = 0;

    tmp = new char[2];

    for(int i = 0; i < payload_len; ++i) {
        if(i > 0 && i % 16 == 0) {
            binary_data[pos++] = '\n';
        }
        else if(i > 0) {
            binary_data[pos++] = ' ';
        }
        snprintf(tmp, 3, "%.2X", data[i]);

        binary_data[pos++] = tmp[0];
        binary_data[pos++] = tmp[1];
    }
    binary_data[pos] = '\0';
    cout << binary_data << '\n';

    cout << '\n';

    delete[] tmp;
    delete[] binary_data;
}

void display_packet_detail_pk(packet* packet) {
    display_packet_l2hdr(packet);
    display_packet_l3hdr(packet);
    display_packet_l4hdr(packet);
    display_packet_payload(packet);
}

// id: packet id
void display_packet_detail_id(int id) {
    --id;
    packet packet = packets.at(id);
    display_packet_detail_pk(&packet);
}

void display_packet_general(packet* packet) {
    int prev_len = packet->get_l2hdr_len();

    char* source_IP = NULL;
    char* dest_IP = NULL;
    char* l4proto = NULL;

    if(packet->l3hdr_tag == L3_IP) {
        struct iphdr* ip_hdr = (iphdr*) (packet->buffer + prev_len);
        source_IP = new char[INET_ADDRSTRLEN];
        dest_IP = new char[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &ip_hdr->saddr, source_IP, INET_ADDRSTRLEN);
        inet_ntop(AF_INET, &ip_hdr->daddr, dest_IP, INET_ADDRSTRLEN);
    }

    if(packet->l3hdr_tag == L3_IPV6) {
        struct ipv6hdr* ipv6_hdr = (ipv6hdr*) (packet->buffer + prev_len);
        source_IP = new char[INET6_ADDRSTRLEN];
        dest_IP = new char[INET6_ADDRSTRLEN];
        inet_ntop(AF_INET6, &ipv6_hdr->saddr, source_IP, INET6_ADDRSTRLEN);
        inet_ntop(AF_INET6, &ipv6_hdr->daddr, dest_IP, INET6_ADDRSTRLEN);
    }

    if(packet->l4hdr_tag == L4_TCP) {
        l4proto = new char[4];
        strncpy(l4proto, "TCP", 4);
    }

    if(packet->l4hdr_tag == L4_UDP) {
        l4proto = new char[4];
        strncpy(l4proto, "UDP", 4);
    }

    if(packet->l4hdr_tag == L4_UNKNOWN) {
        l4proto = new char[8];
        strncpy(l4proto, "UNKNOWN", 8);
    }
    

    cout << packet->id << ", " << (source_IP == NULL ? "NULL" : source_IP) << ", " << (dest_IP == NULL ? "NULL" : dest_IP) << ", " << (l4proto == NULL ? "NULL" : l4proto) << ", " << packet->total_length << "\n\n";

    delete[] source_IP;
    delete[] dest_IP;

}