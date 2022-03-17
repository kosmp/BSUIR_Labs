#include "circle.h"

Circle::Circle() : Ellipse()
{
    w =  h = r = 200;
}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(x, y, r, r);
    centerOfGrav(r, r);
}

void Circle::setCoord(int x, int y, int r)
{
    this->x = x;
    this->y = y;
    this->r = r;
    centerOfGrav(r, r);
}

const char* Circle::checkType()
{
    return "Circle";
}
