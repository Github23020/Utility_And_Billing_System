#pragma once
#include "DoublyLinkedList.h"
template <typename T>
class Stack
{
private:
    LinkedList<T> list;

public:
    bool isEmpty() const
    {
        return list.isEmpty();
    }
    int getSize() const
    {
        return list.getSize();
    }
    void push(T data)
    {
        list.InsertAtEnd(data);
    }
    T pop()
    {
        if (isEmpty())
        {
            return T();
        }
        T value = list.getTail()->getData();
        list.deleteFromEnd();
        return value;
    }
    T top()
    {
        if (isEmpty())
        {
            return T();
        }
        return list.getTail()->getData();
    }
    T peek() const
    {
        return top();
    }
    void printStack() const
    {
        list.printList();
    }

    // Export internal list (copy) for serialization or inspection
    LinkedList<T> toLinkedList() const
    {
        return list;
    }
};
