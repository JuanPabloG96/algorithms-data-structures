#pragma once

#include <iostream>

template <typename T> struct Node
{
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node() : next(nullptr), prev(nullptr) {}

    Node(const T& value) : next(nullptr), prev(nullptr), data(value) {}
};

template <typename T> class DoublyLinkedList
{
private:
    Node<T>* head;
    Node<T>* tail;
    int listSize;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), listSize(0) {}

    ~DoublyLinkedList()
    {
        while (head)
        {
            removeBack();
        }
    }

    DoublyLinkedList(const DoublyLinkedList& other)
        : head(nullptr), tail(nullptr), listSize(0)
    {
        Node<T>* current = other.head;

        while (current)
        {
            pushBack(current->data);
            current = current->next;
        }
    }

    DoublyLinkedList<T>& operator=(const DoublyLinkedList& other)
    {
        if (this == &other)
            return *this;

        clear();

        Node<T>* current = other.head;
        while (current)
        {
            pushBack(current->data);
            current = current->next;
        }

        return *this;
    }

    DoublyLinkedList(DoublyLinkedList&& other)
        : head(other.head), tail(other.tail), listSize(other.listSize)
    {
        other.head = nullptr;
        other.tail = nullptr;
        other.listSize = 0;
    }

    DoublyLinkedList<T>& operator=(DoublyLinkedList&& other)
    {
        if (this == &other)
            return *this;

        clear();

        head = other.head;
        tail = other.tail;
        listSize = other.listSize;

        other.head = nullptr;
        other.tail = nullptr;
        other.listSize = 0;

        return *this;
    }

    void clear()
    {
        while (head)
        {
            removeFront();
        }
    }

    void pushBack(const T& value)
    {
        Node<T>* newNode = new Node<T>(value);

        if (!head)
        {
            head = newNode;
            tail = head;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        listSize++;
    }

    void pushFront(const T& value)
    {
        Node<T>* newNode = new Node<T>(value);

        if (!head)
        {
            head = newNode;
            tail = head;
        }
        else
        {
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
        }
        listSize++;
    }

    void removeBack()
    {
        if (!head)
            return;

        if (head == tail)
        {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            Node<T>* temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete temp;
        }
        listSize--;
    }

    void removeFront()
    {
        if (!head)
            return;

        if (head == tail)
        {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            Node<T>* temp = head;
            head = head->next;
            head->prev = nullptr;
            delete temp;
        }
        listSize--;
    }

    void print()
    {
        Node<T>* current = head;

        while (current)
        {
            std::cout << current->data << " ";
            current = current->next;
        }

        std::cout << std::endl;
    }
};
