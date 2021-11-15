#include "TestSocket.h"
#include "Debug_printf.h"
#include "mydes.h"
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
struct MemoryStruct {
	
	char *memory;
	size_t size;
	
};
static const char chCode[] = "e6316007dff77e76";

static int Decode_postdata(char *result,struct MemoryStruct chunk)
{
	int out_size = 0;
	unsigned char * out_dst = (unsigned char *)malloc(chunk.size / 2);
	;	
	if(out_dst == NULL){
		fprintf(stderr, "out_dst malloc failed\n");
		return 1;
	}
	memset(out_dst,0x00,chunk.size / 2);
	HexStrToByte( chunk.memory, out_dst, chunk.size );
	dw_des_decrypt((const char *)out_dst, chunk.size/2, chCode,(unsigned char *)result,&out_size);
	free(out_dst);
	return 0;
}


static void * pthread_socket_service_tcp(void * data){
	DEBUG("enter");

	struct sockaddr_in my_addr;
	int connfd = 0;
	char buf[64]={0};
	//
	int sfd = socket(AF_INET,SOCK_STREAM,0);
    if (sfd == -1){
		DEBUG("socket faile");
		return NULL;
	}
	memset(&my_addr, 0, sizeof(struct sockaddr_in));
	my_addr.sin_family  = AF_INET;		//使用IPv4地址
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
	my_addr.sin_port = htons(6666);  	//端口
	if(bind(sfd,(struct sockaddr *) &my_addr,sizeof(struct sockaddr_in))==-1){
		_errno = errno;
		DEBUG("bind faile,%s",strerror(_errno));
		return NULL;
	}
	//进入监听状态，等待用户发起请求
	if(listen(sfd,10)==-1){
		_errno = errno;
		DEBUG("listen faile,%s",strerror(_errno));
		return NULL;
	}
	//接收客户端请求
	connfd = accept(sfd, (struct sockaddr*)NULL, NULL);
	if(connfd==-1){
		_errno = errno;
		DEBUG("accept faile,%s",strerror(_errno));
		return NULL;
	}
	read(connfd,buf,64);
	send(connfd, buf, strlen(buf), 0);
	close(connfd); 
	close(sfd);
	DEBUG("rec=%s",buf);
	return NULL;
}
static void * pthread_socket_client_tcp(void * data){
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

	close(sockfd); 
	return  NULL;


}
//socket实现http
static void * pthread_socket_http_tcp(void * data){
	char buf[4096]={0};
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
Content-Length:25\r\n\r\n\
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
	if(read(sockfd,buf,4096) < 0) 
	{ 
		DEBUG("read msg error: %s(errno: %d)\n", strerror(errno), errno);
		exit(0); 
	}else{
		DEBUG("read success");
	}
	DEBUG("buf=%s",buf);
	
	DEBUG("回车=%d",'\r');
	DEBUG("换行=%d",'\n');

	int len = strlen(buf);
	for(int i = 0;i<len;i++){
		if(buf[i]=='\n'){
			i++;
			if(buf[i]=='\r'){
				i++;
				i++;
				char * memory = &buf[i];
				if(memory){
					
					DEBUG("buf2=%s",memory);			
					DEBUG("len=%d",(int)strlen(memory)); 
				}
	
				break;
			}
		}
	}

	struct MemoryStruct chunk;
	chunk.memory = (char*)"e274ba414858d6b6030c036ef0da15743a647cd27fa4f1b72f4f9acc108c35e2c40e4bb5fbe6f447930759830ff8dda03a3b259b992213e9af8a1fe169c4bc167a30b351288e08e6dedf9a65c65590ec0178444d01c02ca290727a3f2e97cadfffa17f1fdf12bf571eb0438e3db044eaac4fabaaac1649c6fdc1e7093732ff6fdedf9a65c65590eccdbdae5fc2960b3811cbfaf018203192c2cf53b439079d1a6f71676d04a76097f507cd3dbb494a944e9d5fd11ef6b247a7d09bca8a2b1f21c749339da97d6e39e2b819635f06f80f6cf080a3098ea8642c8be1e35d4873f945c380b31402c74aa2a0fd9f88b86df120f9e605666372c61f747c31eaf865cf1e9625124cae694873def7a142b09e6643530be186a4df5da41e6b90198a131008664fac7e247071640b4befcac501fe12e1fe5b461bda730b00f11009961315c7f1a08417f414b4f7ff41378eda91bae610e29a28777c21a247eba026f7fd6b770d9aa9c48b0b88c82940357cd128fd281ac9aeac9981808fcf37ed83a172aaf860e13eb33d0f40729dc27667c867815c47b928d9a42bb116fd5bb4fd525efed59c0e0f2fa1358cd1e36c0f39359eab2c894013a5c063f3925123db23fcd45264f0f5d5da3b5ddf5f05330b2119bcf1dee865899f35bce616b0f5dfbfc177d0d35deca7dbc8e7dc993246afbf0f5f14775b0b8a7b6a0037fd5d3c100aea5821c7fdd3781522487128db7cb068c81712177fc9f835089678d5a78e724d606dde5e14b260478f6f0076f37fad625a175b919131ab41b3f1bc6c6edd720bfb0694078d5f1362d49b41f0e2d7286588ee9d6517415cfe0f0eb6c3c1cc307aaeb56d4dc7168cf6b978261bf8485f4485a47db566a5d7838ae70ecbc9ea34c39f5c202812077724776b9e487488cfba393631df784ec73fe25e35c504ba06f18d92285281495652461d3416db5fc9c40dde702261563074ce2aa26d3e0ae13abd27703482c4bc23f41dea9712b17751c2f236c9c3d2ad804818ecfc8c16ab5b9f45d0a3d426201246217a92ddea2bb07a82933072e3bf6f116544f9bae4bfeecb892ba312efedc13c21ddc47e5300e97735192f9b49d2ce6e736550d080e3f62c0275f26624e906d9d1e92a0e25f0e31410e2519eda0530431ef6ea7e57bc3ef31880653eaa9c524ac0f5a9ae1edcbe0cf6b8aa6cd06a4843b8baaead92cb1f5e0ac1";
	chunk.size = strlen(chunk.memory);
	
	DEBUG("chunk.size=%d",(int16_t)chunk.size);	
	char * res1 = (char *)malloc(5*1024);
	Decode_postdata(res1,chunk);
	DEBUG("res1=%s",res1);


	close(sockfd); 
	return  NULL;

}

