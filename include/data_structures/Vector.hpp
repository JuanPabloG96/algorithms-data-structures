#pragma once

#include <cstddef>

template <typename T> class Vector
{
private:
    T m_data;
    size_t m_size;
    size_t m_capacity;

public:
    Vector() {}

    Vector(size_t initial_capacity) : m_capacity(initial_capacity) {}

    ~Vector() { clear(); }

    Vector(const Vector& other) {}

    Vector& operator=(const Vector& other) {}

    Vector(Vector&& other) {}

    Vector& operator=(Vector&& other) {}

    size_t size() const { return this->m_size; }

    size_t capacity() const { return this->capacity(); }

    bool isEmpty() const { return m_size == 0; }

    void reserve(size_t new_capacity) {}

    void push_back(const T& valor) {}

    void push_back(T&& valor) {}

    void pop_back() {}

    void clear() {}

    T& operator[](size_t indice) {}

    const T& operator[](size_t indice) const {}

    T& at(size_t indice) {}
};
