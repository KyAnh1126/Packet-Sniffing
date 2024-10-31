// #include <stdio.h>
// #include <linux/if_ether.h>
// #include <linux/ip.h>
// #include <linux/ipv6.h>
// #include <linux/tcp.h>
// #include <linux/udp.h>
// #include <sys/socket.h>
// #include <arpa/inet.h>
// #include <cstring>
// #include <unistd.h>
// #include <math.h>

// #include <iostream>
// using namespace std;

// #define BUF_SZ 65536
// #define MAC_ADDR_SZ 17

// #define ETH_IP_DEC 8
// #define ETH_IPV6_DEC 56710

// void get_packets() {
//     int sock_r;
//     sock_r = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

//     if(sock_r < 0) {
//         perror("open socket for getting loopback packet");
//         return;
//     }

//     cout << "sock_r = " << sock_r << '\n'; 

//     while(1) {
//         char* buffer = new char[BUF_SZ];

//         memset(buffer, 0, BUF_SZ);
        
//         struct sockaddr saddr;
//         int saddr_len = sizeof(saddr);

//         //copy network packet to a buffer
//         //buffer contains payload + l2, l3, l4 header
//         int buflen = recvfrom(sock_r, buffer, BUF_SZ, 0, &saddr, (socklen_t*)&saddr_len);
        
//         if(buflen < 0) {
//             perror("recv loopback packet from sock_r");
//             close(sock_r);
//             return;
//         }

//         cout << "buflen = " << buflen << '\n';
//         cout << '\n';

//         // using ethhdr struct for print ethernet header

//         struct ethhdr* eth = (struct ethhdr*)buffer;
//         char* src_MAC_address = new char[MAC_ADDR_SZ];
//         char* dest_MAC_address = new char[MAC_ADDR_SZ];
//         int next_layer_proto = eth->h_proto;

//         int ethhdr_len = sizeof(ethhdr);

//         cout << "ethernet header:\n";

//         snprintf(src_MAC_address, MAC_ADDR_SZ + 1, "%.2X:%.2X:%.2X:%.2X:%.2X:%.2X", eth->h_source[0],eth->h_source[1],eth->h_source[2],eth->h_source[3],eth->h_source[4],eth->h_source[5]);
//         snprintf(dest_MAC_address, MAC_ADDR_SZ + 1, "%.2X:%.2X:%.2X:%.2X:%.2X:%.2X", eth->h_dest[0],eth->h_dest[1],eth->h_dest[2],eth->h_dest[3],eth->h_dest[4],eth->h_dest[5]);

//         cout << "source MAC address: " << src_MAC_address << '\n';
//         cout << "destination MAC address: " << dest_MAC_address << '\n';
//         cout << "next layer protocol: " << next_layer_proto << '\n';
//         cout << '\n';

//         delete[] src_MAC_address;
//         delete[] dest_MAC_address;

//         //finish

//         // using iphdr struct for print ip header


//         int iphdr_len;

//         bool is_TCP_packet, is_UDP_packet;
//         is_TCP_packet = is_UDP_packet = 0;

//         if(next_layer_proto == ETH_IP_DEC) { 

//             char* src_IP_address = new char[INET_ADDRSTRLEN];
//             char* dest_IP_address = new char[INET_ADDRSTRLEN];
//             struct iphdr* ip;
            
//             ip = (struct iphdr*) (buffer + ethhdr_len); 

//             iphdr_len = ip->ihl * 4;

//             inet_ntop(AF_INET, &ip->saddr, src_IP_address, INET_ADDRSTRLEN);
//             inet_ntop(AF_INET, &ip->daddr, dest_IP_address, INET_ADDRSTRLEN);

//             cout << "IPv4 header:\n";
//             cout << "version: " << (int)ip->version << '\n';
//             cout << "header length: " << (int)ip->ihl << " (bytes: " << (int)ip->ihl * 4 << ")\n";
//             cout << "total length: " << ntohs(ip->tot_len) << '\n';
//             cout << "identification: " << ntohs(ip->id) << '\n';
//             cout << "TTL: " << (int)ip->ttl << '\n';
//             cout << "protocol: " << (int)ip->protocol << '\n';
//             cout << "header checksum: " << ntohs(ip->check) << '\n';
//             cout << "source IP address: " << src_IP_address << '\n';
//             cout << "destination IP address: " << dest_IP_address << '\n';

//             cout << "tos: " << (int)ip->tos << '\n';
//             cout << "flag offset: " << ntohs(ip->frag_off) << '\n';

//             cout << '\n';

