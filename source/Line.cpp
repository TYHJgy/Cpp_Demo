#include "Line.h"
#include <iostream>

using namespace std;

//���캯��
Line::Line(void)
{
    cout << "Object is being created" << endl;
}
Line::Line(double len)
{
    cout << "Object is being created, length = " << len << endl;
    length = len;
}
//��������
Line::~Line(void)
{
    cout << "Object is being deleted" << endl;
}
//��Ա����
double Line::getLength(void)
{
    return length;
}
void Line::setLength(double len)
{
    length = len;
    
}
