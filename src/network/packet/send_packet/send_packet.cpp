// #include <iostream>
// #include <sys/socket.h>
// #include <linux/if.h>
// #include <cstring>
// #include <sys/ioctl.h>
// #include <unistd.h>
// #include <arpa/inet.h>
// #include <linux/if_ether.h>
// #include <linux/ip.h>
// #include <linux/udp.h>

// #include <netinet/in.h>
// #include <cstring>
// #include "../../../../include/network/packet/packet.h"

// #include "math.h"

// #include <linux/if_packet.h>

// #include <vector>

// #define MAX_SZ 1024

// // #define MAC_ADDR_SZ 18

// #define DESTMAC0 0x00
// #define DESTMAC1 0x00
// #define DESTMAC2 0x00
// #define DESTMAC3 0x00
// #define DESTMAC4 0x00
// #define DESTMAC5 0x00

// using namespace std;

// int open_socket(int* sock) {
//     *sock = socket(AF_PACKET, SOCK_RAW, IPPROTO_IP);
//     if(*sock < 0) {
//         perror("open socket for sending packet");
//         return -1;
//     }
//     return 0;
// }

// int get_if_index(int sock_r, char* if_name, int* if_index) {
//     struct ifreq ifreq_if_index;
//     memset(&ifreq_if_index, 0, sizeof(ifreq_if_index));

//     strncpy(ifreq_if_index.ifr_ifrn.ifrn_name, if_name, IFNAMSIZ);

//     if(ioctl(sock_r, SIOGIFINDEX, &ifreq_if_index) == -1) {
//         perror("ioctl for if_index");
//         return -1;
//     }

//     *if_index = ifreq_if_index.ifr_ifru.ifru_ivalue;
//     return 0;
// }

// int get_if_MAC(int sock_r, char* if_name, char* source_MAC) {
//     struct ifreq ifreq_if_MAC;
//     memset(&ifreq_if_MAC, 0, sizeof(ifreq_if_MAC));

//     strncpy(ifreq_if_MAC.ifr_ifrn.ifrn_name, if_name, IFNAMSIZ);

//     if(ioctl(sock_r, SIOCGIFHWADDR, &ifreq_if_MAC) == -1) {
//         perror("ioctl for if_MAC");
//         return -1;
//     }

//     int sa_family = ifreq_if_MAC.ifr_ifru.ifru_hwaddr.sa_family;
//     char* sa_data = ifreq_if_MAC.ifr_ifru.ifru_hwaddr.sa_data;

//     snprintf(source_MAC, MAC_ADDR_SZ, "%.2X:%.2X:%.2X:%.2X:%.2X:%.2X", (unsigned char)sa_data[0], (unsigned char)sa_data[1], (unsigned char)sa_data[2], (unsigned char)sa_data[3], (unsigned char)sa_data[4], (unsigned char)sa_data[5]);
//     return 0;
// }

// int get_if_IP(int sock_r, char* if_name, char* source_IP) {
//     struct ifreq ifreq_if_IP;
//     memset(&ifreq_if_IP, 0, sizeof(ifreq_if_IP));

//     strncpy(ifreq_if_IP.ifr_ifrn.ifrn_name, if_name, IFNAMSIZ);

//     if(ioctl(sock_r, SIOCGIFADDR, &ifreq_if_IP) < 0) {
//         perror("ioctl for if_IP");
//         return -1;
//     }

//     struct sockaddr* ifru_addr = &ifreq_if_IP.ifr_ifru.ifru_addr;
//     struct sockaddr_in* ifru_addr_in = (struct sockaddr_in*)ifru_addr;
//     struct in_addr* sin_addr = (struct in_addr*)&ifru_addr_in->sin_addr;

//     inet_ntop(AF_INET, sin_addr, source_IP, INET_ADDRSTRLEN);

//     return 0;
// }

// int construct_l2(int sock_r, char* if_name, char* sendbuff, int* total_len) {
//     struct ifreq ifreq_if_MAC;
//     memset(&ifreq_if_MAC, 0, sizeof(ifreq_if_MAC));

