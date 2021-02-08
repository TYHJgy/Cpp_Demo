#include "TestThread.h"
#include "Debug_printf.h"
#include <iostream>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <semaphore.h>

using namespace std;


pthread_mutex_t mutex;
pthread_rwlock_t rwlock;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
sem_t sem;


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
	DEBUG("enter-%s",(char*)data);
	
	pthread_mutex_lock(&mutex);
	for(int i=0;i<10;i++){
		DEBUG("%s",(char*)data);
		sleep(1);
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

static void * test_pthread_exit_run(void * data){
	DEBUG("enter");
	for(int i=0;i<10;i++){
		DEBUG("%d",i);
		pthread_exit(NULL);
	}
	return NULL;
}

/*测试 pthread_exit (结束调用线程)*/
/*线程通过调用pthread_exit函数终止执行，就如同进程在结束时调用exit函数一样。
这个函数的作用是，终止调用它的线程并返回一个指向某个对象的指针。*/
void TestThread::test_pthread_exit(){

	pthread_t pid1;

	pthread_create(&pid1,NULL,test_pthread_exit_run,NULL);
	sleep(5);
}

static void * test_pthread_join_run1(void * data){
	DEBUG("enter");
	for(int i=0;i<10;i++){
		DEBUG("i=%d",i);
		sleep(1);
	}

}
static void * test_pthread_join_run2(void * data){
	DEBUG("enter");
	pthread_t pid = *(pthread_t*)data;
	sleep(1);
	pthread_join(pid,NULL);
	DEBUG("enter2");
}

/*测试   int pthread_join(pthread_t thread, void **retval); */
/*函数 pthread_join   用来等待一个线程的结束,线程间同步的操作。*/
void TestThread::test_pthread_join(){
	static pthread_t pid1;
	static pthread_t pid2;
	pthread_create(&pid1,NULL,test_pthread_join_run1,NULL);
	pthread_create(&pid2,NULL,test_pthread_join_run2,&pid1);
}

static void * test_pthread_cancel_run1(void * data){
	DEBUG("enter");
	for(int i=0;i<10;i++){
		DEBUG("i=%d",i);
		sleep(1);
	}
}
static void * test_pthread_cancel_run2(void * data){
	DEBUG("enter");
	sleep(5);
	pthread_t pid = *(pthread_t*)data;
	pthread_cancel(pid);
	DEBUG("enter2");
}

/*测试   int pthread_cancel(pthread_t thread); */
/*结束指定线程*/
void TestThread::test_pthread_cancel(){
	static pthread_t pid1;
	static pthread_t pid2;
	pthread_create(&pid1,NULL,test_pthread_cancel_run1,NULL);
	pthread_create(&pid2,NULL,test_pthread_cancel_run2,&pid1);
}

static void * test_pthread_rwlock_run1(void * data){
	DEBUG("enter");
	pthread_rwlock_rdlock(&rwlock);
		for(int i=0;i<5;i++){
		DEBUG("i=%d",i);
		sleep(1);
	}	
	pthread_rwlock_unlock(&rwlock);
}


static void * test_pthread_rwlock_run2(void * data){
	DEBUG("enter");

	pthread_rwlock_rdlock(&rwlock);
	for(int i=0;i<5;i++){
		DEBUG("i=%d",i);
		sleep(1);
	}	
	pthread_rwlock_unlock(&rwlock);

}

static void * test_pthread_rwlock_run3(void * data){
	DEBUG("enter");
	pthread_rwlock_wrlock(&rwlock);
	for(int i=0;i<5;i++){
		DEBUG("i=%d",i);
		sleep(1);
	}
	pthread_rwlock_unlock(&rwlock);

}

void TestThread::test_pthread_rwlock(){

	static pthread_t pid1;
	static pthread_t pid2;
	static pthread_t pid3;

	pthread_rwlock_init(&rwlock,NULL);
	
	pthread_create(&pid3,NULL,test_pthread_rwlock_run3,NULL);
	pthread_create(&pid1,NULL,test_pthread_rwlock_run1,NULL);
	pthread_create(&pid2,NULL,test_pthread_rwlock_run2,NULL);
}

static void * test_pthread_cond_run1(void *data){
	DEBUG("enter");
	for(int i=0;i<5;i++){
		DEBUG("i=%d",i);
		sleep(1);
	}	
	pthread_mutex_lock(&mutex);
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mutex);
	DEBUG("enter2");

}
static void * test_pthread_cond_run2(void *data){
	DEBUG("enter");
	struct timespec outtime;
	struct timeval now;
	
	gettimeofday(&now, NULL);
	outtime.tv_sec = now.tv_sec+3;		

	pthread_mutex_lock(&mutex);
		
	//pthread_cond_wait(&cond, &mutex);
	pthread_cond_timedwait(&cond, &mutex, &outtime);
	
	DEBUG("enter2");
	pthread_mutex_unlock(&mutex);

}

void TestThread::test_pthread_cond(){	
	
	static pthread_t pid1;
	static pthread_t pid2;

	pthread_mutex_init(&mutex,NULL);
	
	pthread_create(&pid1,NULL,test_pthread_cond_run1,NULL);
	pthread_create(&pid2,NULL,test_pthread_cond_run2,NULL);
}
static void * test_pthread_sem_run(void * res){
	char *msg = (char*)res;

	DEBUG("1111");
	while (1) {
		sem_wait(&sem);
		strcat(msg, "a");
		DEBUG("resource changed with value: %s\n", msg);
	}

}
void TestThread::test_pthread_sem(){

	pthread_t thread;
	char resource[10] = {0};

    int ret = sem_init(&sem, 0, 0);
    if (ret == -1) {
        DEBUG("sem_init failed \n");
        return;
    }

    ret = pthread_create(&thread, NULL, test_pthread_sem_run, (void*)resource);
    if (ret != 0) {
        DEBUG("pthread_create failed \n");
        return;
    }

    while (1) {
        sem_post(&sem);
        sleep(1);
    }
}




