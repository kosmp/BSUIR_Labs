#ifndef DEQUE_H
#define DEQUE_H
#include <iostream>
#include <QDebug>

template<class T>
class deque
{
public:
    class iterator;
private:
    T** arr;
    int _size;
    int _capacity;
    iterator start;
    iterator finish;
public:

    deque()
    {
        arr = new T*[4];
        for (int i = 0; i < 4; i++)
            arr[i] = reinterpret_cast<T*>(new int8_t[10 * sizeof(T)]);
        _size = 0;
        _capacity = 40;
    }

    ~deque()
    {
        while (start != finish)
        {
            start->~T();
            start++;
        }
        start->~T();
        for (int i = 0; i < _capacity / 10; i++)
            delete[] reinterpret_cast<int8_t*>(arr[i]);
        delete[] arr;
    }

    void push_front(const T& value)
    {
        if (start.getRow() == 0 && start.getCol() == 0 && start.getPointer())
        {
            _capacity *= 2;

            int oldRowCount = (_capacity / 10) / 2;
            int newRowCount = _capacity / 10;
            int mid = (newRowCount - oldRowCount) / 2;

            T** newArr = new T*[newRowCount];
            for (int i = 0; i < mid; i++)
                newArr[i] = reinterpret_cast<T*>(new int8_t[10 * sizeof(T)]);

            for (int i = mid, j = 0; i < mid + oldRowCount; i++, j++)
                newArr[i] = arr[j];
            delete[] arr;

            for (int i = mid + oldRowCount; i < newRowCount; i++)
                newArr[i] = reinterpret_cast<T*>(new int8_t[10 * sizeof(T)]);

            arr = newArr;

            int row = mid + finish.getRow();
            int col = finish.getCol();
            finish.setCoord(row, col);

            start.setCoord(mid, 0);
            start.setCurrArr(arr);
            start--;

            new(&arr[start.getRow()][start.getCol()]) T(value);
            _size++;
        }
        else
        {
            if (_size == 0)
            {
                int row;
                if (finish.getRow() > 0)
                {
                    if (finish.getCol() == 9)
                       row = finish.getRow() + 1;
                    else
                       row = finish.getRow();
                }
                else
                {
                    row = (_capacity / 10) / 2 - 1;
                }
                int col;
                if (finish.getRow() > 0)
                {
                    if (finish.getCol() == 9)
                        col = 0;
                    else
                        col = finish.getCol() + 1;
                }
                else
                {
                    col = 0;
                }
                start = &arr[row][col];
                start.setCoord(row, col);
                finish = &arr[row][col];
                finish.setCoord(row, col);
                start.setCurrArr(arr);
                finish.setCurrArr(arr);
            }
            else
            {
                start.setCurrArr(arr);
                --start;
            }
            new(&arr[start.getRow()][start.getCol()]) T(value);
            _size++;
        }

    }

    void pop_front()
    {
        if (_size == 0)
            return;

        start->~T();
        _size--;
        ++start;
        if (_size == 0)
            start = finish = nullptr;
    }

