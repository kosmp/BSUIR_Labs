#include "doublelist.h"

DoubleList::DoubleList()
{
    maxLen = 30;
    count = 0;
    arr = new Employee*[maxLen];
}

DoubleList::~DoubleList()
{
    for (int i = 0; i < count; i++)
        delete arr[i];
    delete[] arr;
    count = 0;
}

void DoubleList::addToEnd(const QString& name, const QString& surname, const QString& patronymic, const QString& departmentNum, const QString& posAtWork, const QString& dateStart)
{
    if (count == 0)
    {
        Employee* temp = new Employee();
        temp->next = -1;    // -1 like nullptr
        temp->prev = -1;
        // data
        temp->name = name;
        temp->surname = surname;
        temp->patronymic = patronymic;
        temp->departmentNum = departmentNum;
        temp->posAtWork = posAtWork;
        temp->dateStart = dateStart;
        arr[0] = temp;
    }
    else
    {
        Employee* temp = new Employee();
        temp->next = -1;
        temp->prev = count - 1;
        // data
        temp->name = name;
        temp->surname = surname;
        temp->patronymic = patronymic;
        temp->departmentNum = departmentNum;
        temp->posAtWork = posAtWork;
        temp->dateStart = dateStart;
        arr[count] = temp;
    }
    count++;
}


void DoubleList::del(int pos)   // after deleting an element, you need to move all elements one to the left
{
    if (count != 0)
    {
        if (pos == 0 && pos + 1 == count)   // only 1 element
        {
             delete arr[0];
             count--;
        }
        else if (pos == 0)  // if first element and not only 1
        {
            // shift all by 1
            for (int i = 0; i < count - 1; i++)
            {
                arr[i]->name = arr[i+1]->name;
                arr[i]->surname = arr[i+1]->surname;
                arr[i]->patronymic = arr[i+1]->patronymic;
                arr[i]->departmentNum = arr[i+1]->departmentNum;
                arr[i]->dateStart = arr[i+1]->dateStart;
                arr[i]->next = arr[i+1]->next;
                arr[i]->prev = arr[i+1]->prev;
            }
            delete arr[count - 1];
            count--;
            // for each element need to change next and prev index
            for (int i = 0; i < count; i++)
            {
                if (i == 0)
                {
                    arr[i]->next--;
                    arr[i]->prev = -1;  // -1 like nullptr
                    continue;
                }
                if (i == count - 1)
                {
                    arr[i]->prev--;
                    arr[i]->next = -1;
                    continue;
                }
                arr[i]->next--;
                arr[i]->prev--;
            }
        }
        else if (pos + 1 != count)
        {
            for (int i = pos; i < count - 1; i++)
            {
                arr[i]->name = arr[i+1]->name;
                arr[i]->surname = arr[i+1]->surname;
                arr[i]->patronymic = arr[i+1]->patronymic;
                arr[i]->departmentNum = arr[i+1]->departmentNum;
                arr[i]->dateStart = arr[i+1]->dateStart;
                if (i == count - 2) // if last
                {
                    arr[i]->next = -1;
                    arr[i]->prev--;
                    continue;
                }
                arr[i]->next = arr[i+1]->next--;
                arr[i]->prev = arr[i+1]->prev--;
            }
            delete arr[count - 1];
            count--;
        }
        else if (pos + 1 == count)
        {
            delete arr[pos];
            arr[pos - 1]->next = -1;
            arr[pos - 1]->prev--;
            count--;
        }
    }
}


Employee* DoubleList::getElem(int pos)
{
    return arr[pos];
}

void DoubleList::delAll()
{
    for (int i = 0; i < count; i++)
        delete arr[i];
    count = 0;
}

int DoubleList::getCount()
{
    return count;
}
