#include "stareight.h"

StarEight::StarEight() : StarSix()
{
    n = 8;
}

void StarEight::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    paintStar(painter);
}
const char* StarEight::checkType()
{
    return "StarEight";
}
