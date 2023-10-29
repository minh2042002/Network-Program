run: client server
client:
	gcc -std=c11 -o TCP_Client/client TCP_Client/client.c TCP_Client/clientHandler.c TCP_Client/clientHandler.h
server:
	gcc -std=c11 -o TCP_Server/server TCP_Server/server.c TCP_Server/serverHandler.h TCP_Server/serverHandler.c
clean:
	rm -f $(TARGET)