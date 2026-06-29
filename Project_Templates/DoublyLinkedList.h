#pragma once
#include "Node.h"
#include <iostream>
using namespace std;

// Forward declaration for the friend function
template <typename T>
class LinkedList;

// Forward declaration of the friend operator<<
template <typename T>
ostream &operator<<(ostream &out, const LinkedList<T> &list);

// ==================== DOUBLY LINKED LIST CLASS ====================
template <typename T>
class LinkedList
{
private:
    Node<T> *head;
    Node<T> *tail;
    int size;

public:
    // Constructors and Destructor
    LinkedList();
    LinkedList(const LinkedList<T> &other);
    ~LinkedList();

    // Assignment Operator
    LinkedList<T> &operator=(const LinkedList<T> &other);

    // Basic Operations
    bool isEmpty() const;
    int getSize() const;
    Node<T> *getHead() const;
    Node<T> *getTail() const;
    void clear();

    // Insertion Operations
    void append(T data);
    void prepend(T data);
    void insertAtIndex(T data, int index);
    void InsertAtEnd(T data);
    void InsertAtBeginning(T data);

    // Deletion Operations
    void deleteFromEnd();
    void deleteFromStart();
    void deleteFromIndex(int index);
    bool deleteByValue(T data);

    // Search Operations
    Node<T> *search(T data);
    Node<T> *searchById(int id);
    bool contains(const T &value) const;

    // Access and Update Operations
    T getDataAtIndex(int index) const;
    T &getAt(int index);
    const T &getAt(int index) const;
    void updateAt(int index, const T &value);

    // Sorting and Manipulation
    void swapValues(int i, int j);
    void bubbleSort();
    void selectionSort();
    void insertionSort();

    // Display Operations - REMOVED cout << temp->getData() calls
    void printList() const;
    void printLIST();

    // Utility Operations
    void reverse();
    void removeDuplicates();

    // Operator Overloading
    // Fixed: Added template parameter to friend declaration
    friend ostream &operator<< <T>(ostream &out, const LinkedList<T> &list);
    bool operator==(const LinkedList<T> &other) const;
    LinkedList<T> operator+(const LinkedList<T> &other) const;
};

// =============================================================
//               DOUBLY LINKED LIST IMPLEMENTATION
// =============================================================

// ========== CONSTRUCTORS AND DESTRUCTOR ==========

template <typename T>
LinkedList<T>::LinkedList()
{
    head = tail = nullptr;
    size = 0;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &other)
{
    head = tail = nullptr;
    size = 0;

    Node<T> *current = other.getHead();
    while (current != nullptr)
    {
        InsertAtEnd(current->getData());
        current = current->getNext();
    }
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    clear();
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &other)
{
    if (this == &other)
    {
        return *this;
    }

    clear();

    Node<T> *current = other.getHead();
    while (current != nullptr)
    {
        InsertAtEnd(current->getData());
        current = current->getNext();
    }

    return *this;
}

// ========== BASIC OPERATIONS ==========

template <typename T>
bool LinkedList<T>::isEmpty() const
{
    return size == 0;
}

template <typename T>
int LinkedList<T>::getSize() const
{
    return size;
}

template <typename T>
Node<T> *LinkedList<T>::getHead() const
{
    return head;
}

template <typename T>
Node<T> *LinkedList<T>::getTail() const
{
    return tail;
}

template <typename T>
void LinkedList<T>::clear()
{
    Node<T> *current = head;
    while (current != nullptr)
    {
        Node<T> *next = current->getNext();
        delete current;
        current = next;
    }
    head = tail = nullptr;
    size = 0;
}

// ========== INSERTION OPERATIONS ==========

template <typename T>
void LinkedList<T>::append(T data)
{
    Node<T> *newNode = new Node<T>(data);

    if (isEmpty())
    {
        head = tail = newNode;
    }
    else
    {
        newNode->setPrevious(tail);
        tail->setNext(newNode);
        tail = newNode;
    }
    size++;
}

