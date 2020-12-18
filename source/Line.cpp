#include "Line.h"
#include <iostream>

using namespace std;

//构造函数
Line::Line(void)
{
    cout << "Object is being created" << endl;
}
Line::Line(double len)
{
    cout << "Object is being created, length = " << len << endl;
    length = len;
}
//析构函数
Line::~Line(void)
{
    cout << "Object is being deleted" << endl;
}
//成员函数
double Line::getLength(void)
{
    return length;
}
void Line::setLength(double len)
{
    length = len;
    
}
