#include "circle.h"

Circle::Circle(){}

Circle::~Circle(){}

QRectF Circle::boundingRect() const
{
    return QRectF(0,0,1200,600);
}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->translate(300,300);
    painter->drawEllipse(-100, -100, 200, 200);
}

void Circle::moving()
{
    this->moveBy(1, 0);
    if(x() == 750)
    {
        this->moveBy(-750, 0);
    }
}
