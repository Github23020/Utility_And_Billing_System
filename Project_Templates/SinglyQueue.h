#pragma once

#include <iostream>
using namespace std;

template <typename T>
class QueueNode
{
    // Data Members:
    T data;             // The data stored in the node.
    QueueNode<T> *next; // Pointer to the next node in the list.

    // Member Functions to Implement:
public:
    QueueNode()
    {
        this->data = T{};
        this->next = nullptr;
    } // Initializes the node with a given data value and next = nullptr.
    ~QueueNode()
    {

    } // set the next to nullptr
    void setNext(QueueNode<T> *val)
    {
        next = val;
    } // Sets the next pointer to the provided node.
    QueueNode<T> *getNext()
    {
        return next;
    } // Returns the next node pointer.
    void setData(T data)
    {
        this->data = data;
    } // Sets the data of the node.
    T getData()
    {
        return data;
    } // Returns the data of the node.
};

template <typename T>
class LinkedQueue
{
    // Data Members:
    QueueNode<T> *front; // Pointer to the first node (front of the queue).
    QueueNode<T> *rear;  // Pointer to the last node (rear of the queue).
    int size;            // Stores the number of elements currently in the queue.

    // Member Functions to Implement:
public:
    LinkedQueue()
    {
        front = rear = nullptr;
        size = 0;
    } // Initializes front = nullptr, rear = nullptr, and size = 0.
    ~LinkedQueue()
    {
        clear();
    } // Deallocates all nodes in the queue to prevent memory leaks.
    bool isEmpty()
    {
        return (size == 0 ? true : false);
    } // Returns true if the queue is empty; otherwise, false.
    void enqueue(T data)
    {
        QueueNode<T> *newNode = new QueueNode<T>();
        newNode->setData(data);
        if (front == nullptr)
        {
            front = rear = newNode;
            size++;
            return;
        }
        else
        {
            rear->setNext(newNode);
            rear = newNode;
            // T val = rear->getData();
            rear->setNext(nullptr);
            size++;
            // cout << val << " is ADDED!" << endl;
            return;
        }
    } // Creates a new node and adds it to the rear of the queue.
    T dequeue()
    {
        QueueNode<T> *toDelete = front;
        if (front == nullptr)
        {
            cout << "Linked Queue is Empty" << endl;
            return T();
        }
        else if (size == 1)
        {
            front = rear = nullptr;
            T top = toDelete->getData();
            delete toDelete;
            size--;
            // cout << "Front Element (" << top << ") is removed!" << endl;
            return top;
        }
        else
        {
            T top = front->getData();
            front = front->getNext();
            toDelete->setNext(nullptr);
            delete toDelete;
            size--;
            // cout << "Front Element (" << top << ") is removed!" << endl;
            return top;
        }
    } // Removes and returns the element from the front of the queue. If the queue is empty, print a message and return -1.
    T peek()
    {
        if (front == nullptr)
        {
            cout << "Linked Queue is Empty" << endl;
            return T();
        }

        T top = front->getData();
        // cout << "Front Element is " << top << endl;
        return top;
    } // Returns the front element without removing it. If the queue is empty, print a message and return -1.
    int getSize()
    {
        return size;
    } // Returns the number of elements currently in the queue.
    void clear()
    {
        while (!isEmpty())
        {
            dequeue();
        }
    } // Removes all nodes and resets the queue.
    QueueNode<T> *getFront()
    {
        return front;
    }
    void printQueue()
    {
        QueueNode<T> *node = front;
        while (node != nullptr)
        {
            cout << node->getData() << endl;
            node = node->getNext();
        }
        cout << endl;
    } // Displays the queue’s contents from front to rear in order.
};