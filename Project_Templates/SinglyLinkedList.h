#pragma once

#include <iostream>
using namespace std;

// ==================== NODE CLASS ====================
template <typename T>
class Node
{
private:
    T data;
    Node<T> *next;

public:
    // Constructors
    Node();
    Node(const T &value);

    // Getters and Setters
    void setNext(Node<T> *val);
    Node<T> *getNext();
    void setData(T data);
    T &getData();
};

// ==================== LINKED LIST CLASS ====================
template <typename T>
class SinglyLinkedList
{
private:
    Node<T> *head;
    Node<T> *tail;
    int count;

    // Private helper methods
    void swapNodes(Node<T> *prev1, Node<T> *curr1, Node<T> *prev2, Node<T> *curr2);
    Node<T> *getNodeAtIndex(int index);

public:
    // Constructors and Destructor
    SinglyLinkedList();
    ~SinglyLinkedList();

    // Copy constructor and assignment operator
    SinglyLinkedList(const SinglyLinkedList<T> &other);
    SinglyLinkedList<T> &operator=(const SinglyLinkedList<T> &other);

    // Basic Operations
    bool isEmpty() const;
    int getSize() const;
    Node<T> *getHead();
    Node<T> *getTail();

    // Insertion Operations
    void prepend(const T &value);
    void append(const T &value);
    void insertAtIndex(int index, const T &value);

    // Deletion Operations
    void deleteFromBeginning();
    void deleteFromEnd();
    void deleteAtIndex(int index);

    // Search and Access Operations
    bool search(T value) const;
    T &getDataAt(int index);
    const T &getDataAt(int index) const;
    void updateAtIndex(int index, T newValue);
    int countOccurrences(T value) const;

    // Added for transport-system compatibility
    void InsertAtEnd(const T &value);  // Alias for append
    void deleteFromIndex(int index);   // Alias for deleteAtIndex
    T getDataAtIndex(int index) const; // Alias for getDataAt

    // Sorting Algorithms
    void bubbleSort();
    void selectionSort();
    void insertionSort();

    // Utility Operations
    void display() const;
    void reverse();
    void removeDuplicates();

    // Operator Overloading
    friend ostream &operator<<(ostream &out, const SinglyLinkedList<T> &list);
    bool operator==(const SinglyLinkedList<T> &other) const;
    SinglyLinkedList<T> operator+(const SinglyLinkedList<T> &other) const;
};

// =============================================================
//                     NODE IMPLEMENTATION
// =============================================================

template <typename T>
Node<T>::Node()
{
    data = T{};
    next = nullptr;
}

template <typename T>
Node<T>::Node(const T &value)
{
    data = value;
    next = nullptr;
}

template <typename T>
void Node<T>::setNext(Node<T> *val)
{
    this->next = val;
}

template <typename T>
Node<T> *Node<T>::getNext()
{
    return next;
}

template <typename T>
void Node<T>::setData(T data)
{
    this->data = data;
}

template <typename T>
T &Node<T>::getData()
{
    return data;
}

// =============================================================
//                   LINKED LIST IMPLEMENTATION
// =============================================================

// ========== PRIVATE HELPER METHODS ==========

template <typename T>
void SinglyLinkedList<T>::swapNodes(Node<T> *prev1, Node<T> *curr1, Node<T> *prev2, Node<T> *curr2)
{
    if (curr1 == curr2)
        return;

    // If nodes are adjacent (curr1 before curr2)
    if (curr1->getNext() == curr2)
    {
        curr1->setNext(curr2->getNext());
        curr2->setNext(curr1);

        if (prev1)
            prev1->setNext(curr2);
        else
            head = curr2;
    }
    // If nodes are adjacent (curr2 before curr1)
    else if (curr2->getNext() == curr1)
    {
        curr2->setNext(curr1->getNext());
        curr1->setNext(curr2);

        if (prev2)
            prev2->setNext(curr1);
        else
            head = curr1;
    }
    else
    {
        Node<T> *temp = curr1->getNext();
        curr1->setNext(curr2->getNext());
        curr2->setNext(temp);

        if (prev1)
            prev1->setNext(curr2);
        else
            head = curr2;

        if (prev2)
            prev2->setNext(curr1);
        else
            head = curr1;
    }

    // Fix tail
    if (curr1->getNext() == nullptr)
        tail = curr1;
    if (curr2->getNext() == nullptr)
        tail = curr2;
}

