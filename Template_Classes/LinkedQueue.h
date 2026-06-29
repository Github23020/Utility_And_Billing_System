#ifndef INC_2025_FALL_ITULAHORE_DSA_SE200T_PROJECT_2025_FALL_GROUP_J_QUEUE_H
#define INC_2025_FALL_ITULAHORE_DSA_SE200T_PROJECT_2025_FALL_GROUP_J_QUEUE_H

#include <iostream>
#include "Node.h"
using namespace std;

template <typename T>
class LinkedQUEUE
{
private:
    Node<T> *front;
    Node<T> *rear;
    int size;

public:
    LinkedQUEUE();
    ~LinkedQUEUE();

    bool isEmpty() const;
    void enqueue(T data);
    T dequeue();
    T peek() const;
    int getSize() const;
    void clear();
    void printQueue() const;
};

template <typename T>
LinkedQUEUE<T>::LinkedQUEUE() : front(nullptr), rear(nullptr), size(0) {}

template <typename T>
LinkedQUEUE<T>::~LinkedQUEUE()
{
    clear();
}

template <typename T>
bool LinkedQUEUE<T>::isEmpty() const
{
    return size == 0;
}

template <typename T>
void LinkedQUEUE<T>::enqueue(T data)
{
    Node<T> *n = new Node<T>(data);
    if (isEmpty())
    {
        front = rear = n;
    }
    else
    {
        // Use setter/getter API instead of direct 'prev' member
        rear->setNext(n);
        n->setPrevious(rear);
        rear = n;
    }
    size++;
}

template <typename T>
T LinkedQUEUE<T>::dequeue()
{
    if (isEmpty())
        throw "Queue empty";

    Node<T> *temp = front;
    T val = temp->getData(); // use accessor

    front = front->getNext();
    if (!front)
        rear = nullptr;
    else
        front->setPrevious(nullptr);

    delete temp;
    size--;
    return val;
}

template <typename T>
T LinkedQUEUE<T>::peek() const
{
    if (isEmpty())
        throw "Queue empty";
    return front->getData();
}

template <typename T>
int LinkedQUEUE<T>::getSize() const
{
    return size;
}

template <typename T>
void LinkedQUEUE<T>::clear()
{
    while (!isEmpty())
        dequeue();
}

template <typename T>
void LinkedQUEUE<T>::printQueue() const
{
    Node<T> *cur = front;
    cout << "Queue: ";
    while (cur)
    {
        cout << cur->getData() << " ";
        cur = cur->getNext();
    }
    cout << endl;
}

#endif