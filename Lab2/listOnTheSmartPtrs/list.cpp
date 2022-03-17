#include "list.h"

DoubleList::DoubleList()
{
    elem = new Elem;
    length = 0;
}

DoubleList::~DoubleList() {}


int DoubleList::getLength(shared_ptr<DoubleList> ptr)
{
    return ptr->length;
}

int DoubleList::getData(int pos)
{
    shared_ptr<Elem> current = elem->next;
    for (int i = 0; i < pos; i++)
    {
        current = current->next;
    }

    return current->data;
}

void DoubleList::erase(shared_ptr<DoubleList> ptr, int pos)
{
    if (ptr->getLength(ptr) == 0)
    {
        return;
    }
    else
    {
        if (ptr->getLength(ptr) == 1)
        {
            ptr->elem->next = nullptr;
            ptr->length--;
        }
        else
        {
            shared_ptr<Elem> deleteelem = elem->next;
            for (int i = 0; i < pos; i++)
            {
                deleteelem = deleteelem->next;
            }
            (deleteelem->prev.lock())->next = deleteelem->next;
            deleteelem->next->prev = deleteelem->prev;
            ptr->length--;
        }
    }
}

void DoubleList::insert(shared_ptr<DoubleList> ptr, int pos, int numb)
{
    shared_ptr<Elem> eleminsert = make_shared<Elem>();
    eleminsert->data = numb;

    if (ptr->getLength(ptr) == 0)
    {
        elem->next = eleminsert;
        eleminsert->prev = eleminsert;
        eleminsert->next = eleminsert;
        ptr->length++;
        return;
    }
    else
    {
        shared_ptr<Elem> current = elem->next;
        for (int i = 0; i < pos; i++)
        {
            current = current->next;
        }

        eleminsert->next = current;
        eleminsert->prev = current->prev;
        (current->prev.lock())->next = eleminsert;
        current->prev = eleminsert;
        ptr->length++;
        return;

    }
}
