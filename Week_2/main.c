#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Sử dụng: %s <địa chỉ IP hoặc tên miền>\n", argv[0]);
        return 1;
    }

    struct addrinfo hints, *result, *ptr;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC; // Hỗ trợ cả IPv4 và IPv6
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(argv[1], NULL, &hints, &result);
    if (status != 0) {
        fprintf(stderr, "Không thể phân giải tên miền hoặc địa chỉ IP.\n");
        return 1;
    }

    printf("Result:\n");
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
        void *addr;
        char ip_address[INET6_ADDRSTRLEN];

        if (ptr->ai_family == AF_INET) { // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)ptr->ai_addr;
            addr = &(ipv4->sin_addr);
        } else { // IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)ptr->ai_addr;
            addr = &(ipv6->sin6_addr);
        }

        inet_ntop(ptr->ai_family, addr, ip_address, sizeof(ip_address));
        printf("%s\n", ip_address);
    }

    freeaddrinfo(result);
    return 0;
}
