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
	int s = sizeof(int);
	printf("Connected to Server\n");
	int n;
	printf("Enter number of Elements: ");
	scanf("%d",&n);
	
	if(send(sock,&n,s,0)<0){
		printf("Unable to Send size to Server");
		return -1;
	} 
	printf("Size sent to Server\n");
	
	printf("Enter the Elements .\n");
	int *arr = (int*) malloc(n * s);
	int *sorted = (int*)malloc(n*s);

	for(int i=0; i<n; ++i){
		scanf("%d",&arr[i]);
	}
	
	if(send(sock , arr , n*s , 0 )<0)
	{
		printf("Unable to send to Server\n");
		return -1;
	} 
	printf("Array Sent to Server\n"); 
	
	if(read( sock , sorted , n*s)<0){
		printf("Unable to receive from Server\n");
		return -1;
	} 
	printf("Sorted Array : ");
	for(int i=0; i<n; i++)
		printf("%d ",sorted[i] ); 
	
	printf("\nThe End\n");
	return 0; 
} 

