#ifndef FIGURE_H
#define FIGURE_H

#include <QGraphicsItem>
#include <QPainter>
#include <cmath>

class Figure : public QGraphicsItem
{
public:
    Figure();
    void rotating(int time);
    void moving(int check);
    void scaling(int check, float scale);
    virtual double square();
    virtual double perimetr();
    virtual void setCoordTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
    virtual void setCoord(int x1, int y1, int side);
    virtual void setCoordHexagon(int R);
    virtual void setCoord(int par1, int par2);
    virtual void setCoord(int par1, int par2, int par3, int par4);  // rhombus, rectangle, ellipse
    virtual const char* checkType();
protected:
    QRectF boundingRect() const;
};

#endif // FIGURE_H
