#ifndef LIST_H
#define LIST_H

#include <smartp.h>

struct Elem
{
    int data;
    shared_ptr<Elem> next;
    weak_ptr<Elem> prev;
};

class DoubleList
{
public:
    DoubleList();
    ~DoubleList();
    int getLength (shared_ptr<DoubleList> ptr);
    int getData (int pos);
    void insert (shared_ptr<DoubleList> ptr, int pos, int numb);
    void erase (shared_ptr<DoubleList> ptr, int pos);

private:
    int length;
    Elem* elem;
};
#endif // LIST_H
