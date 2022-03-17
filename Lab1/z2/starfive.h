#ifndef STARFIVE_H
#define STARFIVE_H

#include <figure.h>

class StarFive : public Figure
{
public:
    StarFive();
    double square();
    double perimetr();
    void setCoord(int r, int R);
    const char* checkType();
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void paintStar(QPainter *painter);
    int xGrav;
    int yGrav;
    int r;
    int R;
    int n;
};

#endif // STARFIVE_H
