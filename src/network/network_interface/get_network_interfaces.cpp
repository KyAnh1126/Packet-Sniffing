#include <arpa/inet.h>
#include <cerrno>
#include <ifaddrs.h>
#include <iostream>
#include <net/if.h>
#include <string>
#include <string.h>
#include <sysexits.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <vector>
#include <unistd.h>

#include <math.h>

#include "network_interface.h"

using namespace std;

vector<network_interface_ipv4> interfaces_ipv4;
vector<network_interface_ipv6> interfaces_ipv6;

void get_network_interface_ipv4(struct ifaddrs* ptr_entry) {
    int if_name_len = strlen(ptr_entry->ifa_name);

    char* ipaddress_decimal;
    char* netmask_decimal;

    network_interface_ipv4 cur;

    cur.if_name = new char[if_name_len + 1];
    strncpy(cur.if_name, ptr_entry->ifa_name, if_name_len);
    cur.if_name[if_name_len] = '\0';

    cur.ipaddress_decimal = new char[INET_ADDRSTRLEN + 1];
    cur.netmask_decimal = new char[INET_ADDRSTRLEN + 1];

    if(ptr_entry->ifa_addr != NULL) {
        struct sockaddr_in* t_ifa_addr = (struct sockaddr_in*)ptr_entry->ifa_addr;
        struct in_addr t_sin_addr = t_ifa_addr->sin_addr;

        char buffer[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &t_sin_addr, buffer, INET_ADDRSTRLEN);

        strncpy(cur.ipaddress_decimal, buffer, INET_ADDRSTRLEN);
        cur.ipaddress_decimal[INET_ADDRSTRLEN] = '\0';
    }

    if(ptr_entry->ifa_netmask != NULL) {
        struct sockaddr_in* t_ifa_netmask = (struct sockaddr_in*)ptr_entry->ifa_netmask;
        struct in_addr t_sin_addr = t_ifa_netmask->sin_addr;

        char buffer[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &t_sin_addr, buffer, INET_ADDRSTRLEN);

        strncpy(cur.netmask_decimal, buffer, INET_ADDRSTRLEN);
        cur.netmask_decimal[INET_ADDRSTRLEN] = '\0';
    }

    interfaces_ipv4.push_back(cur);
}

void get_network_interface_ipv6(struct ifaddrs* ptr_entry) {
    int if_name_len = strlen(ptr_entry->ifa_name);

    network_interface_ipv6 cur;

    cur.if_name = new char[if_name_len + 1];
    strncpy(cur.if_name, ptr_entry->ifa_name, if_name_len);
    cur.if_name[if_name_len] = '\0';

    cur.ipaddress_decimal = new char[INET6_ADDRSTRLEN + 1];
    cur.netmask_decimal = new char[INET6_ADDRSTRLEN + 1];

    if(ptr_entry->ifa_addr != NULL) {
        struct sockaddr_in6* t_ifa_addr = (struct sockaddr_in6*)ptr_entry->ifa_addr;
        struct in6_addr t_sin6_addr = t_ifa_addr->sin6_addr;

        char buffer[INET6_ADDRSTRLEN];
        inet_ntop(AF_INET6, &t_sin6_addr, buffer, INET6_ADDRSTRLEN);

        strncpy(cur.ipaddress_decimal, buffer, INET6_ADDRSTRLEN);
        cur.ipaddress_decimal[INET6_ADDRSTRLEN] = '\0';

        cur.scope_id = t_ifa_addr->sin6_scope_id;
    }

    if(ptr_entry->ifa_netmask != NULL) {
        struct sockaddr_in6* t_ifa_netmask = (struct sockaddr_in6*)ptr_entry->ifa_netmask;
        struct in6_addr t_sin6_addr = t_ifa_netmask->sin6_addr;

        char buffer[INET6_ADDRSTRLEN];
        inet_ntop(AF_INET6, &t_sin6_addr, buffer, INET6_ADDRSTRLEN);

        strncpy(cur.netmask_decimal, buffer, INET6_ADDRSTRLEN);
        cur.netmask_decimal[INET6_ADDRSTRLEN] = '\0';
    }

    interfaces_ipv6.push_back(cur);
}

void get_network_interfaces() {
    struct ifaddrs* ptr_ifaddrs = NULL;
    struct ifaddrs* ptr_entry;

    int getifaddrs_ret = getifaddrs(&ptr_ifaddrs);
    if(getifaddrs_ret != 0) {
        perror("get interface address failed");
        return;
    }

    ptr_entry = ptr_ifaddrs;

    for(; ptr_entry != NULL; ptr_entry = ptr_entry->ifa_next) {
        char* if_name;
        char* ipaddress_decimal;
        char* netmask_decimal;

        sa_family_t address_family = ptr_entry->ifa_addr->sa_family;

        if(address_family == AF_INET) {
            get_network_interface_ipv4(ptr_entry);
        }

        if(address_family == AF_INET6) {
            get_network_interface_ipv6(ptr_entry);
        }
    }
}