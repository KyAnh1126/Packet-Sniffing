#pragma once

#include <vector>
using namespace std;

struct network_interface_ipv4 {
    char* if_name;
    char* ipaddress_decimal;
    char* netmask_decimal;
};

struct network_interface_ipv6 {
    char* if_name;
    char* ipaddress_decimal;
    char* netmask_decimal;
    uint32_t scope_id;
};

extern vector<network_interface_ipv4> interfaces_ipv4;
extern vector<network_interface_ipv6> interfaces_ipv6;

void get_network_interface_ipv4(struct ifaddrs* ptr_entry);
void get_network_interface_ipv6(struct ifaddrs* ptr_entry);

void get_network_interfaces();

