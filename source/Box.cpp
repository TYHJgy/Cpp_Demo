#include "Box.h"
#include <iostream>
using namespace std;


Box::Box(double length, double breadth, double height)
{
    this->length = length;
    this->breadth = breadth;
    this->height = height;
}

Box::Box(double length) :length(length){}


double Box::getVolume(void)
{
    return length * breadth * height;
}
void Box::setLength(double len)
{
    length = len;
}
void Box::setBreadth(double bre)
{
    breadth = bre;
}
void Box::setHeight(double hei)
{
    height = hei;
}
void Box::setWidth(double wid)
{
    width = wid;
}
double Box::getLength()
{
    return length;
}
double Box::getBreadth()
{
    return breadth;
}
double Box::getHeight()
{
    return height;
}
void printWidth(Box box)
{
    cout << "Width of box : " << box.width << endl;
}

// 重载 + 运算符，用于把两个 Box 对象相加
Box Box::operator+(const Box& b)
{
    Box box(0,0,0);
    box.setLength(this->length + b.length);
    box.setBreadth(this->breadth + b.breadth);
    box.setHeight(this->height + b.height);
    return box;
}
