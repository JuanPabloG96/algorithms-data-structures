#pragma once

#include <iostream>

template <typename T> struct Node
{
    T data;
    Node<T>* next;

    Node() : next(nullptr) {}

    Node(const T& value) : data(value), next(nullptr) {}
};

template <typename T> class LinkedList
{
private:
    Node<T>* head;
    Node<T>* tail;
    size_t list_size;

    Node<T>* getNodeAt(size_t index)
    {
        if (index >= list_size)
        {
            std::cerr << "Error: index out of range." << std::endl;
            return nullptr;
        }

        Node<T>* current = head;

        for (size_t i = 0; i < index; i++)
        {
            current = current->next;
        }

        return current;
    }

    void removeNode(Node<T>* node)
    {
        if (!node)
            return;

        if (node == head)
        {
            removeFront();
            return;
        }

        if (node == tail)
        {
            removeBack();
            return;
        }

        Node<T>* current = head;

        while (current->next != node)
        {
            current = current->next;
        }

        Node<T>* temp = current->next;
        current->next = temp->next;
        delete temp;
        list_size--;
    }

public:
    LinkedList() : head(nullptr), tail(nullptr), list_size(0) {}

    ~LinkedList() { clear(); }

    LinkedList(const LinkedList& other)
        : head(nullptr), tail(nullptr), list_size(0)
    {
        Node<T>* current = other.head;

        while (current)
        {
            pushBack(current->data);
            current = current->next;
        }
    }

    LinkedList<T>& operator=(const LinkedList& other)
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

    LinkedList(LinkedList&& other)
        : head(other.head), tail(other.tail), list_size(other.list_size)
    {
        other.head = nullptr;
        other.tail = nullptr;
        other.list_size = 0;
    }

    LinkedList<T>& operator=(LinkedList&& other)
    {
        if (this == &other)
            return *this;

        clear();

        head = other.head;
        tail = other.tail;
        list_size = other.list_size;

        other.head = nullptr;
        other.tail = nullptr;
        other.list_size = 0;

        return *this;
    }

    // Insert methods
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
            tail = newNode;
        }
        list_size++;
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
            newNode->next = head;
            head = newNode;
        }
        list_size++;
    }

    void insert(size_t index, const T& value)
    {
        if (index > list_size)
        {
            std::cerr << "Error index out of range." << std::endl;
            return;
        }
        if (index == 0)
        {
            pushFront(value);
            return;
        }
        if (index == list_size)
        {
            pushBack(value);
            return;
        }

        Node<T>* current = getNodeAt(index - 1);
        Node<T>* newNode = new Node<T>(value);

        newNode->next = current->next;
        current->next = newNode;

        list_size++;
    }

    // Remove methods
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
            tail = getNodeAt(list_size - 2);
            tail->next = nullptr;
            delete temp;
        }
        list_size--;
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
            delete temp;
        }
        list_size--;
    }

    bool remove(const T& value)
    {
        Node<T>* node = find(value);

        if (!node)
            return false;

        removeNode(node);
        return true;
    }

    bool erase(size_t index)
    {
        Node<T>* node = getNodeAt(index);

        if (!node)
            return false;

        removeNode(node);
        return true;
    }

    // Search methods
    Node<T>* find(const T& value) const
    {
        Node<T>* current = head;

        while (current)
        {
            if (current->data == value)
                return current;

            current = current->next;
        }
        return nullptr;
    }

    bool contains(const T& value) const { return find(value) != nullptr; }

    // Utilities
    void clear()
    {
        while (head)
        {
            removeFront();
        }
    }

    bool empty() const { return list_size == 0; }

    size_t size() const { return this->list_size; }

    void print() const
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
