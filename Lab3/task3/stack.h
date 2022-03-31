#ifndef STACK_H
#define STACK_H

template <typename T>
class Stack
{
public:
    Stack()
    {
        arr = nullptr;
        count = 0;
    }
    ~Stack()
    {
        if (count > 0)
          delete[] arr;
        count = 0;
    }
    void push(T elem)
    {
        T* tmp;
        tmp = arr;
        arr = new T[count + 1];
        count++;
        for (int i = 0; i < count - 1; i++)
          arr[i] = tmp[i];

        arr[count - 1] = elem;

        if (count > 1)
          delete[] tmp;
    }
    T pop()
    {
        if (count == 0)
          return 0; // stack is empty
        count--;
        return arr[count];
    }
    int Count()
    {
        return count;
    }
    bool isEmpty()
    {
        return count == 0;
    }
    T top()
    {
        if (count == 0)
          return 0; // stack is empty
        if (count != 0)
            return arr[count - 1];
    }
private:
    T* arr;
    int count;
};

#endif // STACK_H
