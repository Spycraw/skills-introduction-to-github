#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
#include<arpa/inet.h>
int main() {
	char *ip = "127.0.0.1";
	int port = 5566;

	int sock;
	struct sockaddr_in addr;
	socklen_t addr_size;
	char buffer[1024];
	int n;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		printf("[-]Socket error");
		exit(1);
	}
	printf("[+]TCP client socket created.\n");
	addr.sin_family = AF_INET;
	addr.sin_port = port;
	addr.sin_addr.s_addr = inet_addr(ip);
	connect(sock, (struct sockaddr*)&addr, sizeof(addr));
	printf("Connected to the server.\n");
	while(1) {
		bzero(buffer, 1024);
		printf("Enter message: ");
		fgets(buffer,1024,stdin);
		printf("Client: %s\n", buffer);
		send(sock, buffer, strlen(buffer), 0);
		bzero(buffer, 1024);
		recv(sock, buffer, sizeof(buffer), 0);
		printf("Server: %s\n",buffer);
		if(!strcmp(buffer,"exit\n")) {
			exit(1);
		}
	}
	close(sock);
	printf("Disconnected from the server.\n");
	return 0;

}