//             if(ip->protocol == 6) is_TCP_packet = true;
//             if(ip->protocol == 17) is_UDP_packet = true;

//             delete[] src_IP_address;
//             delete[] dest_IP_address;
//         }

//         if(next_layer_proto == ETH_IPV6_DEC) { 

//             char* src_IPv6_address = new char[INET6_ADDRSTRLEN];
//             char* dest_IPv6_address = new char[INET6_ADDRSTRLEN];
//             struct ipv6hdr* ipv6;

//             ipv6 = (struct ipv6hdr*) (buffer + ethhdr_len);

//             iphdr_len = sizeof(struct ipv6hdr);

//             inet_ntop(AF_INET6, &ipv6->saddr, src_IPv6_address, INET6_ADDRSTRLEN);
//             inet_ntop(AF_INET6, &ipv6->daddr, dest_IPv6_address, INET6_ADDRSTRLEN);

//             cout << "IPv6 header:\n";
//             cout << "version: " << (int)ipv6->version << '\n';
//             cout << "priority: " << (int)ipv6->priority << '\n';
//             cout << "header length: " << iphdr_len << " bytes\n";
//             cout << "payload length: " << ntohs(ipv6->payload_len) << '\n';
//             cout << "next header: " << (int)ipv6->nexthdr << '\n';
//             cout << "hop limit (TTL): " << (int)ipv6->hop_limit << '\n';
//             cout << "source IPv6 address: " << src_IPv6_address << '\n';
//             cout << "destination IPv6 address: " << dest_IPv6_address << '\n';

//             cout << '\n';

//             if(ipv6->nexthdr == 6) is_TCP_packet = 1;
//             if(ipv6->nexthdr == 17) is_UDP_packet = 1;

//             delete[] src_IPv6_address;
//             delete[] dest_IPv6_address;
//         }

//         //finish

//         // using tcphdr for print tcp header

//         int transport_layer_header_len;

//         if(is_TCP_packet) { 

//             struct tcphdr* tcp;
//             tcp = (struct tcphdr*) (buffer + ethhdr_len + iphdr_len);
//             transport_layer_header_len = sizeof(struct tcphdr);

//             cout << "TCP header: \n";
//             cout << "header length: " << transport_layer_header_len << '\n';
//             cout << "source port: " << ntohs(tcp->source) << '\n';
//             cout << "destination port: " << ntohs(tcp->dest) << '\n';
//             cout << "seq: " << ntohs(tcp->seq) << '\n';
//             cout << "ack_seq: " << ntohs(tcp->ack_seq) << '\n';
//             cout << "checksum: " << ntohs(tcp->check) << '\n';
//             cout << "window: " << ntohs(tcp->window) << '\n';

//             cout << '\n';
//         }

//         if(is_UDP_packet) {
//             struct udphdr* udp;
//             udp = (struct udphdr*) (buffer + ethhdr_len + iphdr_len);
//             transport_layer_header_len = sizeof(struct udphdr);

//             cout << "UDP header: \n";
//             cout << "header length: " << transport_layer_header_len << '\n';
//             cout << "source port: " << ntohs(udp->source) << '\n';
//             cout << "destination port: " << ntohs(udp->dest) << '\n';
//             cout << "len: " << ntohs(udp->len) << '\n';
//             cout << "checksum: " << ntohs(udp->check) << '\n';

//             cout << '\n';
//         }

//         // finish

//         // getting user application data

//         if(is_TCP_packet || is_UDP_packet) {

//             cout << "Application layer: \n";

//             int remaining_data;
//             char* user_data = buffer + ethhdr_len + iphdr_len + transport_layer_header_len;
//             char* binary_data;
//             char* tmp;

//             remaining_data = buflen - (sizeof(struct ethhdr) + iphdr_len + transport_layer_header_len);
//             cout << "remaining data: " << remaining_data << '\n';

//             int binary_data_len = remaining_data * 3 + (int)ceil((double)(remaining_data / 16)) + 1;

//             binary_data = new char[binary_data_len];
//             cout << "user application data: \n";

//             int pos = 0;

//             tmp = new char[2];

//             for(int i = 0; i < remaining_data; ++i) {
//                 if(i > 0 && i % 16 == 0) {
//                     binary_data[pos++] = '\n';
//                 }
//                 else if(i > 0) {
//                     binary_data[pos++] = ' ';
//                 }
//                 snprintf(tmp, 3, "%.2X", user_data[i]);

//                 binary_data[pos++] = tmp[0];
//                 binary_data[pos++] = tmp[1];
//             }
//             binary_data[pos] = '\0';
//             cout << binary_data << '\n';
//         }

//         // finish

