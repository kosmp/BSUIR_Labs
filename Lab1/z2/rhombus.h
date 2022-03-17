#ifndef RHOMBUS_H
#define RHOMBUS_H

#include <figure.h>

class Rhombus : public Figure
{
public:
    Rhombus();
    void centerOfGrav();
    double square();
    double perimetr();
    void setCoord(int x1, int y1, int d1, int d2);
    const char* checkType();
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    int x1, x2, x3, x4;
    int y1, y2, y3, y4;
    int xGrav;
    int yGrav;
};

#endif // RHOMBUS_H
