#include "SmallBox.h"


double SmallBox::getSmallWidth(void)
{
    return width;
}

SmallBox::SmallBox():Box(1.0, 1.0, 1.0){   

}

void SmallBox::setSmallWidth(double wid)
{
    width = wid;
}