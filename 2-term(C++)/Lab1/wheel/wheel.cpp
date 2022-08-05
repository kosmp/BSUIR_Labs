#include "wheel.h"

Wheel::Wheel() : Circle(){}

Wheel::~Wheel(){}

void Wheel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    paintingWheel(painter);
}

void Wheel::paintingWheel(QPainter *painter)
{
    QPen picture;
    picture.setWidth(10);
    painter->setPen(picture);
    Circle::paint(painter, 0, 0);
    picture.setWidth(5);
    picture.setColor(Qt::gray);
    painter->setPen(picture);
    QPolygon polygon;
    polygon << QPoint(0,0) << QPoint(0,-97);
    polygon << QPoint(0,0) << QPoint(0,97);
    polygon << QPoint(0,0) << QPoint(-97,0);
    polygon << QPoint(0,0) << QPoint(97,0);
    painter->drawPolygon(polygon);
}
