#include "TestSocket.h"
#include "Debug_printf.h"
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <sys/un.h>
#include <string.h>
#include <errno.h>

using namespace std;
static int _errno = 0;
#define MAXLINE 4096 

static void * pthread_socket_service(void * data){
	DEBUG("enter");

	struct sockaddr_in my_addr;
	int connfd = 0;
	char buf[64]={0};
	
	int sfd = socket(AF_INET,SOCK_STREAM,0);
    if (sfd == -1){
		DEBUG("socket faile");
		return  NULL;
	}
	memset(&my_addr, 0, sizeof(struct sockaddr_in));
	my_addr.sin_family  = AF_INET;//使用IPv4地址
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
	my_addr.sin_port = htons(6666);  //端口
	if(bind(sfd,(struct sockaddr *) &my_addr,sizeof(struct sockaddr_in))==-1){
		_errno = errno;
		DEBUG("bind faile,%s",strerror(_errno));
		return  NULL;
	}
	//进入监听状态，等待用户发起请求
	if(listen(sfd,10)==-1){
		_errno = errno;
		DEBUG("listen faile,%s",strerror(_errno));
		return  NULL;
	}
	//接收客户端请求
	connfd = accept(sfd, (struct sockaddr*)NULL, NULL);
	if(connfd==-1){
		_errno = errno;
		DEBUG("accept faile,%s",strerror(_errno));
		return  NULL;
	}
	read(connfd,buf,64);
	send(connfd, buf, strlen(buf), 0);
	close(connfd); 
	close(sfd);
	DEBUG("rec=%s",buf);
}
static void * pthread_socket_client(void * data){
		char buf[1024]={0};
		int sockfd, n; 
		char recvline[4096];
		const char * sendline = "POST";
	
		struct sockaddr_in servaddr; 
		if((sockfd = socket(AF_INET, SOCK_STREAM, 0))<0)	{
			printf("create socket error: %s(errno: %d)\n", strerror(errno),errno); 
			exit(0); 
		} 
		memset(&servaddr, 0, sizeof(servaddr));
		servaddr.sin_family = AF_INET; 
		servaddr.sin_port = htons(6666); 
		if(inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0)
		{ 
			printf("inet_pton error for %s\n",(char*)data); 
			exit(0); 
		} 
		if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(struct sockaddr)) < 0)
		{ 
			printf("connect error: %s(errno: %d)\n",strerror(errno),errno); 
			exit(0); 
		} 
		DEBUG("sendline=%s",sendline);
		if(send(sockfd, sendline, strlen(sendline), 0) < 0) 
		{ 
			DEBUG("send msg error: %s(errno: %d)\n", strerror(errno), errno);
			exit(0); 
		}else{
			DEBUG("send success");
		}
		if(read(sockfd,buf,1024) < 0) 
		{ 
			DEBUG("read msg error: %s(errno: %d)\n", strerror(errno), errno);
			exit(0); 
		}else{
			DEBUG("read success");
		}
		DEBUG("buf=%s",buf);
		for(int i=0;i<1024;i++){
			//DEBUG("buf=%c",buf[i]);
		}
		close(sockfd); 


}
//socket实现http
static void * pthread_socket_http(void * data){
	char buf[1024]={0};
	int sockfd, n; 
	char recvline[4096];
	const char * sendline = 
"POST /sportMusic/2.0/rest/music/get?evident HTTP/1.1\r\n\
Content-Type: application/json\r\n\
Authorization: OEPAUTH chCode=\"a39d713b25e95b2b\", smartDeviceId=\"11c8478c000068\"\r\n\
User-Agent: PostmanRuntime/7.26.8\r\nAccept: */*\r\n\
Cache-Control: no-cache\r\n\
Postman-Token: 8d987450-0656-415a-bd95-ade1a9ddfd1c\r\n\
Host: 218.200.227.123:9921\r\n\
Accept-Encoding: gzip, deflate, br\r\n\
Connection: keep-alive\r\nContent-Length: 25\r\n\r\n\
{\"musicId\":\"60054701920\"}";

	struct sockaddr_in servaddr; 
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0))<0)	{
		printf("create socket error: %s(errno: %d)\n", strerror(errno),errno); 
		exit(0); 
	} 
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(9921); 
	if(inet_pton(AF_INET, "218.200.227.123", &servaddr.sin_addr) <= 0)
	{ 
		printf("inet_pton error for %s\n",(char*)data); 
		exit(0); 
	} 
	if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(struct sockaddr)) < 0)
	{ 
		printf("connect error: %s(errno: %d)\n",strerror(errno),errno); 
		exit(0); 
	} 
	DEBUG("sendline=%s",sendline);
	if(send(sockfd, sendline, strlen(sendline), 0) < 0) 
	{ 
		DEBUG("send msg error: %s(errno: %d)\n", strerror(errno), errno);
		exit(0); 
	}else{
		DEBUG("send success");
	}
	if(read(sockfd,buf,1024) < 0) 
	{ 
		DEBUG("read msg error: %s(errno: %d)\n", strerror(errno), errno);
		exit(0); 
	}else{
		DEBUG("read success");
	}
	DEBUG("buf=%s",buf);
	for(int i=0;i<1024;i++){
		//DEBUG("buf=%c",buf[i]);
	}
	close(sockfd); 

}


void TestSocket::startTest(){
	cout << "TestSocket::startTest" << endl;
	pthread_t pt1,pt2,pt3;
	pthread_create(&pt1,NULL,pthread_socket_service,NULL);
	sleep(2);
	pthread_create(&pt2,NULL,pthread_socket_client,NULL);
	//pthread_create(&pt3,NULL,pthread_socket_http,NULL);
}










