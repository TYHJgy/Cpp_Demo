#include "TestThread.h"
#include "Debug_printf.h"
#include <iostream>
#include <pthread.h>
#include <string.h>
using namespace std;


pthread_mutex_t mutex;

static void * linux_thread_run(void * data)
{
	cout << "linux_thread_run:" << data << endl;
	char* databuf = (char*)data;
	for(int i = 0;i<10;i++){
		cout << i << endl;
	}
	const char * c = "123456";
	cout << c[0]<<endl;
	//return NULL;
}

unsigned int TestThread::getThreadNum(){
 	return threadNum;
}

vector<pthread_t> TestThread::getPtid(){
	return ptid;
}


void TestThread::startTest(void){

	cout << "startTest" << endl;
	pthread_t pid;
	int error = pthread_create(&pid,NULL,&linux_thread_run,NULL);
	if(error != 0){
		cerr << "Create pthread error!\n" << endl;
	}else{
		threadNum = 1;
		ptid.push_back(pid);
	}

}
static void * test_thread_lock_run(void * data)
{
	DEBUG("enter");
	
	pthread_mutex_lock(&mutex);
	for(int i=0;i<1000;i++){
		DEBUG("%s",(char*)data);
	}	
	pthread_mutex_unlock(&mutex);	
}

/*测试线程同步*/
//互斥锁
void TestThread::test_thread_lock(){
	
	pthread_t pid1;
	pthread_t pid2;
	
	pthread_mutex_init(&mutex, NULL);
	
	pthread_create(&pid1,NULL,&test_thread_lock_run,(void *)"123");
	pthread_create(&pid2,NULL,&test_thread_lock_run,(void *)"456");
}



