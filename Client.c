#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 9999

int main(int argc, char **argv){

//	char sms;
	int delay = atoi(argv[1]);
	char buffer = '#';
	int clientSocket, ret;
	struct sockaddr_in serverAddr;
	//char buffer[1024];
    int *value = calloc(1, sizeof(int));
    int send_value;

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0){
		printf("Error in connection.\n");
		exit(1);
	}
	printf("Client Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("Error in connection.\n");
		exit(1);
	}
	printf("Connected to Server.\n");

	send(clientSocket, &delay, sizeof(int), 0);

	while(2){

		recv(clientSocket, &buffer, sizeof(int), 0);
		//perror("recv");
		printf("%d ", buffer);
		fflush(stdout);
		sleep(delay);
		send(clientSocket, &buffer, sizeof(int), 0);

	}



}
