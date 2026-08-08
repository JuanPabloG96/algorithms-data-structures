#pragma once

#include <algorithm>
#include <cstddef>
#include <new>
#include <stdexcept>

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

    void reallocate(size_t new_capacity)
    {
        T* new_data = static_cast<T*>(::operator new(new_capacity * sizeof(T)));

        for (size_t i = 0; i < size; i++)
        {
            new (&new_data[i]) T(std::move(data[i]));
            data[i].~T();
        }

        ::operator delete(data);

        data = new_data;
        capacity = new_capacity;
    }

    void fillEmptySpaces()
    {
        for (size_t i = size; i < capacity; i++)
        {
            new (&data[i]) T();
        }
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

    void pushBack(const T& element)
    {
        if (size == capacity)
        {
            size_t new_capacity = (capacity == 0) ? 2 : capacity * 2;
            reallocate(new_capacity);
        }

        new (&data[size]) T(element);
        size++;
    }

    void pushBack(T&& element)
    {
        if (size == capacity)
        {
            size_t new_capacity = (capacity == 0) ? 2 : capacity * 2;
            reallocate(new_capacity);
        }

        new (&data[size]) T(std::move(element));
        size++;
    }

    void popBack()
    {
        if (size <= 0)
            return;

        size--;
        data[size].~T();
    }

    void reserve(size_t new_capacity)
    {
        if (new_capacity > capacity)
        {
            reallocate(new_capacity);
        }
    }

    void resize(size_t new_size)
    {
        if (new_size == size)
            return;

        if (new_size > size)
        {
            if (new_size > capacity)
                reallocate(new_size);
            fillEmptySpaces();
        }

        if (new_size < size)
        {
            for (size_t i = new_size; i < size; i++)
            {
                data[i].~T();
            }
        }

        size = new_size;
    }

    void shrinkToFit() {}

    T& front() { return data[0]; }

    T& back() { return data[size - 1]; }

    const T& front() const { return data[0]; }

    const T& back() const { return data[size - 1]; }

    bool empty() { return size == 0; }

    T& at(size_t index)
    {
        if (index >= size)
        {
            throw std::out_of_range("Vector::at - index out of range");
        }
        return data[index];
    }

    const T& at(size_t index) const
    {
        if (index >= size)
        {
            throw std::out_of_range("Vector::at - index out of range");
        }
        return data[index];
    }

    const T* Data() const { return data; }

    size_t Capacity() const { return capacity; }

    size_t Size() const { return size; }

    T* begin() { return data; }

    T* end() { return data + size; }

    const T* begin() const { return data; }

    const T* end() const { return data + size; }
};
