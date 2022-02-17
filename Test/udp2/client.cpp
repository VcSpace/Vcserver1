//udp client
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
  char buf[N] = {0};
  struct sockaddr_in serveraddr;
  FILE *fp = NULL;
  unsigned int len = 0;
  
  if(argc < 3)
  {
    fprintf(stderr,"Usage: %s ip port.\n",argv[0]);
    return -1;
  }
  
  if((sockfd = socket(AF_INET, SOCK_DGRAM, 0))<0)
  {
    perror("fail to socket");
    return -1;
  }
  
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
  serveraddr.sin_port = htons(atoi(argv[2])); //注意atoi
  socklen_t addrlen = sizeof(struct sockaddr);
  
  //提前准备个文本有4500字节的数据
  fp = fopen("./myfile.txt", "r");
  if (!fp)
  {
  	perror("fail to fopen");
    return -1;
  }
  
  len = fread(buf, sizeof(char), 4500, fp); //设读4500字节
	if(!len) {
		fclose(fp);
		perror("fail to fread");
		return -1;
	}
	
	//发4500字节
  sendto(sockfd, buf, 4500, 0, (struct sockaddr *)&serveraddr, addrlen);

  //服务器的sendto写地址了 这里可以省略 收4500字节 
  recvfrom(sockfd, buf, N, 4500, NULL, NULL); 
  printf("From server: %s \n",buf);

  close(sockfd);
  return 0;
}


