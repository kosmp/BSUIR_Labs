#ifndef SMARTP_H
#define SMARTP_H

#include <iostream>

template <typename T>
class weak_ptr;

template <typename T>
class weak_ptr<T[]>;

template <typename T>
class shared_ptr;

template <typename T>
class shared_ptr<T[]>;

template <class T>
class unique_ptr
{
private:
    T* ptr;
public:
    unique_ptr() : ptr(nullptr) {}

    explicit unique_ptr(T* ptr) { this->ptr = ptr; }

    ~unique_ptr() { delete ptr; }

    operator bool() { return ptr; }

    T& operator*() const { return *ptr; }

    T* operator->() const { return ptr; }

    T* get() const { return ptr; }

    T* release()
    {
        T* tmp = ptr;
        ptr = nullptr;
        return tmp;
    }

    void reset(T* p)
    {
        delete ptr;
        ptr = p;
    }

    unique_ptr(unique_ptr const& other) = delete;

    unique_ptr& operator=(unique_ptr const& other) = delete;

    unique_ptr(unique_ptr&& other) : ptr(other.release()) {}

    unique_ptr& operator=(unique_ptr&& other)
    {
        reset(other.release());
        return *this;
    }

    void swap(unique_ptr& right)
    {
        T* tmp = std::move(right.ptr);
        right.ptr = std::move(ptr);
        ptr = std::move(tmp);
    }
};

template <class T>
class unique_ptr<T[]>
{
private:
    T* ptr;
public:

    explicit unique_ptr(T* ptr)
    {
        this->ptr = ptr;
    }

    ~unique_ptr() { delete[] ptr; }

    T& operator[](size_t index) const { return ptr[index]; }

    unique_ptr() : ptr(nullptr) {}

    operator bool() { return ptr; }

    T& operator*() const { return *ptr; }

    T* operator->() const { return ptr; }

    T* get() const { return ptr; }

    T* release()
    {
        T* tmp = ptr;
        ptr = nullptr;
        return tmp;
    }

    void reset(T* p)
    {
        delete[] ptr;
        ptr = p;
    }

    unique_ptr(unique_ptr const& other) = delete;

    unique_ptr& operator=(unique_ptr const& other) = delete;

    unique_ptr(unique_ptr&& other) : ptr(other.release()) {}

    unique_ptr& operator=(unique_ptr&& other)
    {
        reset(other.release());
        return *this;
    }

    void swap(unique_ptr& right)
    {
        T* tmp = std::move(right.ptr);
        right.ptr = std::move(ptr);
        ptr = std::move(tmp);
    }
};

