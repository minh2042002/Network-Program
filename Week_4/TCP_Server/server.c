#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

void write_log(const char *log_filename, const char *log_entry) {
    FILE *log_file = fopen(log_filename, "a");
    if (log_file) {
        time_t current_time;
        char *time_string;
        current_time = time(NULL);
        time_string = ctime(&current_time);
        time_string[strlen(time_string) - 1] = '\0';  // Remove newline character from time string
        fprintf(log_file, "[%s]%s\n", time_string, log_entry);
        fclose(log_file);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Sử dụng: %s <Port_Number> <Directory_name>\n", argv[0]);
        return 1;
    }

    int port_number = atoi(argv[1]);
    char *directory_name = argv[2];

    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Không thể tạo socket");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_number);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Không thể bind socket");
        return 1;
    }

    listen(server_socket, 5);

    char buffer[256];
    FILE *file;
    int bytes_received;

    while (1) {
        int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket < 0) {
            perror("Lỗi khi chấp nhận kết nối");
            continue;
        }

        printf("[+] Đã kết nối với %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        send(client_socket, "+OK Welcome to file server\r\n", 30, 0);

        bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        buffer[bytes_received] = '\0';

        char log_entry[256];
        sprintf(log_entry, "[%s:%d]$%s", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);
        write_log("log_MSSV.txt", log_entry);

        char file_name[128];
        int file_size;
        sscanf(buffer, "UPLD %s %d", file_name, &file_size);

        file = fopen(file_name, "wb");
        if (file == NULL) {
            perror("Lỗi khi mở file");
            close(client_socket);
            continue;
        }

        send(client_socket, "+OK Please send file\r\n", 26, 0);

        bytes_received = 0;
        while (bytes_received < file_size) {
            int bytes = recv(client_socket, buffer, sizeof(buffer), 0);
            fwrite(buffer, 1, bytes, file);
            bytes_received += bytes;
        }

        fclose(file);
        send(client_socket, "+OK Successful upload\r\n", 24, 0);
        close(client_socket);
    }

    close(server_socket);
    return 0;
}
