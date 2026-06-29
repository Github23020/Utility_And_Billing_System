#pragma once

#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class MyArray
{
private:
    T *arr;
    int capacity;
    int size;

    // Private helper methods
    void resizeArray();
    void heapify(int n, int i);
    void swapElements(T &a, T &b);

public:
    // ========== CONSTRUCTORS & DESTRUCTOR ==========

    // Default constructor: empty array with small initial capacity
    MyArray();

    // Constructor with given initial size
    MyArray(int initialSize);

    // Copy constructor (deep copy)
    MyArray(const MyArray<T> &other);

    // Destructor
    ~MyArray();

    // ========== OPERATOR OVERLOADING ==========

    // Copy assignment operator (deep copy)
    MyArray<T> &operator=(const MyArray<T> &other);

    // Subscript operator (non-const)
    T &operator[](int index);

    // Subscript operator (const)
    const T &operator[](int index) const;

    // Equality operator
    bool operator==(const MyArray<T> &other) const;

    // Concatenation operator
    MyArray<T> operator+(const MyArray<T> &other) const;

    // Output stream operator
    friend ostream &operator<<(ostream &out, const MyArray<T> &obj)
    {
        out << "[";
        for (int i = 0; i < obj.size; i++)
        {
            out << obj.arr[i];
            if (i < obj.size - 1)
                out << ", ";
        }
        out << "]";
        return out;
    }

    // ========== BASIC ARRAY OPERATIONS ==========

    // Add element at the end
    void pushBack(T data);

    // Alias for pushBack
    void append(T data);

    // Add element at the beginning
    void prepend(T data);

    // Insert element at specific index
    void insertAt(int index, T data);

    // Remove last element
    void popBack();

    // Alias for popBack
    void pop_back();

    // Remove element at specific index
    void removeAt(int index);

    // Alias for removeAt
    void removeAtIndex(int index);

    // Remove first occurrence of value
    bool removeByValue(T value);

    // Clear all elements
    void clear();

    // ========== SEARCH & QUERY OPERATIONS ==========

    // Find value and return pointer to element
    T *find(T value);

    // Find value and return index
    int findIndex(T value) const;

    // Check if array contains value
    bool contains(T value) const;

    // Check if array is empty
    bool isEmpty() const;

    // Get last element
    T &back();

    const T &back() const;

    // ========== SORTING ALGORITHMS ==========

    // Bubble sort
    void bubbleSort(bool ascending = true);

    // Heap sort
    void heapSort(bool ascending = true);

    // Counting sort (for integer types only)
    void countSort();

    // ========== OTHER OPERATIONS ==========

    // Reverse array
    void reverse();

    // Remove duplicate elements
    void removeDuplicates();

    // Display array (for debugging)
    void display() const;

    // ========== GETTERS ==========

    int getSize() const;
    int get_size() const;  //
    int getCapacity() const;
    T *getArray();
    const T *getArray() const;
    T getValueAt(int index) const;

    // ========== UTILITY METHODS ==========

    // Reserve capacity
    void reserve(int newCapacity);

    // Shrink to fit
    void shrinkToFit();

    // Swap with another array
    void swap(MyArray<T> &other);

    // NEW FUNCTION ADDED-BINASH
    void insert(const T &element); // new function added- binash
};

// =============================================================
//                     IMPLEMENTATION
// =============================================================

