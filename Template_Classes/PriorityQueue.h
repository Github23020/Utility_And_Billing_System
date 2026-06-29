#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <iostream>
#include "MyArray.h"
using namespace std;

template <typename T>
class PriorityQueue
{
    MyArray<T> heap;

public:
    PriorityQueue();
    ~PriorityQueue();
    bool isEmpty() const;
    void enqueue(const T &value);
    T dequeue();
    T peek(); // removed const
    int getSize() const;
    void clear();
    void printHeap(); // removed const
    void heapifyUp(int index);
    void heapifyDown(int index);
};

template <typename T>
PriorityQueue<T>::PriorityQueue() : heap() {}

template <typename T>
PriorityQueue<T>::~PriorityQueue() {}

template <typename T>
bool PriorityQueue<T>::isEmpty() const { return heap.get_size() == 0; }

template <typename T>
void PriorityQueue<T>::heapifyUp(int index)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;
        if (heap[parent] < heap[index])
        {
            T tmp = heap[parent];
            heap[parent] = heap[index];
            heap[index] = tmp;
            index = parent;
        }
        else
            break;
    }
}

template <typename T>
void PriorityQueue<T>::heapifyDown(int index)
{
    int n = heap.get_size();
    while (true)
    {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;
        if (left < n && heap[left] > heap[largest])
            largest = left;
        if (right < n && heap[right] > heap[largest])
            largest = right;
        if (largest != index)
        {
            T tmp = heap[index];
            heap[index] = heap[largest];
            heap[largest] = tmp;
            index = largest;
        }
        else
            break;
    }
}

template <typename T>
void PriorityQueue<T>::enqueue(const T &value)
{
    heap.append(value);
    heapifyUp(heap.get_size() - 1);
}

template <typename T>
T PriorityQueue<T>::dequeue()
{
    if (isEmpty())
        throw "Heap empty";
    T top = heap[0];
    int n = heap.get_size();
    if (n == 1)
    {
        heap.pop_back();
        return top;
    }
    heap[0] = heap[n - 1];
    heap.pop_back();
    heapifyDown(0);
    return top;
}

template <typename T>
T PriorityQueue<T>::peek()
{ // now non-const
    if (isEmpty())
        throw "Heap empty";
    return heap[0];
}

template <typename T>
int PriorityQueue<T>::getSize() const { return heap.get_size(); }

template <typename T>
void PriorityQueue<T>::clear() { heap.clear(); }

template <typename T>
void PriorityQueue<T>::printHeap()
{ // now non-const
    cout << "Heap: ";
    for (int i = 0; i < heap.get_size(); ++i)
        cout << heap[i] << " ";
    cout << endl;
}

#endif