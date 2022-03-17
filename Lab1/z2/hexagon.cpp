#include "hexagon.h"

Hexagon::Hexagon()
{
    R = 100;
    xGrav = 200;
    yGrav = 200;
    points();
}
Hexagon::~Hexagon()
{
    delete[] p;
}

void Hexagon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPolygon hexagon;
    for (int i=0; i<6; i++)     // соединение вершин
    {
        hexagon << p[i];
    }
    painter->setBrush(Qt::green);
    painter->drawPolygon(hexagon);
    this->setTransformOriginPoint(xGrav, yGrav);
}

void Hexagon::points()
{
    int a = 0;
    for (int i = 0; i < 6; i++)     // заполнение массива вершинами многоугольника
    {
        p[i].setX(xGrav+R*cos(a*M_PI/180));
        p[i].setY(yGrav-R*sin(a*M_PI/180));
        if (i+1 == 2)
        {
            x2 = p[i].x();
            y2 = p[i].y();
        }
        else if (i+1 == 3)
        {

            x3 = p[i].x();
            y3 = p[i].y();
        }
        a=a+360/6;
    }
}

double Hexagon::square()
{
    return 3*sqrt(3)/2*(pow((x2-x3),2)+pow((y2-y3),2));
}
double Hexagon::perimetr()
{
    return 6*sqrt(pow((x2-x3),2)+pow((y2-y3),2));
}

void Hexagon::setCoordHexagon(int R)
{
    this->R=R;
    points();
}

const char* Hexagon::checkType()
{
    return "Hexagon";
}