    void push_back(const T& value)
    {
        if (finish.getCol() == 9 && finish.getRow() == _capacity / 10 - 1)
        {
            _capacity *= 2;

            int oldRowCount = (_capacity / 10) / 2;
            int newRowCount = _capacity / 10;
            int mid = (newRowCount - oldRowCount) / 2;

            T** newArr = new T*[newRowCount];
            for (int i = 0; i < mid; i++)
                newArr[i] = reinterpret_cast<T*>(new int8_t[10 * sizeof(T)]);

            for (int i = mid, j = 0; i < mid + oldRowCount; i++, j++)
                newArr[i] = arr[j];
            delete[] arr;

            for (int i = mid + oldRowCount; i < newRowCount; i++)
                newArr[i] = reinterpret_cast<T*>(new int8_t[10 * sizeof(T)]);
            new(&newArr[mid + oldRowCount][0]) T(value);

            int newStartRow = start.getRow() + mid;
            int colStart = start.getCol();
            start.setCoord(newStartRow, colStart);

            finish = &newArr[mid + oldRowCount][0];
            finish.setCoord(mid + oldRowCount, 0);

            _size++;
            arr = newArr;
            start.setCurrArr(arr);
            finish.setCurrArr(arr);
        }
        else
        {
            int row;
            if (finish.getRow() > 0)
            {
                if (finish.getCol() == 9)
                   row = finish.getRow() + 1;
                else
                   row = finish.getRow();
            }
            else
            {
                row = (_capacity / 10) / 2 - 1;
            }
            int col;
            if (finish.getRow() > 0)
            {
                if (finish.getCol() == 9)
                    col = 0;
                else
                    col = finish.getCol() + 1;
            }
            else
            {
                col = 0;
            }

            new(&arr[row][col]) T(value);
            finish = &arr[row][col];
            finish.setCoord(row, col);
            finish.setCurrArr(arr);

            if (_size == 0)
            {
                start = &arr[row][col];
                start.setCoord(row, col);
                start.setCurrArr(arr);
            }
            _size++;
        }
    }

    void pop_back()
    {
        if (_size == 0)
            return;

        finish.setCurrArr(arr);
        finish->~T();
        _size--;
        --finish;
        if (_size == 0)
            start = finish = nullptr;
    }

    void resize( size_t count, const T& value )
    {
        if (count > _size)
        {
            while (_size != count)
                push_back(value);
        }
        else
        {
            while (_size != count)
                pop_back();
        }
    }

    T& operator()(size_t fInd, size_t sInd)
    {
        return arr[fInd][sInd];
    }

    void clear()
    {
        while(_size != 0)
            pop_back();
    }

    int size() const
    {
        return _size;
    }

    bool empty()
    {
        if (_size == 0)
            return true;
        return false;
    }

    iterator begin()
    {
        return start;
    }

    iterator end()
    {
        return finish;
    }

    T& front()
    {
        return *start;
    }

    T& back()
    {
        return *finish;
    }

    class iterator
    {
        T* m_iterator;
        T** currArr;
        int row = 0, col = 0;

    public:
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef std::random_access_iterator_tag iterator_category;
        typedef std::ptrdiff_t difference_type;

        iterator(T* iter = nullptr) : m_iterator(iter) { }

        void setCoord(int row, int col)
        {
            this->row = row;
            this->col = col;
        }

        void setCurrArr(T** arr)
        {
            currArr = arr;
        }

        int getRow()
        {
            return row;
        }

        int getCol()
        {
            return col;
        }

        pointer getPointer()
        {
            return m_iterator;
        }

        bool operator==(const iterator& other) const noexcept { return m_iterator == other.m_iterator; }

        bool operator!=(const iterator& other) const noexcept { return m_iterator != other.m_iterator; }

        reference operator*() const noexcept { return *m_iterator; }

        reference operator()(size_t fInd, size_t sInd) const
        {
            return currArr[fInd][sInd];
        }

        pointer operator->() const noexcept { return m_iterator; }

        iterator& operator++()
        {
            if (col == 9)
            {
                row++;
                col = 0;
                m_iterator = &currArr[row][col];
                return *this;
            }
            col++;
            ++m_iterator;
            return *this;
        }

        iterator operator++(int) noexcept
        {
            if (col == 9)
            {
                row++;
                col = 0;
                m_iterator = &currArr[row][col];
                return m_iterator;
            }
            col++;
            return m_iterator++;
        }

        iterator& operator--()
        {
            if (col == 0)
            {
                row--;
                col = 9;
                m_iterator = &currArr[row][col];
                return *this;
            }
            col--;
            --m_iterator;
            return *this;
        }

        iterator operator--(int) noexcept
        {
            if (col == 0)
            {
                row--;
                col = 9;
                m_iterator = &currArr[row][col];
                return m_iterator;
            }
            col--;
            return m_iterator--;
        }
    };
};

#endif // DEQUE_H
