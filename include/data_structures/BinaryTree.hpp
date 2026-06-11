#pragma once

struct Node
{
    int data;
    Node* left;
    Node* right;
};

class BinaryTree
{
private:
    Node* root;
    void destroy(Node* node);
    Node* clone(Node* node);
    Node* searchNode(int value) const;

public:
    BinaryTree();
    ~BinaryTree();
    BinaryTree(const BinaryTree& other);
    BinaryTree& operator=(const BinaryTree& other);
    BinaryTree(BinaryTree&& other);
    BinaryTree& operator=(BinaryTree&& other);

    void add(int value);
    bool search(int value) const;
    void erase(int value);
    bool isEmpty() const;
    void display() const;
};
