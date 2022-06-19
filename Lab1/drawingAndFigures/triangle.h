#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <figure.h>

class Triangle : public Figure
{
public:
    Triangle();
    double square();
    double perimetr();
    void centerOfGrav();
    void setCoordTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
    const char* checkType();
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    int x1, x2, x3;
    int y1, y2, y3;
    int xGrav;
    int yGrav;

};

#endif // TRIANGLE_H
