#pragma once
class Line
{
public:
    double length;
    void setLength(double len);
    double getLength(void);
    Line();  // 这是构造函数 
    ~Line();  // 这是析构函数声明
    Line(double len);  // 这是构造函数
};

