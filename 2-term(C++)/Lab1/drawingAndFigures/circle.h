#ifndef CIRCLE_H
#define CIRCLE_H

#include <ellipse.h>

class Circle : public Ellipse
{
public:
    Circle();
    void setCoord(int x, int y, int r);
    const char* checkType();
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int r;
};

#endif // CIRCLE_H
