#ifndef SIMPLEVECTOR_H
#define SIMPLEVECTOR_H

#include <string>

template <class T> class SimpleVector {
private:

    typedef T * iterator;
    T* data;
    unsigned int _capacity;
    unsigned int _size;
    std::allocator<T> allocator;
    void grow() {
        _capacity *= 2;
        T* newArr = allocator.allocate(_capacity);
        for (unsigned int i = 0; i < _size; i++)
            allocator.construct(newArr + i, data[i]);
        allocator.deallocate(data, _capacity / 2);
        data = newArr;
    }
public:
    SimpleVector(const SimpleVector<T> & v)
    {
        _size = v._size;
        _capacity = v._capacity;
        data = allocator.allocate(_capacity);
        for (unsigned int i = 0; i < _size; i++)
            allocator.construct(data + i, v.data[i]);
    }
    explicit SimpleVector(unsigned int initCapacity=2) {
        _capacity = initCapacity;
        _size = 0;
        data = allocator.allocate(_capacity);
    }

    bool operator == (SimpleVector<T>& another) {
        if (_size != another._size) return false;
        for (int i = 0; i < _size; i++) {
            if (data[i] != another.data[i]) {
                return false;
            }
        }
        return true;
    }

    ~SimpleVector() {
        allocator.deallocate(data, _capacity);
    }
    void push(T e) {
        if (_size == _capacity) grow();
        data[_size++] = e;
    }

    template<typename... Args>
    void emplace_back(Args... args) {
        if (_size == _capacity) grow();
        allocator.construct(data + _size, args...);
        _size++;
    }

    void reserve(unsigned int capacity) {
        T* newArr = allocator.allocate(capacity);
        for (unsigned int i = 0; i < std::max(capacity, _size); i++) {
            allocator.construct(newArr + i, data[i]);
        }
        allocator.deallocate(data, _capacity);
        _capacity = capacity;
        data = newArr;
    }

    T& at(unsigned int index) {
        return data[index];
    }

    unsigned int size() {
        return _size;
    }

    unsigned int capacity() {
        return _capacity;
    }

    T pop_back() {
        T e = data[--_size];
        return e;
    }

    iterator begin() {
        return data;
    }

    iterator end() {
        return data + _size;
    }
};
#endif // SIMPLEVECTOR_H
