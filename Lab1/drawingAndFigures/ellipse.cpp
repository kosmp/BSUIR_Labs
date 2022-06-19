#include "ellipse.h"

Ellipse::Ellipse()
{
    x = 150;
    y = 150;
    w = 300;
    h = 200;
}

void Ellipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(x, y, w, h);
    centerOfGrav(w, h);
}

double Ellipse::square()
{
    return M_PI*w/2*h/2;
}
double Ellipse::perimetr()
{
    if (w>h)
        return 4*(M_PI*w*h/4+(w/2-h/2))/(w/2+h/2);
    else
        return 4*(M_PI*h*w/4+(h/2-w/2))/(h/2+w/2);
}

void Ellipse::centerOfGrav(int w, int h)
{
    xGrav = x + w / 2;
    yGrav = y + h / 2;
    this->setTransformOriginPoint(xGrav, yGrav);
}

void Ellipse::setCoord(int x, int y, int w, int h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

const char* Ellipse::checkType()
{
    return "Ellipse";
}