template<class T, class... Args>
typename std::enable_if< !std::is_array<T>::value, unique_ptr<T> >::type make_unique(Args&& ...args)
{
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template <class T>
typename std::enable_if < std::is_array<T>::value, unique_ptr<T> >::type make_unique(std::size_t n)
{
    typedef typename std::remove_extent<T>::type RT;
    return unique_ptr<T>(new RT[n]);
}

struct ControlBlock
{
    int shared_count;
    int weak_count;
};

template <class T>
class shared_ptr
{
protected:
    T* ptr;
    ControlBlock* cblock;

public:
    shared_ptr() : ptr(nullptr)
    {
        cblock = nullptr;
    }

    explicit shared_ptr(T* ptr) : ptr(ptr)
    {
        cblock = new ControlBlock();
        cblock->shared_count = 1;
        cblock->weak_count = 0;
    }

    shared_ptr(shared_ptr const& other) : ptr(other.ptr)
    {
        cblock = new ControlBlock();
        cblock = other.cblock;
        ++(cblock->shared_count);
    }

    shared_ptr(shared_ptr&& other) noexcept: ptr(other.ptr)
    {
        if (cblock) delete cblock;
        if (ptr) delete ptr;
        cblock = new ControlBlock();
        cblock = other.cblock;
        other.ptr = nullptr;
        other.cblock = nullptr;
    }

    shared_ptr(weak_ptr<T> const& other) noexcept : ptr(other.ptr), cblock(other.cblock) {}

    ~shared_ptr()
    {
        if (cblock)
        {
            --(cblock->shared_count);
            if (cblock->shared_count > 0) { return; }
            if (cblock->weak_count == 0)
            {
                delete ptr;
                delete cblock;
                return;
            }
            delete ptr;
        }
    }

    operator bool() { return ptr; }

    T& operator*() const { return *ptr; }

    T* operator->() const { return ptr; }

    shared_ptr& operator=(T* other)
    {
        cblock = new ControlBlock();
        ptr = nullptr;
        cblock = nullptr;
        return *this;
    }

    shared_ptr& operator=(shared_ptr const& other)
    {
        cblock = new ControlBlock();
        ptr = other.ptr;
        cblock = other.cblock;
        ++(cblock->shared_count);
        return *this;
    }

    shared_ptr& operator=(shared_ptr&& other)
    {
        if (cblock) delete cblock;
        cblock = new ControlBlock();
        if (ptr) delete ptr;
        ptr = other.ptr;
        cblock = other.cblock;
        other.ptr = nullptr;
        other.cblock = nullptr;
        return *this;
    }

    T* get() const { return ptr; }

    long use_count() const { return cblock->shared_count; }

    void reset(T* p)
    {
        delete ptr;
        ptr = p;
    }

    void swap(shared_ptr& right)
    {
        T* tmp = std::move(right.ptr);
        right.ptr = std::move(ptr);
        ptr = std::move(tmp);
        ControlBlock* tmpBlock = std::move(right.cblock);
        right.cblock = std::move(cblock);
        cblock = std::move(tmpBlock);
    }

    friend class weak_ptr<T>;
};

template <class T>
class shared_ptr <T[]>
{
private:
    T* ptr;
    ControlBlock* cblock;

public:
    shared_ptr() : ptr(nullptr)
    {
        cblock = nullptr;
    }

    explicit shared_ptr(T* ptr) : ptr(ptr)
    {
        cblock = new ControlBlock();
        cblock->shared_count = 1;
        cblock->weak_count = 0;
    }

    shared_ptr(shared_ptr const& other) : ptr(other.ptr)
    {
        cblock = new ControlBlock();
        cblock = other.cblock;
        ++(cblock->shared_count);
    }

    shared_ptr(shared_ptr&& other) noexcept : ptr(other.ptr)
    {
        if (cblock) delete cblock;
        if (ptr) delete[] ptr;
        cblock = new ControlBlock();
        cblock = other.cblock;
        other.ptr = nullptr;
        other.cblock = nullptr;
    }

    shared_ptr(weak_ptr<T> const& other) noexcept : ptr(other.ptr), cblock(other.cblock) {}

    ~shared_ptr()
    {
        if (cblock)
        {
            --(cblock->shared_count);
            if (cblock->shared_count > 0) { return; }
            if (cblock->weak_count == 0)
            {
                delete[] ptr;
                delete cblock;
                return;
            }
            delete[] ptr;
        }
    }

    operator bool() { return ptr; }

    T& operator*() const { return *ptr; }

    T* operator->() const { return ptr; }

    shared_ptr& operator=(shared_ptr const& other)
    {
        cblock = new ControlBlock();
        ptr = other.ptr;
        cblock = other.cblock;
        ++(cblock->shared_count);
        return *this;
    }

    shared_ptr& operator=(shared_ptr&& other)
    {
        if (cblock) delete cblock;
        cblock = new ControlBlock();
        if (ptr) delete[] ptr;
        ptr = other.ptr;
        cblock = other.cblock;
        other.ptr = nullptr;
        other.cblock = nullptr;
        return *this;
    }

    T* get() const { return ptr; }

    long use_count() const { return cblock->shared_count; }

    void reset(T* p)
    {
        delete[] ptr;
        ptr = p;
    }

    void swap(shared_ptr& right)
    {
        T* tmp = std::move(right.ptr);
        right.ptr = std::move(ptr);
        ptr = std::move(tmp);
        ControlBlock* tmpBlock = std::move(right.cblock);
        right.cblock = std::move(cblock);
        cblock = std::move(tmpBlock);
    }

    T& operator[](size_t index) const { return ptr[index]; }

    friend class weak_ptr<T[]>;
};

template<class T, class... Args>
typename std::enable_if< !std::is_array<T>::value, shared_ptr<T> >::type make_shared(Args&&... args)
{
    return shared_ptr<T>(new T(std::forward<Args>(args)...));
}

template <class T>
typename std::enable_if < std::is_array<T>::value, shared_ptr<T> >::type make_shared(std::size_t n)
{
    typedef typename std::remove_extent<T>::type RT;
    return shared_ptr<T>(new RT[n]);
}

template <class T>
class weak_ptr
{
private:
    ControlBlock* cblock;
    T* ptr;
public:
    weak_ptr()
    {
        this->ptr = nullptr;
        cblock = nullptr;
    }

    weak_ptr(const shared_ptr<T>& obj)
    {
        if (obj.cblock)
        {
            this->ptr = obj.ptr;
            cblock = obj.cblock;
            ++(cblock->weak_count);
        }
    }

    weak_ptr(const weak_ptr<T>& obj)
    {
        if (obj.cblock)
        {
            this->ptr = obj.ptr;
            cblock = obj.cblock;
            ++(cblock->weak_count);
        }
        else
        {
            this->ptr = obj.ptr;	// nullptr
            cblock = obj.cblock;	// nullptr
        }
    }
    weak_ptr(const shared_ptr<T>&& obj)
    {
        if (obj.cblock)
        {
            this->ptr = std::move(obj.ptr);
            cblock = std::move(obj.cblock);
            ++(cblock->weak_count);
            --(cblock->shared_count);
        }
    }

    weak_ptr(const weak_ptr<T>&& obj) noexcept
    {
        this->ptr = std::move(obj.ptr);
        cblock = std::move(obj.cblock);
    }

    ~weak_ptr()
    {
        if (cblock)
        {
            if (cblock->weak_count > 0)
            {
                --(cblock->weak_count);
                if (cblock->shared_count == 0 && cblock->weak_count == 0)
                {
                    delete cblock;
                }
            }
        }
        cblock = nullptr;
        ptr = nullptr;
    }

    weak_ptr& operator=(const shared_ptr<T>& obj) noexcept
    {
        if (obj.cblock)
        {
            this->ptr = obj.ptr;
            cblock = obj.cblock;
            ++(cblock->weak_count);
        }
        return *this;
    }

    weak_ptr& operator=(const weak_ptr<T>& obj) noexcept
    {
        if (obj.cblock)
        {
            this->ptr = obj.ptr;
            cblock = obj.cblock;
            ++(cblock->weak_count);
        }
        else
        {
            this->ptr = obj.ptr;	// nullptr
            cblock = obj.cblock;	// nullptr
        }
        return *this;
    }

    weak_ptr& operator=(const shared_ptr<T>&& obj) noexcept
    {
        if (obj.cblock)
        {
            this->ptr = std::move(obj.ptr);
            cblock = std::move(obj.cblock);
            ++(cblock->weak_count);
            --(cblock->shared_count);
        }
        return *this;
    }

    weak_ptr& operator=(const weak_ptr<T>&& obj) noexcept
    {
        this->ptr = std::move(obj.ptr);
        cblock = std::move(obj.cblock);
        return *this;
    }

    bool expired() const noexcept
    {
        if (!cblock) return true;
        return !cblock->shared_count;
    }

    shared_ptr<T> lock() const noexcept
    {
        if (!expired())
        {
            cblock->shared_count++;
            return *this;
        }
        return shared_ptr<T>(nullptr);
    }

    long use_count() const noexcept
    {
        if (!cblock) return 0;
        return cblock->shared_count;
    }

    void reset() noexcept
    {
        this->~weak_ptr();
    }

    void swap(weak_ptr& wp) noexcept
    {
        //std::swap(*this, wp);
        weak_ptr<T> tmp = std::move(wp);
        wp = std::move(*this);
        *this = std::move(tmp);
        tmp.cblock->weak_count++;	// so as not to -- weak_count(it's no need)
    }

    friend class shared_ptr<T>;
};

template <class T>
class weak_ptr<T[]>
{
private:
    ControlBlock* cblock;
    T* ptr;
public:
    weak_ptr()
    {
        this->ptr = nullptr;
        cblock = nullptr;
    }

    weak_ptr(const shared_ptr<T[]>& obj)
    {
        if (obj.cblock)
        {
            this->ptr = obj.ptr;
            cblock = obj.cblock;
            ++(cblock->weak_count);
        }
    }

    weak_ptr(const weak_ptr<T[]>& obj)
    {
        if (obj.cblock)
        {
            this->ptr = obj.ptr;
            cblock = obj.cblock;
            ++(cblock->weak_count);
        }
        else
        {
            this->ptr = obj.ptr;	// nullptr
            cblock = obj.cblock;	// nullptr
        }
    }
    weak_ptr(const shared_ptr<T[]>&& obj)
    {
        if (obj.cblock)
        {
            this->ptr = std::move(obj.ptr);
            cblock = std::move(obj.cblock);
            ++(cblock->weak_count);
            --(cblock->shared_count);
        }
    }

    weak_ptr(const weak_ptr<T[]>&& obj) noexcept
    {
        this->ptr = std::move(obj.ptr);
        cblock = std::move(obj.cblock);
    }

    ~weak_ptr()
    {
        if (cblock)
        {
            if (cblock->weak_count > 0)
            {
                --(cblock->weak_count);
                if (cblock->shared_count == 0 && cblock->weak_count == 0)
                {
                    delete cblock;
                }
            }
        }
        cblock = nullptr;
        ptr = nullptr;
    }

    weak_ptr& operator=(const shared_ptr<T[]>& obj) noexcept
    {
        if (obj.cblock)
        {
            this->ptr = obj.ptr;
            cblock = obj.cblock;
            ++(cblock->weak_count);
        }
        return *this;
    }

    weak_ptr& operator=(const weak_ptr<T[]>& obj) noexcept
    {
        if (obj.cblock)
        {
            this->ptr = obj.ptr;
            cblock = obj.cblock;
            ++(cblock->weak_count);
        }
        else
        {
            this->ptr = obj.ptr;	// nullptr
            cblock = obj.cblock;	// nullptr
        }
        return *this;
    }

    weak_ptr& operator=(const shared_ptr<T[]>&& obj) noexcept
    {
        if (obj.cblock)
        {
            this->ptr = std::move(obj.ptr);
            cblock = std::move(obj.cblock);
            ++(cblock->weak_count);
            --(cblock->shared_count);
        }
        return *this;
    }

    weak_ptr& operator=(const weak_ptr<T[]>&& obj) noexcept
    {
        this->ptr = std::move(obj.ptr);
        cblock = std::move(obj.cblock);
        return *this;
    }

    bool expired() const noexcept
    {
        if (!cblock) return true;
        return !cblock->shared_count;
    }

    shared_ptr<T[]> lock() const noexcept
    {
        if (!expired())
        {
            cblock->shared_count++;
            return *this;
        }
        return shared_ptr<T[]>(nullptr);
    }

    long use_count() const noexcept
    {
        if (!cblock) return 0;
        return cblock->shared_count;
    }

    void reset() noexcept
    {
        this->~weak_ptr();
    }

    void swap(weak_ptr& wp) noexcept
    {
        //std::swap(*this, wp);
        weak_ptr<T[]> tmp = std::move(wp);
        wp = std::move(*this);
        *this = std::move(tmp);
        tmp.cblock->weak_count++;	// so as not to -- weak_count(it's no need)
    }

    friend class shared_ptr<T[]>;
};

#endif // SMARTP_H
