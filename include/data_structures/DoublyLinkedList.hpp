#pragma once

#include <iostream>

template <typename T> struct Node
{
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node() : next(nullptr), prev(nullptr) {}

    Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
};

template <typename T> class DoublyLinkedList
{
private:
    Node<T>* head;
    Node<T>* tail;
    size_t list_size;

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

        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
        list_size--;
    }

    Node<T>* getNodeAt(size_t index) const
    {
        if (index >= list_size)
        {
            std::cerr << "Error: index out of range." << std::endl;
            return nullptr;
        }

        Node<T>* current;

        if (index < list_size / 2)
        {
            current = head;
            for (size_t i = 0; i < index; i++)
            {
                current = current->next;
            }
        }
        else
        {
            current = tail;
            for (size_t i = list_size - 1; i > index; i--)
            {
                current = current->prev;
            }
        }

        return current;
    }

public:
    // constructors rule of 5
    DoublyLinkedList() : head(nullptr), tail(nullptr), list_size(0) {}

    ~DoublyLinkedList() { clear(); }

    DoublyLinkedList(const DoublyLinkedList& other)
        : head(nullptr), tail(nullptr), list_size(0)
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
        : head(other.head), tail(other.tail), list_size(other.list_size)
    {
        other.head = nullptr;
        other.tail = nullptr;
        other.list_size = 0;
    }

    DoublyLinkedList<T>& operator=(DoublyLinkedList&& other)
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

    // insert methods
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
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
        }
        list_size++;
    }

    void insert(size_t index, const T& value)
    {
        if (index > list_size)
        {
            std::cerr << "Error: index is out of range." << std::endl;
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

        Node<T>* current = getNodeAt(index);

        Node<T>* newNode = new Node<T>(value);

        newNode->prev = current->prev;
        newNode->next = current;

        current->prev->next = newNode;
        current->prev = newNode;
        list_size++;
    }

    // remove methods
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
            head->prev = nullptr;
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

    // search methods
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

    // utilities
    void clear()
    {
        while (head)
        {
            removeFront();
        }
    }

    bool empty() const { return list_size == 0; }

    size_t size() const { return list_size; }

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

    void printReverse() const
    {
        Node<T>* current = tail;

        while (current)
        {
            std::cout << current->data << " ";
            current = current->prev;
        }

        std::cout << std::endl;
    }
};