template <typename T>
void LinkedList<T>::prepend(T data)
{
    Node<T> *newNode = new Node<T>(data);

    if (isEmpty())
    {
        head = tail = newNode;
    }
    else
    {
        newNode->setNext(head);
        head->setPrevious(newNode);
        head = newNode;
    }
    size++;
}

template <typename T>
void LinkedList<T>::insertAtIndex(T data, int index)
{
    if (index < 0 || index > size)
    {
        cout << "Invalid Index!" << endl;
        return;
    }

    if (index == 0)
    {
        prepend(data);
        return;
    }

    if (index == size)
    {
        append(data);
        return;
    }

    Node<T> *temp = head;
    for (int i = 0; i < index - 1; i++)
        temp = temp->getNext();

    Node<T> *newNode = new Node<T>(data);

    newNode->setNext(temp->getNext());
    newNode->setPrevious(temp);

    temp->setNext(newNode);
    newNode->getNext()->setPrevious(newNode);

    size++;
}

template <typename T>
void LinkedList<T>::InsertAtEnd(T data)
{
    append(data);
}

template <typename T>
void LinkedList<T>::InsertAtBeginning(T data)
{
    prepend(data);
}

// ========== DELETION OPERATIONS ==========

template <typename T>
void LinkedList<T>::deleteFromEnd()
{
    if (isEmpty())
    {
        return;
    }

    if (head == tail)
    {
        delete head;
        head = tail = nullptr;
    }
    else
    {
        Node<T> *temp = tail;
        tail = tail->getPrevious();
        tail->setNext(nullptr);
        delete temp;
    }
    size--;
}

template <typename T>
void LinkedList<T>::deleteFromStart()
{
    if (isEmpty())
    {
        return;
    }

    if (head == tail)
    {
        delete head;
        head = tail = nullptr;
    }
    else
    {
        Node<T> *temp = head;
        head = head->getNext();
        head->setPrevious(nullptr);
        delete temp;
    }
    size--;
}

template <typename T>
void LinkedList<T>::deleteFromIndex(int index)
{
    if (index < 0 || index >= size)
    {
        cout << "Invalid Index!" << endl;
        return;
    }

    if (index == 0)
    {
        deleteFromStart();
        return;
    }

    if (index == size - 1)
    {
        deleteFromEnd();
        return;
    }

    Node<T> *temp = head;
    for (int i = 0; i < index - 1; i++)
        temp = temp->getNext();

    Node<T> *target = temp->getNext();

    temp->setNext(target->getNext());
    target->getNext()->setPrevious(temp);

    delete target;
    size--;
}

template <typename T>
bool LinkedList<T>::deleteByValue(T data)
{
    Node<T> *temp = head;
    while (temp != nullptr)
    {
        if (temp->getData() == data)
        {
            if (temp == head)
            {
                deleteFromStart();
            }
            else if (temp == tail)
            {
                deleteFromEnd();
            }
            else
            {
                temp->getPrevious()->setNext(temp->getNext());
                temp->getNext()->setPrevious(temp->getPrevious());
                delete temp;
                size--;
            }
            return true;
        }
        temp = temp->getNext();
    }
    return false;
}

// ========== SEARCH OPERATIONS ==========

template <typename T>
Node<T> *LinkedList<T>::search(T data)
{
    Node<T> *current = head;
    while (current != nullptr)
    {
        if (current->getData() == data)
        {
            return current;
        }
        current = current->getNext();
    }
    return nullptr;
}

template <typename T>
Node<T> *LinkedList<T>::searchById(int id)
{
    Node<T> *current = head;
    while (current != nullptr)
    {
        if (current->getData().getId() == id)
        {
            return current;
        }
        current = current->getNext();
    }
    return nullptr;
}

template <typename T>
bool LinkedList<T>::contains(const T &value) const
{
    Node<T> *temp = head;
    while (temp != nullptr)
    {
        if (temp->getData() == value)
            return true;
        temp = temp->getNext();
    }
    return false;
}

