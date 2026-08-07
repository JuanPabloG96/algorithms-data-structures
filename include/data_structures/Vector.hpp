#pragma once

#include <algorithm>
#include <cstddef>
#include <new>

template <typename T> class Vector
{
private:
    T* data;
    size_t capacity;
    size_t size;

    void clear()
    {
        for (size_t i = 0; i < size; i++)
        {
            data[i].~T();
        }
        ::operator delete(data);
        reset();
    }

    void reset()
    {
        data = nullptr;
        size = 0;
        capacity = 0;
    }

public:
    Vector() : capacity(2), size(0)
    {
        data = static_cast<T*>(::operator new(capacity * sizeof(T)));
    }

    explicit Vector(size_t initial_capacity)
        : capacity(initial_capacity), size(initial_capacity)
    {
        data = static_cast<T*>(::operator new(capacity * sizeof(T)));

        for (size_t i = 0; i < size; i++)
        {
            new (&data[i]) T();
        }
    }

    Vector(const Vector& other) : capacity(other.capacity), size(other.size)
    {
        data = static_cast<T*>(::operator new(capacity * sizeof(T)));

        for (size_t i = 0; i < other.size; i++)
        {
            new (&data[i]) T(other[i]);
        }
    }

    Vector& operator=(const Vector& other)
    {
        if (this == &other)
            return *this;

        clear();

        this->capacity = other.capacity;
        this->size = other.size;

        data = static_cast<T*>(::operator new(capacity * sizeof(T)));

        for (size_t i = 0; i < other.size; i++)
        {
            new (&data[i]) T(other[i]);
        }

        return *this;
    }

    Vector(Vector&& other) noexcept
        : capacity(other.capacity), size(other.size), data(other.data)
    {
        other.reset();
    }

    Vector& operator=(Vector&& other) noexcept
    {
        if (this == &other)
            return *this;

        clear();

        data = other.data;
        capacity = other.capacity;
        size = other.size;

        other.reset();

        return *this;
    }

    ~Vector() { clear(); }

    T& operator[](size_t index) { return data[index]; }

    const T& operator[](size_t index) const { return data[index]; }

    void pushBack(T&& element)
    {
        new (&data[size]) T(std::move(element));
        size++;
    }

    size_t getCapacity() const { return capacity; }

    size_t getSize() const { return size; }
};