static void * pthread_socket_service_udp(void * data){
	//创建socket
	int sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if (0 > sockfd)
	{
		 perror("sockfd");
		 exit(0); 
	}

	//准备地址
	struct sockaddr_in addr = {};
	addr.sin_family = AF_INET;//ipv4
	addr.sin_port = htons(12345);//端口号
	addr.sin_addr.s_addr = htonl(INADDR_ANY);//自动获取ip
	//绑定
	int ret = bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
	if (0 > ret)
	{
		 perror("bind");
		 exit(0); 
	}
	struct sockaddr_in src_addr;
	socklen_t addr_len = sizeof(struct sockaddr_in);
	char buf[255] = {};
	//接收数据和来源的ip地址
	if(recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&src_addr,&addr_len) < 0) 
	{ 
		DEBUG("read msg error: %s(errno: %d)\n", strerror(errno), errno);
		exit(0); 
	}else{
		DEBUG("read success");
	}
	DEBUG("sRecv=%s",buf);
	
	//发送数据给目标地址
	if(sendto(sockfd,buf,strlen(buf)+1,0,(struct sockaddr*)&src_addr,addr_len) < 0) 
	{ 
		DEBUG("send msg error: %s(errno: %d)\n", strerror(errno), errno);
		exit(0); 
	}else{
		DEBUG("send success");
	}
	
	DEBUG("the port = %d", addr.sin_port);
	DEBUG("the port = %d", src_addr.sin_port);

	//关闭socket对象
	close(sockfd);
	return  NULL;
}
static void * pthread_socket_client_udp(void * data){
	int sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if (0 > sockfd)
	{
		 perror("socket");
		 exit(0); 
	}
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	socklen_t addr_len = sizeof(struct sockaddr_in);

	char buf[255] = "test";
	if(sendto(sockfd,buf,strlen(buf)+1,0,(struct sockaddr*)&addr,sizeof(addr)) < 0) 
	{ 
		DEBUG("send msg error: %s(errno: %d)\n", strerror(errno), errno);
		exit(0); 
	}else{
		DEBUG("send success");
	}
	if(recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&addr,&addr_len) < 0) 
	{ 
		DEBUG("read msg error: %s(errno: %d)\n", strerror(errno), errno);
		exit(0); 
	}else{
		DEBUG("read success");
	}
	DEBUG("cRecv=%s",buf);
	DEBUG("the ipaddr = %#x", addr.sin_addr.s_addr);
	DEBUG("the port = %d", addr.sin_port);
	close(sockfd);
	return  NULL;
}

void TestSocket::startTestTCP(){
	cout << "TestSocket::startTest" << endl;
	pthread_t pt1,pt2,pt3;
	pthread_create(&pt1,NULL,pthread_socket_service_tcp,NULL);
	sleep(2);
	pthread_create(&pt2,NULL,pthread_socket_client_tcp,NULL);
//	pthread_create(&pt3,NULL,pthread_socket_http_tcp,NULL);
}


void TestSocket::startTestUDP(){
	cout << "TestSocket::startTestUDP" << endl;
	pthread_t pt1,pt2,pt3;
	pthread_create(&pt1,NULL,pthread_socket_service_udp,NULL);
	sleep(2);
	pthread_create(&pt2,NULL,pthread_socket_client_udp,NULL);
	//pthread_create(&pt3,NULL,pthread_socket_http,NULL);
}









