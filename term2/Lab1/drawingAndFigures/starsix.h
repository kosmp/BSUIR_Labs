#ifndef STARSIX_H
#define STARSIX_H

#include <starfive.h>

class StarSix : public StarFive
{
public:
    StarSix();
    const char* checkType();
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // STARSIX_H
