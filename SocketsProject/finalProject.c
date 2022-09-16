#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAX 80
#define PORT 80
#define SA struct sockaddr

int main(int argc, char*argv[])
{
	int sockfd,connfd;
	struct sockaddr_in6 servaddr,cli; //adress for representing the IPv6 address-server

        char *message,server_reply[6000], buff[6000],htmlvar[6000];
        int numbytes = 0;
	//socket create and verification
	sockfd=socket(AF_INET6,SOCK_STREAM,0);//AF_INET6-Ipv6, SOCK_STREAM-TCP
	if(sockfd==-1){
		printf("Socket creation failed...\n");
		exit(0);

	}
	else printf("Sockt successfully created...\n");


	// assign IP,PORT-connect to server
	servaddr.sin6_family=AF_INET6;//connection to the IPv6 server
	inet_pton(AF_INET6, "2001:41d0:701:1100::29c8", &servaddr.sin6_addr);//transform from hex to binary the IPv6 server address

       	servaddr.sin6_port=htons(PORT);//stored in network byte order


	//connect the client socket to server socket
	if(connect(sockfd, (SA*)&servaddr, sizeof(servaddr))!=0){
		printf("connection with the server failed..\n");
		exit(0);
	}
	
	else printf("Connected to the server..\n");


	message = "GET / HTTP/1.0\r\n\r\n";
	if ( send (sockfd , message , strlen(message) , 0) <0)//command to obtain the HTML content

	{puts ("Send failed");
		return 1;

        }
      puts("Data send\n") ;

        FILE *fp; //storing HTML content
	fp=fopen("/home/g5s1e3/step2/index.html", "w+"); 
        if(fp==NULL)
	printf("Error opening the file");
      while ((  numbytes = recv (sockfd ,server_reply , 200  ,0 )) >0)
      
      {
     
     puts(server_reply);//display the content
     fprintf(fp, "%s", server_reply); //write in file the content
     strcat(htmlvar,server_reply);//new variable 
     }
      fclose(fp);

 
 close(sockfd);    //close the socket
 printf("the socket is closed\n\n");
 


	char com[]="13#";
	char server_message[2000];
	int SPORT=22513;
	struct sockaddr_in serverSA;
    int	sockfd_s=socket(AF_INET,SOCK_STREAM,0); // opens the socket for the server
int b=1; //return value for bind function	
    if(sockfd_s==-1){
		printf("socket creation failed...\n");
		exit(0);
	}
	else printf("Socket successfully created...\n");
	bzero(&serverSA,sizeof(serverSA));

	//assign IP,PORT
        memset(&serverSA,0,sizeof(serverSA));
	serverSA.sin_family=AF_INET; //socket family for IPv4
	serverSA.sin_addr.s_addr=htonl(INADDR_ANY); //server address set to any
	serverSA.sin_port=htons(SPORT); //set port number



	//bind socket to IP and verification
	if((bind(sockfd_s,(SA *)&serverSA,sizeof(serverSA)))!=0)
		{
	printf("socket bind failed...\n");
	exit(0);
	}
	else printf("Socket successfully binded..\n");

	//listen
	if((listen(sockfd_s,5))!=0){
		printf("Listen failed..\n");
		exit(0);
	}
	else
		printf("Server listening..\n");


	//accept
	do{
		connfd=accept(sockfd_s,NULL,NULL);//NULL-the requester's address is not copied into the buffer.
		if(connfd<0)
		{ perror("failed\n");
			printf("error: %d", errno);
			exit(1);
		}
		else
			printf("success\n");

	char buffer[6000],er_mes[]="Command not implemented.\n";
	int retv=1;
	retv=1;
	while(retv!=0)
	{retv= recv(connfd,buffer,sizeof(buffer),0);//get commands from client
		if(retv < 0)
		{ printf("failed\n");
			exit(1);
		}
		else
			printf(buffer);
		if(strcmp(buffer,com)==0)//if it contains our command
			send(connfd,htmlvar,sizeof(htmlvar),0);
		else
			send(connfd,er_mes,sizeof(er_mes),0);
	}
close(connfd);
printf("the client socket is closed.\n");
	 }while(1);
close(sockfd);
	printf("the server socket is closed.\n");
	return 0;
}


