#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<errno.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<netdb.h>

#define PORT 5000
int main()
{
	int my_socket, bytes_sent, bytes_recv,true=1;
	char recv_data[64], send_data[64]={"mv \0"};
	struct sockaddr_in my_addr, their_addr;
	struct hostent *host;
	
	host=gethostbyname("127.0.0.1");

	if((my_socket=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("Socket");
		exit(1);
	}
	
	their_addr.sin_family=AF_INET;
	their_addr.sin_port=htons(PORT);
	their_addr.sin_addr=*((struct in_addr *)host->h_addr);
	memset(&(their_addr.sin_zero),'\0',8);
	
	if(connect(my_socket,(struct sockaddr *)&their_addr,sizeof(struct sockaddr))==-1)
	{
		perror("Connect");
		exit(1);
	}
	
	char name[30];
	printf("\nEnter the File Name:");
	scanf("%s",name);
	strcat(name," ");
	strcat(send_data,name);
	char tar[30];
	printf("\nEnter the target file name:");
	scanf("%s",tar);
	strcat(send_data,tar);
	int len=strlen(send_data);
	
	if((bytes_sent=send(my_socket,send_data,len,0))==-1)
	{
		perror("Send");
		exit(1);
	}
	
	/*char send_data2[]={" mv 3 temp.doc \0"};
	len=strlen(send_data2);
	
	if((bytes_sent=send(my_socket,send_data,len,0))==-1)
	{
		perror("Send");
		exit(1);
	}
	
	//send_data=NULL;
	//len=strlen(send_data);
	
	/*if((bytes_sent=send(my_socket,,len,0))==-1)
	{
		perror("Send");
		exit(1);
	}
	*/
	
	printf("\n");
	close(my_socket);
	
	return(0);
}
