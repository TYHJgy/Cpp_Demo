#pragma warning(disable : 4996) //关闭此文件的4996警告
#include "TestTimeAndData.h"
#include <iostream>
#include <time.h>
#include <sys/time.h>

using namespace std;

void TestTimeAndData::startTest()
{
	cout << "TestTimeAndData::startTest" <<endl;

	time_t t;  //秒时间  
	timeval tv;//秒和微妙
	
	tm* local; //本地时间   
	tm* gmt;   //格林威治时间  
	
	char buf[128] = { 0 };

	//获取目前秒时间 
	t = time(NULL); //或者time(&t); 
	cout << "1970-1-1,00:00:00至此：" << t <<"s" << endl;

	//获取秒和微秒
	gettimeofday(&tv, NULL); 
	cout << "1970-1-1,00:00:00至此：" << tv.tv_sec <<"s." << tv.tv_usec <<"us" << endl;

	local = localtime(&t); //转为本地时间  
	strftime(buf, 64, "%y-%m-%d %H:%M:%S", local);
	std::cout << "本地时间：" << buf << std::endl;

	gmt = gmtime(&t);//转为格林威治时间  
	strftime(buf, 64, "%Y-%m-%d %H:%M:%S", gmt);
	std::cout << "格林威治时间：" << buf << std::endl;



}
