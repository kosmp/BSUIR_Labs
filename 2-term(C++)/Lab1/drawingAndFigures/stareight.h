#ifndef STAREIGHT_H
#define STAREIGHT_H

#include <starsix.h>

class StarEight : public StarSix
{
public:
    StarEight();
    const char* checkType();
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // STAREIGHT_H
