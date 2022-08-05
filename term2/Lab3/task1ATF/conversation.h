#ifndef CONVERSATION_H
#define CONVERSATION_H

#include <QString>

class Conversation
{
public:
    Conversation();
    QString date;
    QString code;
    QString city;
    QString time;
    QString tariff;
    QString telNumThisCity;
    QString telNumSubscriber;
    Conversation* next;
    Conversation* prev;
};

#endif // CONVERSATION_H
