#include "triangle.h"

Triangle::Triangle()
{
    x1 = 100;
    y1 = 300;
    x2 = 250;
    y2 = 100;
    x3 = 400;
    y3 = 300;
}

void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPolygon triangle;
    triangle << QPoint(x1,y1) << QPoint(x2,y2) << QPoint(x3,y3);
    painter->setBrush(Qt::green);
    painter->drawPolygon(triangle);
    centerOfGrav();
}

double Triangle::square()
{
    double a, b, c;
    a = sqrt(pow((x1-x2),2)+pow((y1-y2),2));
    b = sqrt(pow((x2-x3),2)+pow((y2-y3),2));
    c = sqrt(pow((x3-x1),2)+pow((y3-y1),2));
    double p = perimetr()/2;
    return sqrt(p*(p-a)*(p-b)*(p-c));
}

double Triangle::perimetr()
{
    return sqrt(pow((x1-x2),2)+pow((y1-y2),2)) + sqrt(pow((x2-x3),2)+pow((y2-y3),2)) + sqrt(pow((x3-x1),2)+pow((y3-y1),2));
}

void Triangle::centerOfGrav()
{
    xGrav = (x1 + x2 + x3) / 3;
    yGrav = (y1 + y2 + y3) / 3;
    this->setTransformOriginPoint(xGrav, yGrav);
}

void Triangle::setCoordTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
    this->x1=x1;
    this->y1=y1;
    this->x2=x2;
    this->y2=y2;
    this->x3=x3;
    this->y3=y3;
}

const char* Triangle::checkType()
{
    return "Triangle";
}