//     strncpy(ifreq_if_MAC.ifr_ifrn.ifrn_name, if_name, IFNAMSIZ);

//     if(ioctl(sock_r, SIOCGIFHWADDR, &ifreq_if_MAC) == -1) {
//         perror("ioctl for if_MAC");
//         return -1;
//     }

//     int sa_family = ifreq_if_MAC.ifr_ifru.ifru_hwaddr.sa_family;
//     char* sa_data = ifreq_if_MAC.ifr_ifru.ifru_hwaddr.sa_data;

//     struct ethhdr* eth_hdr = (struct ethhdr*) (sendbuff + *total_len);

//     for(int i = 0; i < 6; ++i) {
//         eth_hdr->h_source[i] = (unsigned char) sa_data[i];
//     }
//     // handle h_dest
//     eth_hdr->h_dest[0] = DESTMAC0;
//     eth_hdr->h_dest[1] = DESTMAC1;
//     eth_hdr->h_dest[2] = DESTMAC2;
//     eth_hdr->h_dest[3] = DESTMAC3;
//     eth_hdr->h_dest[4] = DESTMAC4;
//     eth_hdr->h_dest[5] = DESTMAC5;

//     eth_hdr->h_proto = htons(ETH_P_IP);
//     *total_len += sizeof(*eth_hdr);

//     return 0;
// }

// int construct_l3(int sock_r, char* if_name, char* sendbuff, int* total_len) {
//     struct ifreq ifreq_if_IP;
//     memset(&ifreq_if_IP, 0, sizeof(ifreq_if_IP));

//     strncpy(ifreq_if_IP.ifr_ifrn.ifrn_name, if_name, IFNAMSIZ);

//     if(ioctl(sock_r, SIOCGIFADDR, &ifreq_if_IP) < 0) {
//         perror("ioctl for if_IP");
//         return -1;
//     }

//     struct sockaddr* ifru_addr = &ifreq_if_IP.ifr_ifru.ifru_addr;
//     struct sockaddr_in* ifru_addr_in = (struct sockaddr_in*)ifru_addr;
//     struct in_addr* sin_addr = (struct in_addr*)&ifru_addr_in->sin_addr;

//     char* source_IP = new char[INET_ADDRSTRLEN];
//     inet_ntop(AF_INET, sin_addr, source_IP, INET_ADDRSTRLEN);

//     struct iphdr* ip_hdr = (struct iphdr*) (sendbuff + *total_len);

//     ip_hdr->version = 4;
//     ip_hdr->ihl = 5;
//     ip_hdr->id = htons(10201);
//     ip_hdr->ttl = 64;
//     ip_hdr->protocol = 17; // for UDP packet
//     ip_hdr->check = htons(0);

//     ip_hdr->saddr = inet_addr(source_IP);

//     char* des_IP = "127.0.0.1";
//     ip_hdr->daddr = inet_addr(des_IP);

//     *total_len += sizeof(*ip_hdr);
//     return 0;
// }

// int construct_l4(char* sendbuff, int* total_len) {
//     struct udphdr* udp_hdr = (struct udphdr*) (sendbuff + *total_len);
//     udp_hdr->source = htons(23451);
//     udp_hdr->dest = htons(23452);
//     udp_hdr->check = 0;

//     *total_len += sizeof(*udp_hdr);
//     return 0;
// }

// int add_payload(char* sendbuff, int* total_len) {
//     sendbuff[(*total_len)++] = 0x12;
//     sendbuff[(*total_len)++] = 0x34;
//     sendbuff[(*total_len)++] = 0x56;
//     sendbuff[(*total_len)++] = 0x78;
//     sendbuff[(*total_len)++] = 0x32;
//     return 0;
// }


// void display_packet_ETH(struct ethhdr* eth_hdr) {
//     cout << "ETHERNET HEADER\n";

