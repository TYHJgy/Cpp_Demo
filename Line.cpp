#include "Line.h"
#include <iostream>

using namespace std;
// ��Ա��������
double Line::getLength(void)
{
    return length;
}

void Line::setLength(double len)
{
    length = len;
    
}

// ��Ա�������壬�������캯��
Line::Line(void)
{
    cout << "Object is being created" << endl;
}
Line::~Line(void)
{
    cout << "Object is being deleted" << endl;
}
// ��Ա�������壬�������캯��
Line::Line(double len)
{
    cout << "Object is being created, length = " << len << endl;
    length = len;
}