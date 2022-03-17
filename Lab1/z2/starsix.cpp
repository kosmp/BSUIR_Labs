#include "starsix.h"

StarSix::StarSix() : StarFive()
{
    n = 6;
}

void StarSix::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    paintStar(painter);
}

const char* StarSix::checkType()
{
    return "StarSix";
}