//     char* source_MAC = new char[MAC_ADDR_SZ];
//     char* dest_MAC = new char[MAC_ADDR_SZ];
//     int h_proto = eth_hdr->h_proto;

//     snprintf(source_MAC, MAC_ADDR_SZ + 1, "%.2X:%.2X:%.2X:%.2X:%.2X:%.2X", eth_hdr->h_source[0],eth_hdr->h_source[1],eth_hdr->h_source[2],eth_hdr->h_source[3],eth_hdr->h_source[4],eth_hdr->h_source[5]);
//     snprintf(dest_MAC, MAC_ADDR_SZ + 1, "%.2X:%.2X:%.2X:%.2X:%.2X:%.2X", eth_hdr->h_dest[0],eth_hdr->h_dest[1],eth_hdr->h_dest[2],eth_hdr->h_dest[3],eth_hdr->h_dest[4],eth_hdr->h_dest[5]);

//     cout << "source MAC address: " << source_MAC << '\n';
//     cout << "destination MAC address: " << dest_MAC << '\n';
//     cout << "next layer protocol: " << h_proto << '\n';
//     cout << '\n';

//     delete[] source_MAC;
//     delete[] dest_MAC;
// }

// void display_packet_l2hdr(struct l2hdr* l2_hdr_ptr) {
//     struct ethhdr* eth_hdr = (*l2_hdr_ptr).eth_hdr;
    
//     display_packet_ETH(eth_hdr);
// }

// void display_packet_IP(struct iphdr* ip_hdr) {
//     char* src_IP = new char[INET_ADDRSTRLEN];
//     char* dest_IP = new char[INET_ADDRSTRLEN];

//     inet_ntop(AF_INET, &ip_hdr->saddr, src_IP, INET_ADDRSTRLEN);
//     inet_ntop(AF_INET, &ip_hdr->daddr, dest_IP, INET_ADDRSTRLEN);

//     cout << "IPv4 header:\n";
//     cout << "version: " << (int)ip_hdr->version << '\n';
//     cout << "header length: " << (int)ip_hdr->ihl << " (bytes: " << (int)ip_hdr->ihl * 4 << ")\n";
//     cout << "total length: " << ntohs(ip_hdr->tot_len) << '\n';
//     cout << "identification: " << ntohs(ip_hdr->id) << '\n';
//     cout << "TTL: " << (int)ip_hdr->ttl << '\n';
//     cout << "protocol: " << (int)ip_hdr->protocol << '\n';
//     cout << "header checksum: " << ntohs(ip_hdr->check) << '\n';
//     cout << "source IP address: " << src_IP << '\n';
//     cout << "destination IP address: " << dest_IP << '\n';

//     cout << "tos: " << (int)ip_hdr->tos << '\n';
//     cout << "flag offset: " << ntohs(ip_hdr->frag_off) << '\n';

//     cout << '\n';

//     delete[] src_IP;
//     delete[] dest_IP;
// }

// void display_packet_UDP(struct udphdr* udp_hdr) {
//     cout << "UDP header: \n";
//     cout << "header length: " << sizeof(udphdr) << '\n';
//     cout << "source port: " << ntohs(udp_hdr->source) << '\n';
//     cout << "destination port: " << ntohs(udp_hdr->dest) << '\n';
//     cout << "len: " << ntohs(udp_hdr->len) << '\n';
//     cout << "checksum: " << ntohs(udp_hdr->check) << '\n';

//     cout << '\n';
// }

// void console_packet_payload_test(int remaining_data, char** data) {
//     char* binary_data;
//     char* tmp;

//     cout << "remaining data: " << remaining_data << '\n';

//     int binary_data_len = remaining_data * 3 + (int)ceil((double)(remaining_data / 16)) + 3;

//     binary_data = new char[binary_data_len];
//     cout << "user application data: \n";

//     int pos = 0;

//     tmp = new char[2];

