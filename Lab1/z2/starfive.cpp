#include "starfive.h"

StarFive::StarFive() : Figure()
{
    n = 5;
    xGrav = 300;
    yGrav = 300;
    r = 100;
    R = 200;
}

void StarFive::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    paintStar(painter);
}

void StarFive::paintStar(QPainter *painter)
{
    QPolygon starFive;
    QPoint *p = new QPoint[n*2];
    int a = 0;
    for (int i = 0; i < n*2; i++)     // заполнение массива вершинами звезды
    {
        if (i % 2 == 0)
         {
            p[i].setX(xGrav+r*cos(a*M_PI/180));
            p[i].setY(yGrav-r*sin(a*M_PI/180));
         }
         else
         {
            p[i].setX(xGrav+R*cos(a*M_PI/180));
            p[i].setY(yGrav-R*sin(a*M_PI/180));
         }
        a=a+180/n;
    }
    for (int i=0; i<n*2; i++)     // соединение вершин
    {
        starFive << p[i];
    }
    painter->setBrush(Qt::green);
    painter->drawPolygon(starFive);
    delete []p;
    this->setTransformOriginPoint(xGrav, yGrav);
}

double StarFive::square()
{
    return n*r*R*sin(M_PI/n);
}

double StarFive::perimetr()
{
    return 2*n*sqrt(R*R+r*r-2*R*r*cos(M_PI/n));
}

void StarFive::setCoord(int r, int R)
{
    this->r = r;
    this->R = R;
}

const char* StarFive::checkType()
{
    return "StarFive";
}
