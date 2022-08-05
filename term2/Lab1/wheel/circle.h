#ifndef CIRCLE_H
#define CIRCLE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>

class Circle : public QGraphicsItem
{
public:
    Circle();
    ~Circle();
    void moving();
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
#endif // CIRCLE_H
