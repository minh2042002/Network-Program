#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "service.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Sử dụng: %s <địa chỉ IP hoặc tên miền>\n", argv[0]);
        return 1;
    }

    if (is_valid_ip(argv[1])) {
        findDomainNameByIPAddress(argv[1]);
    } else if (is_valid_domain(argv[1])) {
        findIPAddressByDomainName(argv[1]);
    } else {
        printf("Chuỗi nhập không hợp lệ.\n");
    }

    return 0;
}
