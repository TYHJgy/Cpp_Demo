#pragma once
#include <iostream>
using namespace std;
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
        //必须添加关键字 virtual
        virtual int area()
        {
            cout << "Parent class area :" << endl;
            return 0;
        }
        //virtual int area2() = 0;//派生类必须实现此虚函数
    };

    class Rectangle : public Shape {
    public:
        Rectangle(int a = 0, int b = 0) :Shape(a, b) { }
        int area()
        {
            cout << "Rectangle class area :" << endl;
            return (width * height);
        }
    };
    class Triangle : public Shape {
    public:
        Triangle(int a = 0, int b = 0) :Shape(a, b) { }
        int area()
        {
            cout << "Triangle class area :" << endl;
            return (width * height / 2);
        }
    };

}

