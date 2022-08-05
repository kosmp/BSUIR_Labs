#ifndef SQUARE_H
#define SQUARE_H

#include <triangle.h>

class Square : public Triangle
{
public:
    Square();
    double square();
    double perimetr();
    void centerOfGrav();
    void setCoord(int x1, int y1, int side);
    const char* checkType();
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    int x1, x2, x3, x4;
    int y1, y2, y3, y4;
    int xGrav;
    int yGrav;
};

#endif // SQUARE_H
