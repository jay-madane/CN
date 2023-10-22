#include <iostream>
#include <cstring>
#include <netdb.h>
#include <arpa/inet.h>

int main() {
    char ip_address[100];
    std::cout << "Enter an IP address: ";
    std::cin >> ip_address;

    struct addrinfo hints, *result, *p;
    int status;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;  // Use AF_INET for IPv4, AF_INET6 for IPv6
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo(ip_address, NULL, &hints, &result)) != 0) {
        std::cerr << "getaddrinfo: " << gai_strerror(status) << std::endl;
        return 1;
    }

    for (p = result; p != NULL; p = p->ai_next) {
        void *addr;
        std::string ipVer;

        if (p->ai_family == AF_INET) { // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipVer = "IPv4";
        } else { // IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipVer = "IPv6";
        }

        char hostname[NI_MAXHOST];
        if (getnameinfo(p->ai_addr, p->ai_addrlen, hostname, NI_MAXHOST, NULL, 0, NI_NAMEREQD) == 0) {
            std::cout << "IP Address: " << ip_address << " corresponds to " << hostname << " (" << ipVer << ")" << std::endl;
        } else {
            std::cerr << "Couldn't resolve the hostname for the provided IP address." << std::endl;
        }
    }

    freeaddrinfo(result);
    return 0;
}
