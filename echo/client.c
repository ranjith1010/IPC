#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <string.h> 
#define PORT 8080 

int main(int argc, char const *argv[]) 
{ 
	int sock = 0, valread; 
	struct sockaddr_in serv_addr;  

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	}
	char *message = (char*) malloc(100*sizeof(char)); 
	while(1) {
	    printf("Enter a message: ");
	    //scanf("%s",message);
	    size_t max=100;
	    int n = getline(&message,&max,stdin);
	    send(sock, &n, sizeof(int),0);
	    send(sock, &message[0], n, 0);
	    recv(sock, &message[0], n, 0);
	    printf("Message Received : %s",message);
	    //An extra breaking condition can be added here (to terminate the while loop)
	}
		return 0; 
} 