template <typename T>
Node<T> *SinglyLinkedList<T>::getNodeAtIndex(int index)
{
    if (index < 0 || index >= count)
        return nullptr;

    Node<T> *temp = head;
    for (int i = 0; i < index; i++)
        temp = temp->getNext();
    return temp;
}

// ========== CONSTRUCTORS AND DESTRUCTOR ==========

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList()
{
    head = nullptr;
    tail = nullptr;
    count = 0;
}

template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
    while (!isEmpty())
    {
        deleteFromBeginning();
    }
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T> &other)
{
    head = nullptr;
    tail = nullptr;
    count = 0;

    Node<T> *current = other.head;
    while (current != nullptr)
    {
        append(current->getData());
        current = current->getNext();
    }
}

template <typename T>
SinglyLinkedList<T> &SinglyLinkedList<T>::operator=(const SinglyLinkedList<T> &other)
{
    if (this == &other)
        return *this;

    // Clear current list
    while (!isEmpty())
    {
        deleteFromBeginning();
    }

    // Copy from other list
    Node<T> *current = other.head;
    while (current != nullptr)
    {
        append(current->getData());
        current = current->getNext();
    }

    return *this;
}

// ========== BASIC OPERATIONS ==========

template <typename T>
bool SinglyLinkedList<T>::isEmpty() const
{
    return head == nullptr;
}

template <typename T>
int SinglyLinkedList<T>::getSize() const
{
    return count;
}

template <typename T>
Node<T> *SinglyLinkedList<T>::getHead()
{
    return head;
}

template <typename T>
Node<T> *SinglyLinkedList<T>::getTail()
{
    return tail;
}

// ========== INSERTION OPERATIONS ==========

template <typename T>
void SinglyLinkedList<T>::prepend(const T &value)
{
    Node<T> *newNode = new Node<T>(value);

    if (isEmpty())
    {
        head = tail = newNode;
    }
    else
    {
        newNode->setNext(head);
        head = newNode;
    }
    count++;
}

template <typename T>
void SinglyLinkedList<T>::append(const T &value)
{
    Node<T> *newNode = new Node<T>(value);

    if (isEmpty())
    {
        head = tail = newNode;
    }
    else
    {
        tail->setNext(newNode);
        tail = newNode;
    }
    count++;
}

template <typename T>
void SinglyLinkedList<T>::insertAtIndex(int index, const T &value)
{
    if (index < 0 || index > count)
    {
        cout << "Invalid index! Position should be between 0 and " << count << endl;
        return;
    }

    if (index == 0)
    {
        prepend(value);
    }
    else if (index == count)
    {
        append(value);
    }
    else
    {
        Node<T> *newNode = new Node<T>(value);
        Node<T> *current = head;

        for (int i = 0; i < index - 1; ++i)
        {
            current = current->getNext();
        }
        newNode->setNext(current->getNext());
        current->setNext(newNode);
        count++;
    }
}

// ========== DELETION OPERATIONS ==========

template <typename T>
void SinglyLinkedList<T>::deleteFromBeginning()
{
    if (isEmpty())
    {
        cout << "List is empty! Cannot delete." << endl;
        return;
    }

    Node<T> *temp = head;
    if (head == tail)
    {
        head = tail = nullptr;
    }
    else
    {
        head = head->getNext();
    }
    delete temp;
    count--;
}

template <typename T>
void SinglyLinkedList<T>::deleteFromEnd()
{
    if (isEmpty())
    {
        cout << "List is empty. Cannot delete." << endl;
        return;
    }

    if (head == tail)
    {
        deleteFromBeginning();
        return;
    }

    Node<T> *current = head;
    while (current->getNext() != tail)
    {
        current = current->getNext();
    }
    delete tail;
    tail = current;
    tail->setNext(nullptr);
    count--;
}

