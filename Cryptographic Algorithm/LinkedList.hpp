#pragma once
#include <iostream>
#include <string>
#include <cctype>

class Node
{
public:
    char letter;
    int quantity;
    Node *prox;

    Node(char letter) : letter(letter), quantity(1), prox(nullptr) {}
    ~Node() {}
};

class LinkedList
{
public:
    Node *root;

    LinkedList() : root(nullptr) {}
    ~LinkedList()
    {
        Node *current = root;
        while (current)
        {
            Node *next = current->prox;
            delete current;
            current = next;
        }
    }
    Node *createNode(char letter)
    {
        Node *newNode = new Node(letter);
        newNode->prox = nullptr;
        return newNode;
    }
    void insertNode(char letter)
    {
        if (!std::isalpha(letter))
            return;

        if (root == nullptr)
        {
            root = createNode(letter);
            return;
        }

        Node *temp = root;
        Node *last = nullptr;

        while (temp != nullptr)
        {
            if (temp->letter == letter)
            {
                temp->quantity++;
                return;
            }
            last = temp;
            temp = temp->prox;
        }

        last->prox = createNode(letter);
    }
    void findLetter(char &mostUsedLetter)
    {

        mostUsedLetter = '\0';
        int mostUsedCount = -1;

        Node *temp = root;
        while (temp)
        {
            if (temp->quantity > mostUsedCount)
            {
                mostUsedCount = temp->quantity;
                mostUsedLetter = temp->letter;
            }
            temp = temp->prox;
        }
    }
};