//     for(int i = 0; i < remaining_data; ++i) {
//         if(i > 0 && i % 16 == 0) {
//             binary_data[pos++] = '\n';
//         }
//         else if(i > 0) {
//             binary_data[pos++] = ' ';
//         }
//         snprintf(tmp, 3, "%.2X", (*data)[i]);

//         binary_data[pos++] = tmp[0];
//         binary_data[pos++] = tmp[1];
//     }
//     binary_data[pos] = '\0';
//     cout << binary_data << '\n';

//     cout << '\n';

//     delete[] tmp;
//     delete[] binary_data;
// }

// int main() {
//     int sock_r;
//     if(open_socket(&sock_r) == -1) return 1;

//     cout << "sock_r = " << sock_r << '\n';

//     int if_index;
//     char* if_source_MAC = new char[MAC_ADDR_SZ];
//     char* if_source_IP = new char[MAC_ADDR_SZ];

//     int total_len = 0;

//     char* if_name = "lo";

//     //print some information of network interface (index, MAC, IP)
//     if(get_if_index(sock_r, if_name, &if_index) == -1) return 1;
//     cout << "index for " << if_name << ": " << if_index << '\n';

//     if(get_if_MAC(sock_r, if_name, if_source_MAC) == -1) return 1;
//     cout << "source MAC: " << if_source_MAC << '\n';

//     if(get_if_IP(sock_r, if_name, if_source_IP) == -1) return 1;
//     cout << "source IP: " << if_source_IP << '\n';
//     //finish

//     // construct layer header

//     char* sendbuff = new char[MAX_SZ];
//     memset(sendbuff, 0, MAX_SZ);

//     if(construct_l2(sock_r, if_name, sendbuff, &total_len) == -1) return 1;
//     if(construct_l3(sock_r, if_name, sendbuff, &total_len) == -1) return 2;
//     if(construct_l4(sendbuff, &total_len) == -1) return 3;
//     if(add_payload(sendbuff, &total_len) == -1) return 4;

//     struct udphdr* udp_hdr = (struct udphdr*) (sendbuff + sizeof(struct ethhdr) + sizeof(struct iphdr));
//     udp_hdr->len = htons((total_len - sizeof(struct iphdr) - sizeof(struct ethhdr)));

//     struct iphdr* ip_hdr = (struct iphdr*) (sendbuff + sizeof(struct ethhdr));
//     ip_hdr->tot_len = htons((total_len - sizeof(struct ethhdr)));

//     cout << "construct packet success\n";
//     cout << "\ntest\n\n";

//     struct ethhdr* eth_hdr = (struct ethhdr*) (sendbuff);
//     ip_hdr = (struct iphdr*) (sendbuff + sizeof(struct ethhdr));
//     udp_hdr = (struct udphdr*) (sendbuff + sizeof(struct ethhdr) + sizeof(struct iphdr));
//     char* data = (sendbuff + sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct udphdr));

//     display_packet_ETH(eth_hdr);
//     display_packet_IP(ip_hdr);
//     display_packet_UDP(udp_hdr);
//     console_packet_payload_test(5, &data);

//     struct sockaddr_ll saddr_ll;
//     saddr_ll.sll_ifindex = if_index;
//     saddr_ll.sll_halen = ETH_ALEN;
//     saddr_ll.sll_addr[0] = DESTMAC0;
//     saddr_ll.sll_addr[1] = DESTMAC1;
//     saddr_ll.sll_addr[2] = DESTMAC2;
//     saddr_ll.sll_addr[3] = DESTMAC3;
//     saddr_ll.sll_addr[4] = DESTMAC4;
//     saddr_ll.sll_addr[5] = DESTMAC5;
    
//     int send_len = sendto(sock_r, sendbuff, total_len, 0, (struct sockaddr*)&saddr_ll, sizeof(struct sockaddr_ll));
//     if(send_len < 0) {
//         perror("send data to raw socket failed");
//         return 5;
//     }

//     cout << "send_len: " << send_len << '\n';

//     //finish

//     close(sock_r);
// }