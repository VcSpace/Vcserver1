//udp server
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>

#define N 5000

int main(int argc, const char *argv[])
{
	int sockfd;
	char buf[N] = {};
	struct sockaddr_in serveraddr,clientaddr;
	
	
	if((sockfd = socket(AF_INET,SOCK_DGRAM,0))<0)
	{//第二个参数TCP是SOCK_STREAM,UDP是SOCK_DGRAM
		perror("fail to socket");
		return -1;
	}
	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(20222);  //注意atoi
	
	if(bind(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr))<0)
	{
		perror("fail to bind");
		return -1;
	}

	socklen_t addrlen = sizeof(struct sockaddr);

//	while(1)
	{
		//接收4500字节
		recvfrom(sockfd, buf, 4500, 0, (struct sockaddr *)&clientaddr, &addrlen);
		printf("From client: %s \n",buf);
		if(0 == strncmp(buf,"quit",4))
		{
			;
		}

		strcat(buf,"from server...");
		//发送4500字节
		sendto(sockfd, buf, 4500, 0, (struct sockaddr *)&clientaddr, sizeof(clientaddr));
	}
	
	close(sockfd);
	return 0;
}