template <typename T>
void MyArray<T>::swapElements(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
void MyArray<T>::resizeArray()
{
    capacity = capacity * 2;
    T *newArr = new T[capacity];
    for (int i = 0; i < size; i++)
    {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
}

template <typename T>
void MyArray<T>::heapify(int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i)
    {
        swapElements(arr[i], arr[largest]);
        heapify(n, largest);
    }
}

// ========== CONSTRUCTORS & DESTRUCTOR ==========

template <typename T>
MyArray<T>::MyArray()
{
    this->capacity = 5;
    arr = new T[capacity];
    size = 0;
    for (int i = 0; i < capacity; i++)
    {
        arr[i] = T();
    }
}

template <typename T>
MyArray<T>::MyArray(int initialSize)
{
    if (initialSize <= 0)
    {
        initialSize = 0;
    }
    this->capacity = (initialSize > 0) ? initialSize : 5;
    arr = new T[capacity];
    size = initialSize;
    for (int i = 0; i < size; i++)
    {
        arr[i] = T();
    }
}

template <typename T>
MyArray<T>::MyArray(const MyArray<T> &other)
{
    capacity = other.capacity;
    size = other.size;
    arr = new T[capacity];
    for (int i = 0; i < size; i++)
    {
        arr[i] = other.arr[i];
    }
}

template <typename T>
MyArray<T>::~MyArray()
{
    delete[] arr;
}

// ========== OPERATOR OVERLOADING ==========

template <typename T>
MyArray<T> &MyArray<T>::operator=(const MyArray<T> &other)
{
    if (this == &other)
    {
        return *this;
    }
    delete[] arr;
    capacity = other.capacity;
    size = other.size;
    arr = new T[capacity];
    for (int i = 0; i < size; i++)
    {
        arr[i] = other.arr[i];
    }
    return *this;
}

template <typename T>
T &MyArray<T>::operator[](int index)
{
    if (index < 0 || index >= size)
    {
        throw out_of_range("Index out of range");
    }
    return arr[index];
}

template <typename T>
const T &MyArray<T>::operator[](int index) const
{
    if (index < 0 || index >= size)
    {
        throw out_of_range("Index out of range");
    }
    return arr[index];
}

template <typename T>
bool MyArray<T>::operator==(const MyArray<T> &other) const
{
    if (size != other.size)
        return false;

    for (int i = 0; i < size; i++)
    {
        if (arr[i] != other.arr[i])
            return false;
    }
    return true;
}

template <typename T>
MyArray<T> MyArray<T>::operator+(const MyArray<T> &other) const
{
    MyArray<T> result(size + other.size);
    result.size = size + other.size;

    for (int i = 0; i < size; i++)
        result.arr[i] = arr[i];

    for (int i = 0; i < other.size; i++)
        result.arr[size + i] = other.arr[i];

    return result;
}

// ========== BASIC ARRAY OPERATIONS ==========

template <typename T>
void MyArray<T>::pushBack(T data)
{
    if (size == capacity)
    {
        resizeArray();
    }
    arr[size] = data;
    size++;
}

template <typename T>
void MyArray<T>::append(T data)
{
    pushBack(data);
}

template <typename T>
void MyArray<T>::prepend(T data)
{
    if (size == capacity)
    {
        resizeArray();
    }
    for (int i = size; i > 0; i--)
    {
        arr[i] = arr[i - 1];
    }
    arr[0] = data;
    size++;
}

template <typename T>
void MyArray<T>::insertAt(int index, T data)
{
    if (index < 0 || index > size)
    {
        throw out_of_range("Index out of range");
    }

    if (size == capacity)
    {
        resizeArray();
    }

    for (int i = size; i > index; i--)
    {
        arr[i] = arr[i - 1];
    }
    arr[index] = data;
    size++;
}

template <typename T>
void MyArray<T>::popBack()
{
    if (size > 0)
    {
        size--;
    }
}

template <typename T>
void MyArray<T>::pop_back()
{
    popBack();
}

template <typename T>
void MyArray<T>::removeAt(int index)
{
    if (index < 0 || index >= size)
    {
        throw out_of_range("Index out of range");
    }

    for (int i = index; i < size - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
    size--;
}

template <typename T>
void MyArray<T>::removeAtIndex(int index)
{
    removeAt(index);
}

template <typename T>
bool MyArray<T>::removeByValue(T value)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == value)
        {
            removeAt(i);
            return true;
        }
    }
    return false;
}

template <typename T>
void MyArray<T>::clear()
{
    size = 0;
}

// ========== SEARCH & QUERY OPERATIONS ==========

template <typename T>
T *MyArray<T>::find(T value)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == value)
        {
            return &arr[i];
        }
    }
    return nullptr;
}

template <typename T>
int MyArray<T>::findIndex(T value) const
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == value)
        {
            return i;
        }
    }
    return -1;
}

template <typename T>
bool MyArray<T>::contains(T value) const
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == value)
        {
            return true;
        }
    }
    return false;
}

template <typename T>
bool MyArray<T>::isEmpty() const
{
    return size == 0;
}

template <typename T>
T &MyArray<T>::back()
{
    if (size == 0)
    {
        throw out_of_range("Array is empty");
    }
    return arr[size - 1];
}

