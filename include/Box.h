#pragma once
class Box
{
private:
    double length;         // ����
    double breadth;        // ���
    double height;         // �߶�

protected:
    double width;

public:
    // ��Ա��������
    double getVolume(void);
    void setLength(double len);
    void setBreadth(double bre);
    void setHeight(double hei);
    void setWidth(double wid);
    friend void printWidth(Box box);
};

