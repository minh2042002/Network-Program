#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>



int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Sử dụng: %s <Port_Number> <Directory_name>\n", argv[0]);
        return 1;
    }

    int port_number = atoi(argv[1]);
    char *directory_name = argv[2];

    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    int server_socket = createSocket();
    if (server_socket == -1) {
        return 1;
    }

    int bind = bindServer(port_number, server_socket);
    if (bind == 0) {
        return 1;
    }

    /// Server handler

    listen(server_socket, 5);

    char buffer[256];
    FILE *file;
    int bytes_received;

    while (1) {
        // connect with a client
        int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket < 0) {
            perror("Lỗi khi chấp nhận kết nối");
            continue;
        }

        // connect is success
        printf("[+] Đã kết nối với %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        send(client_socket, "+OK Welcome to file server\r\n", 30, 0);
        sscanf("+OK Welcome to file server\r\n", "%s", buffer);
        write_log(client_addr, buffer);

        // request from client
        bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        buffer[bytes_received] = '\0';

        write_log(client_addr, buffer);

        char file_name[128];
        int file_size;
        sscanf(buffer, "UPLD %s %d", file_name, &file_size);
       
        // Create new file and wait send file from client
        file = fopen(directory_name+"/"+file_name, "wb");
        if (file == NULL) {
            perror("Lỗi khi mở file");
            close(client_socket);
            continue;
        }

        send(client_socket, "+OK Please send file\r\n", 26, 0);

        // read file and write into new file
        bytes_received = 0;
        while (bytes_received < file_size) {
            int bytes = recv(client_socket, buffer, sizeof(buffer), 0);
            fwrite(buffer, 1, bytes, file);
            bytes_received += bytes;
        }

        fclose(file);


        send(client_socket, "+OK Successful upload\r\n", 24, 0);
        sscanf("+OK Successful upload\r\n", "%s", buffer);
        write_log(client_addr, buffer);

        close(client_socket);
    }

    close(server_socket);
    return 0;
}
