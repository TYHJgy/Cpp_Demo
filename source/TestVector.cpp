#include "TestVector.h"
#include "Box.h"
#include <vector>
#include <thread>
#include <iostream>

using namespace std;

static void test()
{
	cout << "enter test" << endl;
}

void TestVector::starTest()
{
	cout << "enter starTest" << endl;
	vector<Box> bs;
	Box b1(0,0,0);
	bs.push_back(b1);
	cout << bs.size() << endl;

	cout << bs[0].getVolume() << endl;
	vector<thread> ts;
	thread th1(test);

	cout << ts.size() << endl;
	//ts.push_back(th1);//此语句会报错-2020-12-22 09:41:50-gy	
	th1.join();//此时主线程被阻塞直至子线程执行结束。	
}