template <typename T>
const T &MyArray<T>::back() const
{
    if (size == 0)
    {
        throw out_of_range("Array is empty");
    }
    return arr[size - 1];
}

// ========== SORTING ALGORITHMS ==========

template <typename T>
void MyArray<T>::bubbleSort(bool ascending)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (ascending)
            {
                if (arr[j] > arr[j + 1])
                    swapElements(arr[j], arr[j + 1]);
            }
            else
            {
                if (arr[j] < arr[j + 1])
                    swapElements(arr[j], arr[j + 1]);
            }
        }
    }
}

template <typename T>
void MyArray<T>::heapSort(bool ascending)
{
    // Build max heap
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(size, i);

    // Extract elements from heap
    for (int i = size - 1; i > 0; i--)
    {
        swapElements(arr[0], arr[i]);
        heapify(i, 0);
    }

    // Reverse for descending order if needed
    if (!ascending)
    {
        reverse();
    }
}

template <typename T>
void MyArray<T>::countSort()
{
    if (size <= 1)
        return;

    // Find maximum element
    T maxElement = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] > maxElement)
            maxElement = arr[i];
    }

    // Create count array - using C-style cast
    int maxVal = (int)maxElement;
    int range = maxVal + 1;
    int *count = new int[range];

    // Initialize count array with zeros
    for (int i = 0; i < range; i++)
    {
        count[i] = 0;
    }

    // Count occurrences
    for (int i = 0; i < size; i++)
    {
        int index = (int)arr[i];
        count[index]++;
    }

    // Modify count array to store positions
    for (int i = 1; i < range; i++)
    {
        count[i] = count[i] + count[i - 1];
    }

    // Build output array
    T *output = new T[size];
    for (int i = size - 1; i >= 0; i--)
    {
        int index = (int)arr[i];
        output[count[index] - 1] = arr[i];
        count[index]--;
    }

    // Copy back to original array
    for (int i = 0; i < size; i++)
    {
        arr[i] = output[i];
    }

    delete[] count;
    delete[] output;
}

// ========== OTHER OPERATIONS ==========

template <typename T>
void MyArray<T>::reverse()
{
    for (int i = 0; i < size / 2; i++)
    {
        swapElements(arr[i], arr[size - i - 1]);
    }
}

template <typename T>
void MyArray<T>::removeDuplicates()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size;)
        {
            if (arr[i] == arr[j])
            {
                removeAt(j);
            }
            else
            {
                j++;
            }
        }
    }
}

template <typename T>
void MyArray<T>::display() const
{
    cout << "[";
    for (int i = 0; i < size; i++)
    {
        cout << arr[i];
        if (i < size - 1)
            cout << ", ";
    }
    cout << "]" << endl;
}

// ========== GETTERS ==========

template <typename T>
int MyArray<T>::getSize() const
{
    return size;
}
//added this function for array size --Usman Latif
template <typename T>
int MyArray<T>::get_size() const
{
    return size;
}

template <typename T>
int MyArray<T>::getCapacity() const
{
    return capacity;
}

template <typename T>
T *MyArray<T>::getArray()
{
    return arr;
}

template <typename T>
const T *MyArray<T>::getArray() const
{
    return arr;
}

template <typename T>
T MyArray<T>::getValueAt(int index) const
{
    if (index < 0 || index >= size)
    {
        throw out_of_range("Index out of range");
    }
    return arr[index];
}

// ========== UTILITY METHODS ==========

template <typename T>
void MyArray<T>::reserve(int newCapacity)
{
    if (newCapacity > capacity)
    {
        T *newArr = new T[newCapacity];
        for (int i = 0; i < size; i++)
        {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        capacity = newCapacity;
    }
}

template <typename T>
void MyArray<T>::shrinkToFit()
{
    if (size < capacity)
    {
        capacity = size;
        T *newArr = new T[capacity];
        for (int i = 0; i < size; i++)
        {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
    }
}

template <typename T>
void MyArray<T>::swap(MyArray<T> &other)
{
    T *tempArr = arr;
    int tempSize = size;
    int tempCapacity = capacity;

    arr = other.arr;
    size = other.size;
    capacity = other.capacity;

    other.arr = tempArr;
    other.size = tempSize;
    other.capacity = tempCapacity;
}

template <typename T>
void MyArray<T>::insert(const T &element)
{
    append(element);
}