template <typename T>
void SinglyLinkedList<T>::deleteAtIndex(int index)
{
    if (index < 0 || index >= count)
    {
        cout << "Invalid position! It should be between 0 and " << count - 1 << endl;
        return;
    }

    if (index == 0)
    {
        deleteFromBeginning();
    }
    else if (index == count - 1)
    {
        deleteFromEnd();
    }
    else
    {
        Node<T> *prev = head;
        for (int i = 0; i < index - 1; ++i)
        {
            prev = prev->getNext();
        }

        Node<T> *toDelete = prev->getNext();
        prev->setNext(toDelete->getNext());

        delete toDelete;
        count--;
    }
}

// ========== SEARCH AND ACCESS OPERATIONS ==========

template <typename T>
bool SinglyLinkedList<T>::search(T value) const
{
    if (isEmpty())
    {
        return false;
    }

    Node<T> *current = head;
    while (current != nullptr)
    {
        if (current->getData() == value)
        {
            return true;
        }
        current = current->getNext();
    }
    return false;
}

template <typename T>
T &SinglyLinkedList<T>::getDataAt(int index)
{
    Node<T> *node = getNodeAtIndex(index);
    if (node == nullptr)
    {
        throw "Index out of bounds";
    }
    return node->getData();
}

template <typename T>
const T &SinglyLinkedList<T>::getDataAt(int index) const
{
    Node<T> *node = getNodeAtIndex(index);
    if (node == nullptr)
    {
        throw "Index out of bounds";
    }
    return node->getData();
}

template <typename T>
void SinglyLinkedList<T>::updateAtIndex(int index, T newValue)
{
    if (index < 0 || index >= count)
    {
        cout << "Invalid Index" << endl;
        return;
    }

    if (isEmpty())
    {
        cout << "Linked List is Empty" << endl;
        return;
    }

    Node<T> *current = head;
    for (int i = 0; i < index; i++)
    {
        current = current->getNext();
    }
    current->setData(newValue);
}

template <typename T>
int SinglyLinkedList<T>::countOccurrences(T value) const
{
    if (isEmpty())
    {
        return 0;
    }

    int countCheck = 0;
    Node<T> *current = head;
    while (current != nullptr)
    {
        if (current->getData() == value)
        {
            countCheck++;
        }
        current = current->getNext();
    }
    return countCheck;
}

// ========== ADDED FOR TRANSPORT-SYSTEM COMPATIBILITY ==========

template <typename T>
void SinglyLinkedList<T>::InsertAtEnd(const T &value)
{
    append(value);
}

template <typename T>
void SinglyLinkedList<T>::deleteFromIndex(int index)
{
    deleteAtIndex(index);
}

template <typename T>
T SinglyLinkedList<T>::getDataAtIndex(int index) const
{
    return getDataAt(index);
}

// ========== SORTING ALGORITHMS ==========

template <typename T>
void SinglyLinkedList<T>::bubbleSort()
{
    if (count < 2)
        return;

    bool swapped = true;

    while (swapped)
    {
        swapped = false;
        Node<T> *prev = nullptr;
        Node<T> *curr = head;

        while (curr && curr->getNext())
        {
            if (curr->getData() > curr->getNext()->getData())
            {
                swapped = true;
                swapNodes(prev, curr, curr, curr->getNext());

                // After swapping, curr moved down, so update prev
                if (prev == nullptr)
                    prev = head;
                else
                    prev = prev->getNext();
            }
            else
            {
                prev = curr;
                curr = curr->getNext();
            }
        }
    }
}

