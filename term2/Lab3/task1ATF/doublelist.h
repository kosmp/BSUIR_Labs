#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <conversation.h>

class DoubleList
{
public:
    DoubleList();
    ~DoubleList();
    Conversation* head;
    Conversation* tail;
    int count;

    void addToEnd(const QString& date, const QString& code, const QString& city, const QString& time, const QString& tariff, const QString& telNumThisCity, const QString& telNumSubscriber);
    void add(int pos, const QString& date, const QString& code, const QString& city, const QString& time, const QString& tariff, const QString& telNumThisCity, const QString& telNumSubscriber);
    int getCount();
    void del(int pos);
    void delAll();
    Conversation* getElem(int pos);
};

#endif // DOUBLELIST_H
