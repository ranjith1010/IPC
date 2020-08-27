// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080
int main(int argc, char
    const * argv[]) {
    int server_fd, valread;
    int clients[10];
    int size = 0;
    struct sockaddr_in address;
    int opt = 1;
    int conn;
    int addrlen = sizeof(address);

    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, & opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr * ) & address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    char message[100];
    while(conn = accept(server_fd, (struct sockaddr *)NULL, NULL)) {
    int pid;
    if((pid = fork()) == 0) {
    	int n=0;
        while (recv(conn, &n, sizeof(int), 0)>0 && recv(conn,&message,n,0)>0) {
	    //message[n]='\0';
            printf("Message Received from Client-%d : ",conn);
            for(int i=0; i<n; ++i)
            	printf("%c",message[i]);
            printf("\n");
      	    send(conn, message, n, 0);
            
        }
        exit(0);
    }
}
    return 0;
}
