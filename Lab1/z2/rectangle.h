#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <figure.h>

class Rectangle : public Figure
{
public:
    Rectangle();
    double square();
    double perimetr();
    void centerOfGrav();
    void setCoord(int x1, int y1, int w, int h);
    const char* checkType();
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    int x1, y1;
    int w, h;
    int xGrav;
    int yGrav;
};

#endif // RECTANGLE_H
