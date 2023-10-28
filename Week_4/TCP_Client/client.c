#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Sử dụng: %s <IP_Addr> <Port_Number>\n", argv[0]);
        return 1;
    }

    char *server_ip = argv[1];
    int port_number = atoi(argv[2]);

    struct sockaddr_in server_addr;
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Không thể tạo socket");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_number);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Không thể kết nối đến server");
        return 1;
    }

    char buffer[256];
    int bytes_received;

    bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    buffer[bytes_received] = '\0';
    printf("%s", buffer);

    char file_path[128];
    int file_size;
    while (1) {
        printf("Nhập đường dẫn file hoặc nhấn Enter để kết thúc: ");
        fgets(file_path, sizeof(file_path), stdin);
        file_path[strcspn(file_path, "\n")] = '\0'; // Xóa ký tự newline từ fgets

        if (strlen(file_path) == 0) {
            break;
        }

        FILE *file = fopen(file_path, "rb");
        if (file == NULL) {
            perror("Không thể mở file");
            continue;
        }

        fseek(file, 0, SEEK_END);
        file_size = ftell(file);
        fseek(file, 0, SEEK_SET);

        sprintf(buffer, "UPLD %s %d", file_path, file_size);
        send(client_socket, buffer, strlen(buffer), 0);

        bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        buffer[bytes_received] = '\0';
        printf("%s", buffer);

        while (!feof(file)) {
            bytes_received = fread(buffer, 1, sizeof(buffer), file);
            send(client_socket, buffer, bytes_received, 0);
        }

        fclose(file);

        bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        buffer[bytes_received] = '\0';
        printf("%s", buffer);
    }

    close(client_socket);
    return 0;
}
