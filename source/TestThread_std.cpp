
#include "TestThread_std.h"

#include <iostream>
#include <thread>


using namespace std;

static void test(){
	cout << "test" << endl;
}


static void std_thread_run(void) {
	cout << "std_thread_run" << endl;
	for (int i = 0; i < 10;i++) {
		cout << "std_thread_run:"<< i << endl;
	}
}

unsigned int TestThread_std::getThreadNum(){
 	return threadNum;
}


void TestThread_std::startTest(void){
	cout << "startTest" << endl;
	test();
	thread th(std_thread_run);//第一个参数为函数名，第二个参数为该函数的第一个参数，如果该函数接收多个参数就依次写在后面。此时线程开始执行。
}








