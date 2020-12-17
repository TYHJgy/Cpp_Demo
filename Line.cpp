#include "Line.h"
#include <iostream>

using namespace std;
// 成员函数定义
double Line::getLength(void)
{
    return length;
}

void Line::setLength(double len)
{
    length = len;
    
}

// 成员函数定义，包括构造函数
Line::Line(void)
{
    cout << "Object is being created" << endl;
}
Line::~Line(void)
{
    cout << "Object is being deleted" << endl;
}
// 成员函数定义，包括构造函数
Line::Line(double len)
{
    cout << "Object is being created, length = " << len << endl;
    length = len;
}