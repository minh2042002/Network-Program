#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "service.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Cú pháp: %s <địa chỉ IPv4 hoặc tên miền>\n", argv[0]);
        return 1;
    }

    if (is_valid_ipv4(argv[1])) {
        findDomainNameByIPAddress(argv[1]);
    } else if (is_valid_domain(argv[1])) {
        findIPAddressByDomainName(argv[1]);
    } else {
        printf("Chuỗi nhập không hợp lệ.\n");
    }

    return 0;
}
