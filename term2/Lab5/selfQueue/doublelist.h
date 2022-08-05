#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <node.h>
#include "smartPointers.h"

template<class T>
class DoubleList
{
    Node<T>* head;
    Node<T>* tail;
    int count;

public:
    DoubleList()
    {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    ~DoubleList()
    {
        delAll();
    }

    void addToEnd(const T& data)
    {
        if (count == 0)
        {
            Node<T>* temp = new Node<T>();
            temp->next = nullptr;
            temp->prev = nullptr;
            head = tail = temp;
            // data
            temp->data = data;
        }
        else
        {
            Node<T>* temp = new Node<T>();
            temp->next = nullptr;
            temp->prev = tail;
            tail->next = temp;
            tail = temp;
            // data
            temp->data = data;
        }
        count++;
    }

    void add(int pos, const T& data)   // positions from 1 to end
    {
        if (count == 0 || pos == count + 1)
        {
            addToEnd(data);
        }
        else if (pos == 1)
        {
            Node<T>* elem = new Node<T>();
            elem->prev = nullptr;
            elem->next = head;
            head->prev = elem;
            head = elem;
            // data
            elem->data = data;
            count++;
        }
        else
        {
            Node<T>* elemCur = head;
            int i = 1;
            while (i < pos)
            {
                elemCur = elemCur->next;
                i++;
            }
            Node<T>* elemPrev = elemCur->prev;
            Node<T>* elemIns = new Node<T>();
            elemIns->prev = elemPrev;
            elemIns->next = elemCur;
            elemPrev->next = elemIns;
            elemCur->prev = elemIns;
            // data
            elemIns->data = data;
            count++;
        }
    }

    int getCount()
    {
        return count;
    }

    void del(int pos)
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
                Node<T>* elem = head;
                head = head->next;
                head->prev = nullptr;
                delete elem;
                count--;
            }
            else if (pos != count)
            {
                Node<T>* elemDel = head;
                int i = 1;
                while (i < pos)
                {
                    elemDel = elemDel->next;
                    i++;
                }
                Node<T>* elemPrev = elemDel->prev;
                Node<T>* elemNext = elemDel->next;
                elemPrev->next = elemNext;
                elemNext->prev = elemPrev;
                delete elemDel;
                count--;
            }
            else if (pos == count)
            {
                Node<T>* elem = tail;
                tail = tail->prev;
                delete elem;
                tail->next = nullptr;
                count--;
            }
        }
    }

    void delAll()
    {
        while (count != 0 )
            del(count);
    }

    Node<T>* getElem(int pos)
    {
        Node<T>* elem = head;
        int i = 1;
        while (i < pos && head != nullptr)
        {
            elem = elem->next;
            i++;
        }
        return elem;
    }
};

#endif // DOUBLELIST_H
