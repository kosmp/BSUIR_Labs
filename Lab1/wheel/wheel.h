#ifndef WHEEL_H
#define WHEEL_H

#include <circle.h>

class Wheel : public Circle
{
public:
    Wheel();
    ~Wheel();
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void paintingWheel(QPainter *painter);
};

#endif // WHEEL_H
