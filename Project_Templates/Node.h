#ifndef NODE_H // Add include guard ---USMAN LATIF
#define NODE_H
template <typename T>
class Node
{
private:
    T data;
    Node<T> *next;
    Node<T> *previous;

public:
    // Constructors
    Node();
    Node(T val);

    // Getters and Setters
    void setNext(Node<T> *val);
    Node<T> *getNext();
    void setPrevious(Node<T> *val);
    Node<T> *getPrevious();
    void setData(const T &d);
    T &getData();
    const T &getData() const;
};

// =============================================================
//                     NODE IMPLEMENTATION
// =============================================================

template <typename T>
Node<T>::Node()
{
    next = previous = nullptr;
    data = T();
}

template <typename T>
Node<T>::Node(T val)
{
    next = previous = nullptr;
    data = val;
}

template <typename T>
void Node<T>::setNext(Node<T> *val)
{
    next = val;
}

template <typename T>
Node<T> *Node<T>::getNext()
{
    return next;
}

template <typename T>
void Node<T>::setPrevious(Node<T> *val)
{
    previous = val;
}

template <typename T>
Node<T> *Node<T>::getPrevious()
{
    return previous;
}

template <typename T>
void Node<T>::setData(const T &d)
{
    data = d;
}

template <typename T>
T &Node<T>::getData()
{
    return data;
}

template <typename T>
const T &Node<T>::getData() const
{
    return data;
}
#endif