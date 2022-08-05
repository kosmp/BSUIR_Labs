#include "rhombus.h"

Rhombus::Rhombus() : Figure()
{
    x1 = 100;
    y1 = 200;
    x2 = 200;
    y2 = 50;
    x3 = 300;
    y3 = 200;
    x4 = 200;
    y4 = 350;
}

void Rhombus::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPolygon rhombus;
    rhombus << QPoint(x1,y1) << QPoint(x2,y2);
    rhombus << QPoint(x1,y1) << QPoint(x4,y4);
    rhombus << QPoint(x3,y3) << QPoint(x2,y2);
    painter->setBrush(Qt::yellow);
    painter->drawPolygon(rhombus);
    centerOfGrav();
}

double Rhombus::square()
{
    return 2*sqrt(pow(x1-x3,2)+pow(y1-y3,2))/2*sqrt(pow(x2-x4,2)+pow(y2-y4,2))/2;
}

double Rhombus::perimetr()
{
    return sqrt(pow(x1 - x2,2) + pow(y1 - y2,2)) * 4;
}

void Rhombus::centerOfGrav()
{
    xGrav = x1 + (x3 - x1)/2;
    yGrav = y1;
    this->setTransformOriginPoint(xGrav, yGrav);
}

void Rhombus::setCoord(int x1, int y1, int d1, int d2)
{
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x1 + d1 / 2;
    this->y2 = y1 - d2 / 2;
    this->x3 = x1 + d1;
    this->y3 = y1;
    this->x4 = x1 + d1 / 2;
    this->y4 = y1 + d2 / 2;
}

const char* Rhombus::checkType()
{
    return "Rhombus";
}
