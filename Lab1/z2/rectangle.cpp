#include "rectangle.h"

Rectangle::Rectangle() : Figure()
{
    x1 = 100;
    y1 = 100;
    w = 100;
    h = 200;
}

void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(Qt::blue);
    painter->drawRect(x1,y1,w,h);
    centerOfGrav();
}

double Rectangle::square()
{
    return w * h;
}

double Rectangle::perimetr()
{
    return (w + h) * 2;
}

void Rectangle::centerOfGrav()
{
    xGrav = x1 + w / 2;
    yGrav = y1 + h / 2;
    this->setTransformOriginPoint(xGrav, yGrav);
}

void Rectangle::setCoord(int x1, int y1, int w, int h)
{
    this->x1 = x1;
    this->y1 = y1;
    this->w = w;
    this->h = h;
}

const char* Rectangle::checkType()
{
    return "Rectangle";
}