//         delete[] buffer;
//         cout << "\n\n";

//         // break;
//     }
    

//     close(sock_r);
// }

// int main() {
//     get_packets();
// }



// struct m_ethhdr {
//     char* source_MAC;
//     char* dest_MAC;
//     int h_proto;
// };

// struct m_iphdr {
//     char* source_IP;
//     char* dest_IP;
//     int ihl;
//     int version;
//     int tot_len;
//     int id;
//     int ttl;
//     int protocol;
//     int check;
// };

// struct m_ipv6hdr {

// };

// struct m_tcphdr {

// };

// struct m_udphdr {

// };











// #include <stdio.h>
// #include <linux/if_ether.h>
// #include <linux/if.h>
// #include <linux/ip.h>
// #include <linux/ipv6.h>
// #include <linux/tcp.h>
// #include <linux/udp.h>
// #include <sys/socket.h>
// #include <sys/ioctl.h>
// #include <arpa/inet.h>
// #include <cstring>
// #include <unistd.h>
// #include <math.h>

// // #include <linux/in.h>

// #include <iostream>
// #include <vector>

// #include "../../../include/network/packet/packet.h"

// using namespace std;

// vector<packet> packets;

// void enum_to_name_l4proto(int l4proto, char** res) {
//     switch(l4proto) {
//         case IPPROTO_TCP: {
//             *res = new char[4];
//             strncpy(*res, "TCP", 4);
//             break;
//         }   
//         case IPPROTO_UDP: {
//             *res = new char[4];
//             strncpy(*res, "UDP", 4);
//             break;
//         }
//         default: {
//             *res = new char[8];
//             strncpy(*res, "UNKNOWN", 8);
//         }
//     }
// }

// void get_packet_l2hdr(struct packet* m_packet_ptr, char** buffer, int* l2hdr_len, int* l3proto) {    
//     (*m_packet_ptr).l2_hdr.eth_hdr = (struct ethhdr*) (*buffer);
//     *l2hdr_len = sizeof(struct ethhdr);
//     *l3proto = (*m_packet_ptr).l2_hdr.eth_hdr->h_proto;
// }

// void get_packet_IP(struct packet* m_packet_ptr, char** buffer, int prev_len, int* l3hdr_len, int* l4proto, char** source_IP, char** dest_IP) {
//     (*m_packet_ptr).l3_hdr.tag = M_IP;
//     (*m_packet_ptr).l3_hdr.ip_hdr = (struct iphdr*) (buffer + prev_len);
//     *l3hdr_len = sizeof(struct iphdr);
//     *l4proto = (*m_packet_ptr).l3_hdr.ip_hdr->protocol;

//     *source_IP = new char[INET_ADDRSTRLEN];
//     *dest_IP = new char[INET_ADDRSTRLEN];

//     inet_ntop(AF_INET, &(*m_packet_ptr).l3_hdr.ip_hdr->saddr, *source_IP, INET_ADDRSTRLEN);
//     inet_ntop(AF_INET, &(*m_packet_ptr).l3_hdr.ip_hdr->daddr, *dest_IP, INET_ADDRSTRLEN);
// }

// void get_packet_IPv6(struct packet* m_packet_ptr, char** buffer, int prev_len, int* l3hdr_len, int* l4proto, char** source_IP, char** dest_IP) {
//     (*m_packet_ptr).l3_hdr.tag = M_IPV6;
//     (*m_packet_ptr).l3_hdr.ipv6_hdr = (struct ipv6hdr*) (buffer + prev_len);
//     *l3hdr_len = sizeof(struct ipv6hdr);
//     *l4proto = (*m_packet_ptr).l3_hdr.ipv6_hdr->nexthdr;

//     *source_IP = new char[INET6_ADDRSTRLEN];
//     *dest_IP = new char[INET6_ADDRSTRLEN];

//     inet_ntop(AF_INET6, &(*m_packet_ptr).l3_hdr.ipv6_hdr->saddr, *source_IP, INET6_ADDRSTRLEN);
//     inet_ntop(AF_INET6, &(*m_packet_ptr).l3_hdr.ipv6_hdr->daddr, *dest_IP, INET6_ADDRSTRLEN);
// }

// void get_packet_l3hdr(int* l3proto, struct packet* m_packet_ptr, char** buffer, int prev_len, int* l3hdr_len, int* l4proto, char** source_IP, char** dest_IP) {
//     if(*l3proto == ETH_IP_DEC) {
//         get_packet_IP(m_packet_ptr, buffer, prev_len, l3hdr_len, l4proto, source_IP, dest_IP);
//     }

