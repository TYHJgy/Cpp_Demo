#pragma once
#include <iostream>
using namespace std;
class PrintData
{
public:
    void print(int i) {
        cout << "整数为: " << i << endl;
    }

    void print(double  f) {
        cout << "浮点数为: " << f << endl;
    }

    void print(char c[]) {
        cout << "字符串为: " << c << endl;
    }
};

