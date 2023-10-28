#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include "serverHandler.h"


/// @brief create new socket
/// @return a socket descriptor return -1 if create fail)
int createSocket()
{
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        perror("Không thể tạo socket");
    }

    return server_socket;
}

/// @brief bind server with port and socket descriptor
/// @param port_number port server
/// @param server_socket  a socket descriptor
/// @return 0 - if bind fail, 1- if bind is success
int bindServer(int port_number, int server_socket)
{
    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_number);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Không thể bind socket");
        return 0;
    }

    return 1;
}

/// @brief write log to file 
/// @param client_addr contain ip address and port of client
/// @param buffer information
void write_log(struct sockaddr_in client_addr, const char *buffer)
{
    char log_entry[256];
    sprintf(log_entry, "[%s:%d]$%s", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);

    FILE *log_file = fopen("log_20205003.txt", "a");
    if (log_file)
    {
        time_t current_time;
        char *time_string;
        current_time = time(NULL);
        time_string = ctime(&current_time);
        time_string[strlen(time_string) - 1] = '\0'; // Remove newline character from time string
        fprintf(log_file, "[%s]%s\n", time_string, log_entry);
        fclose(log_file);
    }
}