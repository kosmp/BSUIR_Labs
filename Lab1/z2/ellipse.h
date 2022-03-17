#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <figure.h>

class Ellipse : public Figure
{
public:
    Ellipse();
    double square();
    double perimetr();
    void centerOfGrav(int w, int h);
    void setCoord(int x, int y, int w, int h);
    const char* checkType();
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int xGrav;
    int yGrav;
    int w, h, x, y;
};

#endif // ELLIPSE_H
