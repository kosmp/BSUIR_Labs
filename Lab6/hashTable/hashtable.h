#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "selfStack.h"
#include <QString>

class HashTable
{
private:
    stack<int>* arr;
    int size;
public:
    HashTable()
    {
        size = 10;
        arr = new stack<int>[size];
    }

    HashTable(int s)
    {
        size = s;
        arr = new stack<int>[size];
    }

    ~HashTable()
    {
        delete[] arr;
    }

    int hashFunction(int key)
    {
        return key % size;
    }

    void insertItem(int data)
    {
        int index = hashFunction(data);
        if (findStackWithValue(data) == -1)
            arr[index].push(data);
    }

    void deleteItem(int data)
    {
        int index = hashFunction(data);
        stack<int> tmp = arr[index];
        stack<int> tmpNew;
        int sizeTmp = (int)tmp.size();
        bool find = false;
        for (int i = 0; i < sizeTmp; i++)
        {
            if (tmp.top() != data || find)
            {
                tmpNew.push(tmp.top());
                tmp.pop();
            }
            else
            {
                find = true;
                tmp.pop();
            }
        }
        int sizeTmpNew = (int)tmpNew.size();
        for (int i = 0; i < sizeTmpNew; i++)
        {
            tmp.push(tmpNew.top());
            tmpNew.pop();
        }
        arr[index] = tmp;
    }

    int findStackWithMax()
    {
        int max = -1;
        int indOfStack = -1;
        for (int i = 0; i < size; i++)
        {
            stack<int> tmp = arr[i];
            int sizeOfArrI = (int)arr[i].size();
            for (int j = 0; j < sizeOfArrI; j++)
            {
                if (tmp.top() >= max)
                {
                    max = tmp.top();
                    indOfStack = i;
                    tmp.pop();
                }
                else
                {
                    tmp.pop();
                }
            }
        }
        return indOfStack;
    }

    int findStackWithValue(int value)
    {
        int indOfStack = -1;
        for (int i = 0; i < size; i++)
        {
            stack<int> tmp = arr[i];
            int sizeOfArrI = (int)arr[i].size();
            for (int j = 0; j < sizeOfArrI; j++)
            {
                if (tmp.top() == value)
                {
                    indOfStack = i;
                    tmp.pop();
                    return indOfStack;
                }
                else
                {
                    tmp.pop();
                }
            }
        }
        return indOfStack;
    }

    bool empty()
    {
        for (int i = 0; i < size; i++)
            if (!arr[i].empty())
                return false;
        return true;
    }

    QString printTable()
    {
        QString table;
        for (int i = 0; i < size; i++)
        {
            stack<int> reverseOrder;
            stack<int> tmp = arr[i];
            int sizeTmp = (int)tmp.size();
            for (int j = 0; j < sizeTmp; j++)
            {
                reverseOrder.push(tmp.top());
                tmp.pop();
            }
            int sizeReverse = (int)reverseOrder.size();
            for (int j = 0;  j < sizeReverse; j++)
            {
                table.push_back(QString::number(reverseOrder.top()));
                table.push_back(' ');
                reverseOrder.pop();
            }
            table.push_back('\n');
        }
        return table;
    }
};

#endif // HASHTABLE_H
