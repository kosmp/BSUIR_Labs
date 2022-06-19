#include "figure.h"

Figure::Figure()
{

}

QRectF Figure::boundingRect() const
{
    return QRectF(0,0,700,700);
}

void Figure::rotating(int time)
{
    this->setRotation(time);
}

void Figure::moving(int check)
{
    if(check == 1)
    {
        this->moveBy(1, 0);
        if(x() == 650)
        {
            this->moveBy(-950, 0);
        }
    }
    else if (check == 2)
    {
        this->moveBy(-1, 0);
        if(x() == -320)
        {
            this->moveBy(950, 0);
        }
    }
    else if (check == 3)
    {
        this->moveBy(0, -1);
        if(y() == -300)
        {
            this->moveBy(0, 850);
        }
    }
    else if (check == 4)
    {
        this->moveBy(0, 1);
        if(y() == 650)
        {
            this->moveBy(0, -800);
        }
    }
}

void Figure::scaling(int check, float scale)
{
        if(check == 1)
        {
            this->setScale(scale);
        }
        else if (check == 2)
        {
            this->setScale(scale);
        }
}

double Figure::square(){return -1;}
double Figure::perimetr(){return -2;}
void Figure::setCoordTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
    Q_UNUSED(x1);
    Q_UNUSED(y1);
    Q_UNUSED(x2);
    Q_UNUSED(y2);
    Q_UNUSED(x3);
    Q_UNUSED(y3);
}
void Figure::setCoord(int x1, int y1, int side)
{
    Q_UNUSED(x1);
    Q_UNUSED(y1);
    Q_UNUSED(side);
}
void Figure::setCoordHexagon(int R)
{
    Q_UNUSED(R);
}
void Figure::setCoord(int par1, int par2)
{
    Q_UNUSED(par1);
    Q_UNUSED(par2);
}
void Figure::setCoord(int par1, int par2, int par3, int par4)
{
    Q_UNUSED(par1);
    Q_UNUSED(par2);
    Q_UNUSED(par3);
    Q_UNUSED(par4);
}

const char* Figure::checkType()
{
    return "UnknowFgiure";
}
