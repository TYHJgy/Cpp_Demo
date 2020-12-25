#pragma once
#include "Box.h"

class SmallBox:public Box
{
public:
    SmallBox();
    void setSmallWidth(double wid);
    double getSmallWidth(void);
};

