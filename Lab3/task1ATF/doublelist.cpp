#include "doublelist.h"

DoubleList::DoubleList()
{
    head = nullptr;
    tail = nullptr;
    count = 0;
}

DoubleList::~DoubleList()
{
    delAll();
}

void DoubleList::addToEnd(const QString& date, const QString& code, const QString& city, const QString& time, const QString& tariff, const QString& telNumThisCity, const QString& telNumSubscriber)
{
    if (count == 0)
    {
        Conversation* temp = new Conversation();
        temp->next = nullptr;
        temp->prev = nullptr;
        head = tail = temp;
        // data
        temp->date = date;
        temp->code = code;
        temp->city = city;
        temp->time = time;
        temp->tariff = tariff;
        temp->telNumThisCity = telNumThisCity;
        temp->telNumSubscriber = telNumSubscriber;
    }
    else
    {
        Conversation* temp = new Conversation();
        temp->next = nullptr;
        temp->prev = tail;
        tail->next = temp;
        tail = temp;
        // data
        temp->date = date;
        temp->code = code;
        temp->city = city;
        temp->time = time;
        temp->tariff = tariff;
        temp->telNumThisCity = telNumThisCity;
        temp->telNumSubscriber = telNumSubscriber;
    }
    count++;
}

void DoubleList::add(int pos, const QString& date, const QString& code, const QString& city, const QString& time, const QString& tariff, const QString& telNumThisCity, const QString& telNumSubscriber)   // positions from 1 to end
{
    if (count == 0 || pos == count + 1)
    {
        addToEnd(date, code, city, time, tariff, telNumThisCity, telNumSubscriber);
    }
    else if (pos == 1)
    {
        Conversation* elem = new Conversation();
        elem->prev = nullptr;
        elem->next = head;
        head->prev = elem;
        head = elem;
        // data
        elem->date = date;
        elem->code = code;
        elem->city = city;
        elem->time = time;
        elem->tariff = tariff;
        elem->telNumThisCity = telNumThisCity;
        elem->telNumSubscriber = telNumSubscriber;
        count++;
    }
    else
    {
        Conversation* elemCur = head;
        int i = 1;
        while (i < pos)
        {
            elemCur = elemCur->next;
            i++;
        }
        Conversation* elemPrev = elemCur->prev;
        Conversation* elemIns = new Conversation();
        elemIns->prev = elemPrev;
        elemIns->next = elemCur;
        elemPrev->next = elemIns;
        elemCur->prev = elemIns;
        // data
        elemIns->date = date;
        elemIns->code = code;
        elemIns->city = city;
        elemIns->time = time;
        elemIns->tariff = tariff;
        elemIns->telNumThisCity = telNumThisCity;
        elemIns->telNumSubscriber = telNumSubscriber;
        count++;
    }
}

int DoubleList::getCount()
{
    return count;
}

void DoubleList::del(int pos)
{
    if (count != 0)
    {
        if (pos == 1 && pos == count)
        {
             tail = nullptr;
             delete head;
             count--;
        }
        else if (pos == 1)
        {
            Conversation* elem = head;
            head = head->next;
            head->prev = nullptr;
            delete elem;
            count--;
        }
        else if (pos != count)
        {
            Conversation* elemDel = head;
            int i = 1;
            while (i < pos)
            {
                elemDel = elemDel->next;
                i++;
            }
            Conversation* elemPrev = elemDel->prev;
            Conversation* elemNext = elemDel->next;
            elemPrev->next = elemNext;
            elemNext->prev = elemPrev;
            delete elemDel;
            count--;
        }
        else if (pos == count)
        {
            Conversation* elem = tail;
            tail = tail->prev;
            delete elem;
            tail->next = nullptr;
            count--;
        }
    }
}

void DoubleList::delAll()
{
    while (count != 0 )
        del(count);
}

Conversation* DoubleList::getElem(int pos)
{
    Conversation* elem = head;
    int i = 1;
    while (i < pos && head != nullptr)
    {
        elem = elem->next;
        i++;
    }
    return elem;
}