template <typename T>
void SinglyLinkedList<T>::selectionSort()
{
    if (count < 2)
        return;

    Node<T> *startPrev = nullptr;
    Node<T> *start = head;

    while (start && start->getNext())
    {
        Node<T> *minPrev = startPrev;
        Node<T> *minNode = start;

        Node<T> *prev = start;
        Node<T> *curr = start->getNext();

        while (curr)
        {
            if (curr->getData() < minNode->getData())
            {
                minPrev = prev;
                minNode = curr;
            }
            prev = curr;
            curr = curr->getNext();
        }

        if (minNode != start)
        {
            swapNodes(startPrev, start, minPrev, minNode);

            if (startPrev == nullptr)
                startPrev = head;
            else
                startPrev = startPrev->getNext();
        }
        else
        {
            startPrev = start;
            start = start->getNext();
        }
    }
}

template <typename T>
void SinglyLinkedList<T>::insertionSort()
{
    if (count < 2)
        return;

    Node<T> *sorted = nullptr;

    while (head != nullptr)
    {
        Node<T> *curr = head;
        head = head->getNext();
        curr->setNext(nullptr);

        if (sorted == nullptr || curr->getData() < sorted->getData())
        {
            curr->setNext(sorted);
            sorted = curr;
        }
        else
        {
            Node<T> *temp = sorted;
            while (temp->getNext() && temp->getNext()->getData() < curr->getData())
            {
                temp = temp->getNext();
            }
            curr->setNext(temp->getNext());
            temp->setNext(curr);
        }
    }

    head = sorted;

    Node<T> *p = head;
    while (p && p->getNext())
        p = p->getNext();
    tail = p;
}

// ========== UTILITY OPERATIONS ==========

template <typename T>
void SinglyLinkedList<T>::display() const
{
    // Node<T> *temp = head;
    // while (temp)
    // {
    //     cout << temp->getData();
    //     if (temp->getNext())
    //         cout << " -> ";
    //     temp = temp->getNext();
    // }
    // cout << " -> NULL" << endl;
    Node<T> *temp = head;
    while (temp)
    {
        cout << temp->getData() << endl; // changings
        temp = temp->getNext();          //  changings
    }
    cout << " -> NULL" << endl;
}

template <typename T>
void SinglyLinkedList<T>::reverse()
{
    if (count < 2)
        return;

    Node<T> *prev = nullptr;
    Node<T> *current = head;
    Node<T> *next = nullptr;

    tail = head;

    while (current != nullptr)
    {
        next = current->getNext();
        current->setNext(prev);
        prev = current;
        current = next;
    }

    head = prev;
}

template <typename T>
void SinglyLinkedList<T>::removeDuplicates()
{
    if (count < 2)
        return;

    Node<T> *current = head;

    while (current != nullptr && current->getNext() != nullptr)
    {
        Node<T> *runner = current;
        while (runner->getNext() != nullptr)
        {
            if (runner->getNext()->getData() == current->getData())
            {
                Node<T> *temp = runner->getNext();
                runner->setNext(runner->getNext()->getNext());
                delete temp;
                count--;

                if (runner->getNext() == nullptr)
                    tail = runner;
            }
            else
            {
                runner = runner->getNext();
            }
        }
        current = current->getNext();
    }
}

// ========== OPERATOR OVERLOADING ==========

template <typename T>
ostream &operator<<(ostream &out, const SinglyLinkedList<T> &list)
{
    Node<T> *temp = list.head;
    out << "[";
    while (temp != nullptr)
    {
        out << temp->getData();
        if (temp->getNext())
            out << " -> ";
        temp = temp->getNext();
    }
    out << "]";
    return out;
}

template <typename T>
bool SinglyLinkedList<T>::operator==(const SinglyLinkedList<T> &other) const
{
    if (count != other.count)
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
SinglyLinkedList<T> SinglyLinkedList<T>::operator+(const SinglyLinkedList<T> &other) const
{
    SinglyLinkedList<T> result;

    // Copy current list
    Node<T> *current = head;
    while (current != nullptr)
    {
        result.append(current->getData());
        current = current->getNext();
    }

    // Copy other list
    current = other.head;
    while (current != nullptr)
    {
        result.append(current->getData());
        current = current->getNext();
    }

    return result;
}