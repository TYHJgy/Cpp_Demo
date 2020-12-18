#pragma once
class Line
{
public:
    double length;
    void setLength(double len);
    double getLength(void);
    Line();             //构造函数声明
    ~Line();            //析构函数声明
    Line(double len);   //构造函数声明
};