// ========== ACCESS AND UPDATE OPERATIONS ==========

template <typename T>
T LinkedList<T>::getDataAtIndex(int index) const
{
    if (index < 0 || index >= size)
    {
        cout << "Index out of range!" << endl;
        return T();
    }

    Node<T> *temp = head;
    for (int i = 0; i < index; i++)
    {
        temp = temp->getNext();
    }
    return temp->getData();
}

template <typename T>
T &LinkedList<T>::getAt(int index)
{
    if (index < 0 || index >= size)
    {
        throw "Index out of range";
    }

    Node<T> *temp = head;
    for (int i = 0; i < index; i++)
        temp = temp->getNext();

    return temp->getData();
}

template <typename T>
const T &LinkedList<T>::getAt(int index) const
{
    if (index < 0 || index >= size)
    {
        throw "Index out of range";
    }

    Node<T> *temp = head;
    for (int i = 0; i < index; i++)
        temp = temp->getNext();

    return temp->getData();
}

template <typename T>
void LinkedList<T>::updateAt(int index, const T &value)
{
    if (index < 0 || index >= size)
    {
        throw "Index out of range";
    }

    Node<T> *temp = head;
    for (int i = 0; i < index; i++)
        temp = temp->getNext();

    temp->setData(value);
}

// ========== SORTING AND MANIPULATION ==========

template <typename T>
void LinkedList<T>::swapValues(int i, int j)
{
    if (i == j)
    {
        return;
    }

    if (i < 0 || j < 0 || i >= size || j >= size)
    {
        return;
    }

    if (i > j)
    {
        int temp = i;
        i = j;
        j = temp;
    }

    Node<T> *node1 = head;
    for (int a = 0; a < i && node1 != nullptr; a++)
    {
        node1 = node1->getNext();
    }

    Node<T> *node2 = head;
    for (int b = 0; b < j && node2 != nullptr; b++)
    {
        node2 = node2->getNext();
    }

    if (node1 == nullptr || node2 == nullptr)
    {
        return;
    }

    T tempData = node1->getData();
    node1->setData(node2->getData());
    node2->setData(tempData);
}

template <typename T>
void LinkedList<T>::bubbleSort()
{
    if (size < 2)
        return;

    bool swapped = true;
    while (swapped)
    {
        swapped = false;
        Node<T> *current = head;

        while (current != nullptr && current->getNext() != nullptr)
        {
            if (current->getData() > current->getNext()->getData())
            {
                swapped = true;

                T tempData = current->getData();
                current->setData(current->getNext()->getData());
                current->getNext()->setData(tempData);
            }
            current = current->getNext();
        }
    }
}

template <typename T>
void LinkedList<T>::selectionSort()
{
    if (size < 2)
        return;

    Node<T> *current = head;

    while (current != nullptr)
    {
        Node<T> *minNode = current;
        Node<T> *temp = current->getNext();

        while (temp != nullptr)
        {
            if (temp->getData() < minNode->getData())
            {
                minNode = temp;
            }
            temp = temp->getNext();
        }

        if (minNode != current)
        {
            T tempData = current->getData();
            current->setData(minNode->getData());
            minNode->setData(tempData);
        }

        current = current->getNext();
    }
}

