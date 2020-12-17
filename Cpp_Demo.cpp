#include <iostream>
#include "Box.h"
#include "Line.h"
#include "SmallBox.h"
#include "PrintData.h"
#include "Shape.h"

using namespace std;

void testline() {
	cout << "enter testline" << endl;
	Line line;

	// 设置长度
	line.setLength(6.0);
	cout << "Length of line : " << line.getLength() << endl;

	// 不使用成员函数设置长度
	line.length = 10.0; // OK: 因为 length 是公有的
	cout << "Length of line : " << line.length << endl;
}
void testBox() {
	cout << "enter testBox" << endl;
	Box Box1;                // 声明 Box1，类型为 Box
	Box Box2;                // 声明 Box2，类型为 Box
	double volume = 0.0;     // 用于存储体积

	// box 1 详述
	Box1.setLength(6.0);
	Box1.setBreadth(7.0);
	Box1.setHeight(5.0);

	// box 2 详述
	Box2.setLength(12.0);
	Box2.setBreadth(13.0);
	Box2.setHeight(10.0);

	// box 1 的体积
	volume = Box1.getVolume();
	cout << "Box1 的体积：" << volume << endl;

	// box 2 的体积
	volume = Box2.getVolume();
	cout << "Box2 的体积：" << volume << endl;
}
void testSmallBox() {
	cout << "enter testSmallBox" << endl;
	SmallBox box;
	// 使用成员函数设置宽度
	box.setSmallWidth(5.0);
	cout << "Width of box : " << box.getSmallWidth() << endl;
}
void testFriendMethod() {
	cout << "enter testFriendMethod" << endl;
	Box box;
	// 使用成员函数设置宽度
	box.setWidth(10.0);
	// 使用友元函数输出宽度
	printWidth(box);
}
void testPrintData()
{
	cout << "enter testPrintData" << endl;

	PrintData pd;

	// 输出整数
	pd.print(5);
	// 输出浮点数
	pd.print(500.263);
	// 输出字符串
	char c[] = "Hello C++";
	pd.print(c);
}
void testDerivedClass() {
	cout << "enter testDerivedClass" << endl;

	Shape* shape;
	Shape shape2(10,7);
	Rectangle rec(10, 7);
	Triangle  tri(10, 5);

	shape2.area();
	// 存储矩形的地址
	shape = &rec;
	// 调用矩形的求面积函数 area
	shape->area();

	// 存储三角形的地址
	shape = &tri;
	// 调用三角形的求面积函数 area
	shape->area();

}
void testString() {
	cout << "enter testString" << endl;

	string str1 = "abc";
	string str2 = "abc";
	cout << &str1 << "||" << &str2 << endl;
	cout << (str1 == str2) << endl;
	cout << (0 == 1) << endl;
	cout << true << endl;
	cout << (str1._Equal(str2)) << endl;
}
int main()
{
	testBox();
	testline();
	testSmallBox();
	testFriendMethod();
	testPrintData();
	testDerivedClass();
	testString();
	return 0;
}