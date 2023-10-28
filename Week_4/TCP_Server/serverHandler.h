#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H

int createSocket();
int bindServer(int port_number, int server_socket);
void write_log(struct sockaddr_in client_addr, const char *buffer);

#endif