template <typename T>
void LinkedList<T>::insertionSort()
{
    if (size < 2)
        return;

    LinkedList<T> sortedList;

    Node<T> *current = head;
    while (current != nullptr)
    {
        Node<T> *nextNode = current->getNext();

        if (sortedList.isEmpty() || current->getData() < sortedList.getHead()->getData())
        {
            sortedList.prepend(current->getData());
        }
        else
        {
            Node<T> *sortedCurrent = sortedList.getHead();
            while (sortedCurrent->getNext() != nullptr &&
                   sortedCurrent->getNext()->getData() < current->getData())
            {
                sortedCurrent = sortedCurrent->getNext();
            }

            Node<T> *newNode = new Node<T>(current->getData());
            newNode->setNext(sortedCurrent->getNext());
            newNode->setPrevious(sortedCurrent);

            if (sortedCurrent->getNext() != nullptr)
            {
                sortedCurrent->getNext()->setPrevious(newNode);
            }
            sortedCurrent->setNext(newNode);

            if (newNode->getNext() == nullptr)
            {
                sortedList.tail = newNode;
            }

            sortedList.size++;
        }

        current = nextNode;
    }

    clear();

    Node<T> *sortedCurrent = sortedList.getHead();
    while (sortedCurrent != nullptr)
    {
        append(sortedCurrent->getData());
        sortedCurrent = sortedCurrent->getNext();
    }
}

// ========== DISPLAY OPERATIONS ==========

template <typename T>
void LinkedList<T>::printList() const
{
    Node<T> *temp = head;
    int count = 1;

    if (temp == nullptr)
    {
        cout << "List is empty!" << endl;
        return;
    }

    while (temp != nullptr)
    {
        cout << "[" << count << "] ";
        cout << temp->getData();
        temp = temp->getNext();
        count++;
    }
    cout << "Total items: " << size << endl;
}

template <typename T>
void LinkedList<T>::printLIST()
{
    Node<T> *temp = head;
    int count = 1;

    cout << "LIST: ";
    while (temp != nullptr)
    {
        cout << "[" << count << "] ";
        cout << temp->getData();
        temp = temp->getNext();
        count++;
    }
    cout << "Total items: " << size << endl;
}

// ========== UTILITY OPERATIONS ==========

template <typename T>
void LinkedList<T>::reverse()
{
    if (size < 2)
        return;

    Node<T> *current = head;
    Node<T> *temp = nullptr;

    tail = head;

    while (current != nullptr)
    {
        temp = current->getPrevious();
        current->setPrevious(current->getNext());
        current->setNext(temp);
        current = current->getPrevious();
    }

    if (temp != nullptr)
    {
        head = temp->getPrevious();
    }
}

template <typename T>
void LinkedList<T>::removeDuplicates()
{
    if (size < 2)
        return;

    Node<T> *current = head;

    while (current != nullptr && current->getNext() != nullptr)
    {
        Node<T> *temp = current->getNext();
        Node<T> *prev = current;

        while (temp != nullptr)
        {
            if (temp->getData() == current->getData())
            {
                prev->setNext(temp->getNext());
                if (temp->getNext() != nullptr)
                {
                    temp->getNext()->setPrevious(prev);
                }
                else
                {
                    tail = prev;
                }

                delete temp;
                size--;
                temp = prev->getNext();
            }
            else
            {
                prev = temp;
                temp = temp->getNext();
            }
        }

        current = current->getNext();
    }
}

// ========== OPERATOR OVERLOADING ==========

// The operator<< function definition
template <typename T>
ostream &operator<<(ostream &out, const LinkedList<T> &list)
{
    Node<T> *temp = list.getHead();
    int count = 1;

    while (temp != nullptr)
    {
        out << "[" << count << "] ";
        out << temp->getData();
        temp = temp->getNext();
        count++;
    }
    out << "Total items: " << list.getSize() << endl;
    return out;
}

template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T> &other) const
{
    if (size != other.size)
        return false;

    Node<T> *current1 = head;
    Node<T> *current2 = other.head;

    while (current1 != nullptr && current2 != nullptr)
    {
        if (current1->getData() != current2->getData())
            return false;
        current1 = current1->getNext();
        current2 = current2->getNext();
    }

    return true;
}

template <typename T>
LinkedList<T> LinkedList<T>::operator+(const LinkedList<T> &other) const
{
    LinkedList<T> result;

    Node<T> *current = head;
    while (current != nullptr)
    {
        result.append(current->getData());
        current = current->getNext();
    }

    current = other.head;
    while (current != nullptr)
    {
        result.append(current->getData());
        current = current->getNext();
    }

    return result;
}