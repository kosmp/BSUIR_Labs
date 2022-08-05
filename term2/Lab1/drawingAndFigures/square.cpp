#include "square.h"

Square::Square()
{
    x1 = 100;
    y1 = 100;
    x2 = 300;
    y2 = 100;
    x3 = 300;
    y3 = 300;
    x4 = 100;
    y4 = 300;
}

void Square::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPolygon square;
    square << QPoint(x1,y1) << QPoint(x2,y2);
    square << QPoint(x1,y1) << QPoint(x4,y4);
    square << QPoint(x3,y3) << QPoint(x4,y4);
    square << QPoint(x3,y3) << QPoint(x2,y2);
    painter->setBrush(Qt::red);
    painter->drawPolygon(square);
    centerOfGrav();
}

double Square::square()
{
    return pow(sqrt(pow((x1-x2),2)+pow((y1-y2),2)),2);
}

double Square::perimetr()
{
    return sqrt(pow((x1-x2),2)+pow((y1-y2),2))*4;
}

void Square::centerOfGrav()
{
    xGrav = x1+(x3-x1)/2;
    yGrav = y1+(y3-y1)/2;
    this->setTransformOriginPoint(xGrav, yGrav);
}

void Square::setCoord(int x1, int y1, int side)
{
    this->x1=x1;
    this->y1=y1;
    this->x3=x1+side;
    this->y3=y1+side;
    this->x2=x1+side;
    this->y2=y1;
    this->x4=x1;
    this->y4=y1+side;
}

const char* Square::checkType()
{
    return "Square";
}
