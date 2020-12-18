#pragma once
class Box
{
private:
    double length;         // 长度
    double breadth;        // 宽度
    double height;         // 高度

protected:
    double width;

public:
    // 成员函数声明
    double getVolume(void);
    void setLength(double len);
    void setBreadth(double bre);
    void setHeight(double hei);
    void setWidth(double wid);
    friend void printWidth(Box box);
};

