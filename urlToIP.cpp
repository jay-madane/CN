#include <iostream>
#include <cstring>
#include <netdb.h>
#include <arpa/inet.h>

int main() {
    char url[100];
    std::cout << "Enter a URL (e.g., example.com): ";
    std::cin >> url;

    struct addrinfo hints, *result, *p;
    int status;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;  // Use AF_INET for IPv4, AF_INET6 for IPv6
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo(url, NULL, &hints, &result)) != 0) {
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

        char ipstr[INET6_ADDRSTRLEN];
        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        std::cout << "URL: " << url << " corresponds to IP Address " << ipstr << " (" << ipVer << ")" << std::endl;
    }

    freeaddrinfo(result);
    return 0;
}
