#ifndef SELFSTACK_H
#define SELFSTACK_H

template <class T>
class stack
{
private:
    int _size;
    int _capacity;
    T* arr = nullptr;

public:
    stack()
    {
        _size = 0;
        _capacity = 20;
        arr = new T[_capacity];
    }

    stack(const stack<T>& other)
    {
        if (arr != nullptr)
        delete[] arr;
        arr = new T[other._capacity];
        for (int i = 0; i < other._capacity; i++)
        {
            arr[i] = other.arr[i];
        }
        _size = other._size;
        _capacity = other._capacity;
    }

    ~stack()
    {
        if (arr != nullptr)
        delete[] arr;
    }

    stack<T>& operator=(const stack<T>& other)
    {
        if (arr != nullptr)
        delete[] arr;
        arr = new T[other._capacity];
        for (int i = 0; i < other._capacity; i++)
        {
            arr[i] = other.arr[i];
        }
        _capacity = other._capacity;
        _size = other._size;
        return *this;
    }

    T& top()
    {
        return arr[_size - 1];
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

    void push(const T& value)
    {
        if (_size == _capacity)
        {
            T* newArr = new T[_capacity * 2];
            for (int i = 0; i < _capacity; i++)
                newArr[i] = arr[i];
            newArr[_capacity] = value;
            _capacity *= 2;
            _size++;
            delete[] arr;
            arr = newArr;
        }
        else
        {
            arr[_size] = value;
            _size++;
        }
    }

    void pop()
    {
        if (_size == 0)
        {
            return;
        }
        else
        {
            _size--;
        }
    }
};

#endif // SELFSTACK_H
