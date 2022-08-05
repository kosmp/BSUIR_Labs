#ifndef QUEUE_H
#define QUEUE_H
#include "doublelist.h"

template <class T>
class queue
{
    int _size;
    DoubleList<T>* list = new DoubleList<T>();

public:
    queue()
    {
        _size = 0;
    }

    queue(const queue<T>& other)
    {
        _size = other._size;
        if (list->getCount() != 0)
            list->delAll();
        for (int k = 1; k <= other.list->getCount(); k++)
            list->addToEnd(other.list->getElem(k)->data);
    }

    queue(queue<T>&& other)
    {
        _size = other._size;
        if (list->getCount() != 0)
            list->delAll();
        for (int i = 1; i <= other.list->getCount(); i++)
            list->addToEnd(other.list->getElem(i)->data);

        other.list->delAll();
        delete other.list;
        other.list = new DoubleList<T>();
    }

    ~queue()
    {
        if (list != nullptr)
        {
            list->delAll();
            delete list;
        }
    }

    queue& operator=(const queue<T>& other)
    {
        _size = other._size;
        if (list->getCount() != 0)
            list->delAll();
        for (int i = 1; i <= other.list->getCount(); i++)
            list->addToEnd(other.list->getElem(i)->data);
        return *this;
    }

    int size() const
    {
        return _size;
    }

    bool empty() const
    {
        if (_size == 0)
            return true;
        return false;
    }

    T& back()
    {
        return list->getElem(_size)->data;
    }

    T& front()
    {
        return list->getElem(1)->data;
    }

    void push(const T& value)
    {
        list->addToEnd(value);
        _size++;
    }

    void pop()
    {
        list->del(1);
        _size--;
    }

    void swap(queue<T>& other) noexcept
    {
        std::swap(_size, other._size);
        std::swap(list, other.list);
    }
};

#endif // QUEUE_H
