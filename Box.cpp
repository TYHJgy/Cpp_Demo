#include "Box.h"
#include <iostream>
using namespace std;


// ��Ա��������
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
//��ע�⣺printWidth() �����κ���ĳ�Ա����
void printWidth(Box box)
{
    /* ��Ϊ printWidth() �� Box ����Ԫ��������ֱ�ӷ��ʸ�����κγ�Ա */
    cout << "Width of box : " << box.width << endl;
}


