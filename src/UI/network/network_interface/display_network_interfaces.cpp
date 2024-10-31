#include <iostream>
#include <vector>
#include "display_network_interfaces.h"
#include "network_interface.h"

void display_network_interfaces() {
    for(int i = 0; i < interfaces_ipv4.size(); ++i) {
        network_interface_ipv4 cur = interfaces_ipv4.at(i);
        cout << "IPv4" << ", interface name: " << cur.if_name << ", IP address: " << cur.ipaddress_decimal << ", netmask: " << cur.netmask_decimal << '\n';
    }

    cout << '\n';

    for(int i = 0; i < interfaces_ipv6.size(); ++i) {
        network_interface_ipv6 cur = interfaces_ipv6.at(i);
        cout << "IPv6" << ", interface name: " << cur.if_name << ", IP address: " << cur.ipaddress_decimal << ", netmask: " << cur.netmask_decimal << ", scope id = " << cur.scope_id << '\n';
    }

    for(int i = 0; i < interfaces_ipv4.size(); ++i) {
        network_interface_ipv4 cur = interfaces_ipv4.at(i);
        delete[] cur.if_name;
        delete[] cur.ipaddress_decimal;
        delete[] cur.netmask_decimal;
    }

    for(int i = 0; i < interfaces_ipv6.size(); ++i) {
        network_interface_ipv6 cur = interfaces_ipv6.at(i);
        delete[] cur.if_name;
        delete[] cur.ipaddress_decimal;
    }
}
