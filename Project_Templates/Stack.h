#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
using namespace std;

template <typename T>
class Stack
{
    T *array;     // Pointer to the dynamic array storing the stack elements.
    int size;     // The current size of the stack.
    int capacity; // The current capacity of stack.

public:
    Stack()
    {
        capacity = 10;
        size = 0;
        array = new T[10];
    } // Initializes the stack with an initial capacity 10, allocates the dynamic array with the initial capacity, sets size to 0.
    ~Stack()
    {
        delete[] array;
    } // Deallocates the dynamic array to prevent memory leaks.
    bool isEmpty()
    {
        if (size == 0)
        {
            return true;
        }
        else
            return false;
    } // Returns true if the stack is empty; otherwise, false.
    void push(T data)
    {
        if (size == capacity)
        {
            capacity *= 2;
            T *temp = new T[capacity];
            for (int i = 0; i < size; i++)
            {
                temp[i] = array[i];
            }
            delete array;
            array = temp;
        }
        array[size] = data; // Top
        size += 1;
    } // If the array is full, resizes it by doubling its capacity. Updates top and size accordingly.
    T pop()
    {
        if (isEmpty())
        {
            cout << "Stack is Empty" << endl;
            return T();
        }
        T top = array[size - 1];
        size--;
        cout << "Top ( " << top << " ) is REMOVED! " << endl;
        return top;
    } // Remove and return the top element of the stack. If the stack is empty, print an error message and return -1.
    T seek()
    {
        if (isEmpty())
        {
            cout << "Stack is Empty" << endl;
            return T();
        }
        T top = array[size - 1];
        cout << "Top element of the stack is " << top << endl;
        return top;
    } // Returns the top element of the stack, don’t remove it from the stack. If the stack is empty, print a message and return -1.
    int getSize()
    {
        return size;
    } // Returns the number of elements in the stack.
    void clear()
    {
        int s = size;
        for (int i = 0; i < s; i++)
        {
            size--;
        }
        cout << "Size of Stack is " << size << endl;
    } // Removes all elements from the stack.
    void printStack()
    {
        cout << "Stack :" << endl;
        for (int i = 0; i < size; i++)
        {
            cout << "=> " << array[i] << endl;
        }
    } // Prints all the elements in the stack from top to bottom.
};

#endif