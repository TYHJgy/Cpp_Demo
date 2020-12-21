
#include "TestThread.h"
#include <iostream>
#include <thread>

using namespace std;

static void test(){
	cout << "test" << endl;
}

static void * linux_thread_run(void * data)
{
	cout << "linux_thread_run:" << data << endl;
	char* databuf = (char*)data;
	for(int i = 0;i<10;i++){
		cout << i << endl;
	}
	const char * c = "123456";
	cout << c[0]<<endl;
	return NULL;
}

unsigned int TestThread::getThreadNum(){
 	return threadNum;
}

vector<pthread_t> TestThread::getPtid(){
	return ptid;
}


void TestThread::startTest(void){
	cout << "startTest" << endl;
	test();

	pthread_t pid;
	int error = pthread_create(&pid,0,linux_thread_run,NULL);
	if(error != 0){
		cerr << "Create pthread error!\n" << endl;
	}else{
		threadNum = 1;
		ptid.push_back(pid);
	}	
}




