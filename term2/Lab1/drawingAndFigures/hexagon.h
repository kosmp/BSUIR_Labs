#ifndef HEXAGON_H
#define HEXAGON_H

#include <square.h>

class Hexagon : public Square
{
public:
    Hexagon();
    ~Hexagon();
    double square();
    double perimetr();
    void setCoordHexagon(int R);
    const char* checkType();
    void points();
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QPoint *p = new QPoint[6];
    int R;
    int x2, x3;
    int y2, y3;
    int xGrav, yGrav;
};

#endif // HEXAGON_H
