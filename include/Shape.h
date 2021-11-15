#pragma once
#include <iostream>
using namespace std;

#define TESTABC
namespace myShape {
    class Shape
    {
    protected:
        int width, height;
    public:
        Shape(int a = 0, int b = 0)
        {
            width = a;
            height = b;
        }
        //必须添加关键字 virtual才能实现多态
        virtual int area()
        {
            cout << "Parent class area :" << endl;
            return 0;
        }
#ifdef TESTABC0
        //C++ 接口是使用抽象类来实现的，如果类中有一个函数被声明为纯虚函数，则这个类就是抽象类。
        //抽象类不能被用于实例化对象，它只能作为接口使用。
        //派生类需要被实例化，则必须实现每个虚函数
        virtual int area2() = 0;
#endif
    };

    //矩形
    class Rectangle : public Shape {
    public:
        Rectangle(int a = 0, int b = 0) :Shape(a, b) { }
#ifdef TESTABC0

        int area()
        {
            cout << "Rectangle class area :" << endl;
            return (width * height);
        }
        int area2() {
            cout << "Rectangle area2" << endl;
        }
#endif
    };
    //三角形
    class Triangle : public Shape {
    public:
        Triangle(int a = 0, int b = 0) :Shape(a, b) { }
        int area()
        {
            cout << "Triangle class area :" << endl;
            return (width * height / 2);
        }        
        int area2() {
            cout << "Triangle area2" << endl;
			return 0;
        }
    };

}

