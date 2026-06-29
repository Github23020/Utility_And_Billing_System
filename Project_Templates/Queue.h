#pragma once
#include "DoublyLinkedList.h"
#include "MyArray.h"

template <typename T>

class Queue
{
private:
    LinkedList<T> list;

public:
    // Add the element to the rear
    void enqueue(T data)
    {
        list.InsertAtEnd(data);
    }
    // remove and return the element from front
    T dequeue()
    {
        if (isEmpty())
        {
            throw underflow_error("Error : Queue is Empty !");
        }
        T data = list.getHead()->getData();
        list.deleteFromStart();
        return data;
    }
    // See front element without removing it
    T peek() const
    {
        if (isEmpty())
        {
            throw underflow_error("Error : Queue is Empty !");
        }
        return list.getHead()->getData();
    }
    // Check size of Queue
    bool isEmpty() const
    {
        return list.isEmpty();
    }
    // Get the current size of the queue
    int getSize() const
    {
        return list.getSize();
    }

    //  Print the queue
    void printQueue() const
    {
        list.printList();
    }

    // Export internal list (copy) for serialization
    LinkedList<T> toLinkedList() const
    {
        return list;
    }
    
    // Added for transport-system compatibility
    MyArray<T> getAllElements() const
    {
        MyArray<T> result;
        Node<T>* current = list.getHead();
        while (current != nullptr)
        {
            result.push_back(current->getData());
            current = current->getNext();
        }
        return result;
    }
};
