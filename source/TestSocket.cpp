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


}
//socket实现http
static void * pthread_socket_http_tcp(void * data){
	char buf[4096]={0};
	int sockfd, n; 
	char recvline[4096];
	const char * sendline2 = 
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

	const char * sendline = 
"POST /sportMusic/2.0/rest/music/get?evident HTTP/1.1\r\n\
Content-Type: application/json\r\n\
Authorization: OEPAUTH chCode=\"a39d713b25e95b2b\", smartDeviceId=\"11c8478c000068\"\r\n\
Accept: */*\r\n\
Cache-Control: no-cache\r\n\
Postman-Token: 8d987450-0656-415a-bd95-ade1a9ddfd1c\r\n\
Host: open.migu.cn:98\r\n\
Accept-Encoding: gzip, deflate, br\r\n\
Content-Length:25\r\n\r\n\
{\"musicId\":\"60054701920\"}";

	const char * sendline1 =
"POST /sportMusic/2.0/rest/music/get HTTP/1.1\r\n\
Host: open.migu.cn:98\r\n\
version:linux_v1.0\r\n\
sign:D35DBCFCB9C6AD65684A09CC546E81D372CF8EBC145A33131A236EE80EA00168A697112734B69A5CED2D5446449711C8\r\n\
Authorization:521344C36CD535EF102A44422721B210174C35FE7A79FCD83B0BDE9B971A69F2211324588D6D439D122DB811F68D8FBAD235A890F63D52794FA18287FDDEC10C7AD86D2F16781572055BB6CA725ED5D4AB1FE8A9FA4B6929F88DAF783271969E15A3D661CCFBB696780A820CA95052CF123319C74F44F923E28EA08CD55744A14E8F83C886147ACAC0911240BC9A58DC24498FAA27664F65C527D64741E7BED3C2EE49AB1D15CFD72A1195087E8ED98EC63934302EC77ACA\r\n\
Content-Type: application/json\r\n\
User-Agent: PostmanRuntime/7.26.8\r\n\
Accept: */*\r\n\
Cache-Control: no-cache\r\n\
Postman-Token: 8d987450-0656-415a-bd95-ade1a9ddfd1c\r\n\
Accept-Encoding: gzip, deflate, br\r\n\
Content-Length:80\r\n\r\n\
E274BA414858D6B6B4A842F49FEDA3C34E8637DCDF16E131A75117272858A87D2C1EBAE7B76F5EA3";

	const char * sendline11 =
"POST /sportMusic/2.0/rest/music/get HTTP/1.1\r\n\
Host: open.migu.cn:98\r\n\
version:linux_v1.0\r\n\
sign:D35DBCFCB9C6AD65684A09CC546E81D372CF8EBC145A33131A236EE80EA00168A697112734B69A5CED2D5446449711C8\r\n\
Content-Type: application/json\r\n\
User-Agent: PostmanRuntime/7.26.8\r\n\
Accept: */*\r\n\
Cache-Control: no-cache\r\n\
Postman-Token: 8d987450-0656-415a-bd95-ade1a9ddfd1c\r\n\
Accept-Encoding: gzip, deflate, br\r\n\
Content-Length:80\r\n\r\n\
E274BA414858D6B6B4A842F49FEDA3C34E8637DCDF16E131A75117272858A87D2C1EBAE7B76F5EA3";

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
	chunk.memory = (char*)"f2966c8487aa6af7f5b139f4759e235a9a7db2b640641f0ef845544ea22117592f929c2aa2a272d852ff4e2d32e25a392d65bf29443608622039f38d261cdf8f8f9d203f99475d4adfa5a3a4f49fed7b5ac88117b65f3a0a";
	chunk.size = strlen(chunk.memory);
	
	DEBUG("chunk.size=%d",(int16_t)chunk.size);	
	char * res1 = (char *)malloc(5*1024);
	Decode_postdata(res1,chunk);
	DEBUG("res1=%s",res1);


	close(sockfd); 

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
}

void TestSocket::startTestTCP(){
	cout << "TestSocket::startTest" << endl;
	pthread_t pt1,pt2,pt3;
	pthread_create(&pt1,NULL,pthread_socket_service_tcp,NULL);
	sleep(2);
	//pthread_create(&pt2,NULL,pthread_socket_client_tcp,NULL);
	pthread_create(&pt3,NULL,pthread_socket_http_tcp,NULL);
}


void TestSocket::startTestUDP(){
	cout << "TestSocket::startTestUDP" << endl;
	pthread_t pt1,pt2,pt3;
	pthread_create(&pt1,NULL,pthread_socket_service_udp,NULL);
	sleep(2);
	pthread_create(&pt2,NULL,pthread_socket_client_udp,NULL);
	//pthread_create(&pt3,NULL,pthread_socket_http,NULL);
}









