#pragma once
class Line
{
public:
    double length;
    void setLength(double len);
    double getLength(void);
    Line();             //���캯������
    ~Line();            //������������
    Line(double len);   //���캯������
};