//     if(*l3proto == ETH_IPV6_DEC) {
//         get_packet_IPv6(m_packet_ptr, buffer, prev_len, l3hdr_len, l4proto, source_IP, dest_IP);
//     }
// }

// void get_packet_l4hdr(int l4proto, int prev_len, struct packet* m_packet_ptr, char** buffer) {

// }

// void get_packets() {
//     int sock_r;
//     sock_r = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

//     if(sock_r < 0) {
//         perror("open socket for getting loopback packet");
//         return;
//     }

//     cout << "sock_r = " << sock_r << '\n'; 

//     while(1) {
//         char* buffer = new char[BUF_SZ];

//         memset(buffer, 0, BUF_SZ);
        
//         struct sockaddr saddr;
//         int saddr_len = sizeof(saddr);

//         //copy network packet to a buffer
//         //buffer contains payload + l2, l3, l4 header
//         int buflen = recvfrom(sock_r, buffer, BUF_SZ, 0, &saddr, (socklen_t*)&saddr_len);
        
//         if(buflen < 0) {
//             perror("recv loopback packet from sock_r");
//             close(sock_r);
//             return;
//         }

//         cout << "buflen = " << buflen << '\n';
//         cout << '\n';

//         struct packet recv_packet;
//         int l2hdr_len, l3hdr_len, l4hdr_len;
//         int l3proto, l4proto;
//         l3proto = l4proto = -1;

//         recv_packet.id = packets.size() + 1;

//         //ethernet header


//         //network header

//         char* source_IP;
//         char* dest_IP;

//         if(l3proto == ETH_IP_DEC) {
//             recv_packet.l3_hdr.tag = M_IP;
//             recv_packet.l3_hdr.ip_hdr = (struct iphdr*) (buffer + l2hdr_len);
//             l3hdr_len = sizeof(struct iphdr);
//             l4proto = recv_packet.l3_hdr.ip_hdr->protocol;

//             source_IP = new char[INET_ADDRSTRLEN];
//             dest_IP = new char[INET_ADDRSTRLEN];

//             inet_ntop(AF_INET, &recv_packet.l3_hdr.ip_hdr->saddr, source_IP, INET_ADDRSTRLEN);
//             inet_ntop(AF_INET, &recv_packet.l3_hdr.ip_hdr->daddr, dest_IP, INET_ADDRSTRLEN);
//         }

//         if(l3proto == ETH_IPV6_DEC) {
//             recv_packet.l3_hdr.tag = M_IPV6;
//             recv_packet.l3_hdr.ipv6_hdr = (struct ipv6hdr*) (buffer + l2hdr_len);
//             l3hdr_len = sizeof(struct ipv6hdr);
//             l4proto = recv_packet.l3_hdr.ipv6_hdr->nexthdr;

//             source_IP = new char[INET6_ADDRSTRLEN];
//             dest_IP = new char[INET6_ADDRSTRLEN];

//             inet_ntop(AF_INET6, &recv_packet.l3_hdr.ipv6_hdr->saddr, source_IP, INET6_ADDRSTRLEN);
//             inet_ntop(AF_INET6, &recv_packet.l3_hdr.ipv6_hdr->daddr, dest_IP, INET6_ADDRSTRLEN);
//         }

//         //transport layer
//         if(l4proto == IPPROTO_TCP) {
//             recv_packet.l4_hdr.tag = M_TCP;
//             recv_packet.l4_hdr.tcp_hdr = (struct tcphdr*) (buffer + l2hdr_len + l3hdr_len);
//             l4hdr_len = sizeof(struct tcphdr);
//         }

//         if(l4proto == IPPROTO_UDP) {
//             recv_packet.l4_hdr.tag = M_UDP;
//             recv_packet.l4_hdr.udp_hdr = (struct udphdr*) (buffer + l2hdr_len + l3hdr_len);
//             l4hdr_len = sizeof(struct udphdr);
//         }

//         //application layer
//         if(l4proto == IPPROTO_TCP || l4proto == IPPROTO_UDP) {
//             recv_packet.user_data.data = (buffer + l2hdr_len + l3hdr_len + l4hdr_len);
//         }

//         char* proto_name;
//         enum_to_name_l4proto(l4proto, &proto_name);

//         cout << recv_packet.id << ", " << source_IP << ", " << dest_IP << ", " << proto_name << ", " << buflen << '\n';

//         packets.push_back(recv_packet);

//         delete[] buffer;
//         delete[] source_IP;
//         delete[] dest_IP;
//         delete[] proto_name;
//     }
//     close(sock_r);
// }

// int main() {
//     get_packets();
// }