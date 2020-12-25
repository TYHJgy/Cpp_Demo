#include "TestReferences.h"
#include <iostream>
using namespace std;

double vals[] = { 10.1, 12.6, 33.1, 24.1, 50.0 };

//把引用作为返回值
double& setValues(int i)
{
	return vals[i];   // 返回第 i 个元素的引用
}
//把引用作为返回值测试
void ReferencesAsReturn() {
	cout << "改变前的值" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << "vals[" << i << "] = ";
		cout << vals[i] << endl;
	}

	setValues(1) = 20.23; // 改变第 2 个元素
	setValues(3) = 70.8;  // 改变第 4 个元素

	cout << "改变后的值" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << "vals[" << i << "] = ";
		cout << vals[i] << endl;
	}
}

//把引用作为参数
void swap(int& x, int& y)
{
	int temp;
	temp = x; /* 保存地址 x 的值 */
	x = y;    /* 把 y 赋值给 x */
	y = temp; /* 把 x 赋值给 y  */

	return;
}
//把引用作为参数测试
void ReferencesAsParameter() {
	// 局部变量声明
	int a = 100;
	int b = 200;

	cout << "交换前，a 的值：" << a << endl;
	cout << "交换前，b 的值：" << b << endl;

	/* 调用函数来交换值 */
	swap(a, b);

	cout << "交换后，a 的值：" << a << endl;
	cout << "交换后，b 的值：" << b << endl;

}

void TestReferences::startTest()
{
	ReferencesAsParameter();	//把引用作为参数测试
	ReferencesAsReturn();		//把引用作为返回值测试
}
