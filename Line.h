#pragma once
class Line
{
public:
    double length;
    void setLength(double len);
    double getLength(void);
    Line();  // ���ǹ��캯�� 
    ~Line();  // ����������������
    Line(double len);  // ���ǹ��캯��
};

