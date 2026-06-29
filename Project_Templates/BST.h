#pragma once

#include <iostream>
#include "MyArray.h"
using namespace std;

// ==================== BST NODE CLASS ====================
template <typename T>
class BSTNode
{
private:
    T key;
    BSTNode<T> *left;
    BSTNode<T> *right;

public:
    // Constructors
    BSTNode(T key);

    // Getters and Setters
    void setKey(T key);
    void setLeft(BSTNode<T> *left);
    void setRight(BSTNode<T> *right);

    // changes: BINASH
    T &getKey() { return key; }
    const T &getKey() const { return key; }

    //    T getKey() const;
    BSTNode<T> *getLeft() const;
    BSTNode<T> *getRight() const;
};

// ==================== BINARY SEARCH TREE CLASS ====================
template <typename T>
class BST
{
private:
    BSTNode<T> *root;
    int nodeCount;

    // Private helper methods
    BSTNode<T> *insertRecursive(BSTNode<T> *node, T key);
    BSTNode<T> *searchNodeRecursive(BSTNode<T> *node, T key);
    T *searchRecursive(BSTNode<T> *node, T key);
    BSTNode<T> *deleteRecursive(BSTNode<T> *node, T key);
    BSTNode<T> *findMinNode(BSTNode<T> *node) const;
    void inorderRecursive(BSTNode<T> *node) const;
    void clearRecursive(BSTNode<T> *node);
    void getAllElementsHelper(BSTNode<T> *node, MyArray<T> &arr) const; // Helper for getAllElements

public:
    // Constructor and Destructor
    BST();
    ~BST();

    // Basic Operations
    void insert(T key);
    BSTNode<T> *searchNode(T key);
    T *search(T key);
    void remove(T key);
    void clear();

    // Traversal Operations
    void inorderTraversal() const;

    // Utility Operations
    int getSize() const;
    BSTNode<T> *getRoot() const;
    bool isEmpty() const;

    // Additional Operations
    void preorderTraversal() const;
    void postorderTraversal() const;
    T *findMin() const;
    T *findMax() const;

    // Added for transport-system compatibility
    void insertNode(T key);
    bool removeNode(T key);
    MyArray<T> getAllElements() const;
};

// =============================================================
//                     BST NODE IMPLEMENTATION
// =============================================================

template <typename T>
BSTNode<T>::BSTNode(T key)
{
    this->key = key;
    this->left = nullptr;
    this->right = nullptr;
}

template <typename T>
void BSTNode<T>::setKey(T key)
{
    this->key = key;
}

template <typename T>
void BSTNode<T>::setLeft(BSTNode<T> *left)
{
    this->left = left;
}

template <typename T>
void BSTNode<T>::setRight(BSTNode<T> *right)
{
    this->right = right;
}

// changes: BINASH
// template <typename T>
// T& BSTNode<T>::getKey() const
//{
//    return key;
//}

template <typename T>
BSTNode<T> *BSTNode<T>::getLeft() const
{
    return left;
}

template <typename T>
BSTNode<T> *BSTNode<T>::getRight() const
{
    return right;
}

// =============================================================
//              BINARY SEARCH TREE IMPLEMENTATION
// =============================================================

// ========== PRIVATE HELPER METHODS ==========

template <typename T>
BSTNode<T> *BST<T>::insertRecursive(BSTNode<T> *node, T key)
{
    if (node == nullptr)
    {
        BSTNode<T> *newNode = new BSTNode<T>(key);
        return newNode;
    }

    if (key < node->getKey())
    {
        node->setLeft(insertRecursive(node->getLeft(), key));
    }
    else if (key > node->getKey())
    {
        node->setRight(insertRecursive(node->getRight(), key));
    }

    return node;
}
template <typename T>
T *searchRec(BSTNode<T> *NODE, const T &key)
{
    if (!NODE)
        return nullptr;
    int c = cmp(key, NODE->data);
    if (c == 0)
        return &NODE->data;
    if (c < 0)
        return searchRec(NODE->left, key);
    return searchRec(NODE->right, key);
}

template <typename T>
BSTNode<T> *BST<T>::searchNodeRecursive(BSTNode<T> *node, T key)
{
    if (node == nullptr)
    {
        cout << "Key not found : Nullptr !" << endl;
        return nullptr;
    }
    if (node->getKey() == key)
    {
        return node;
    }
    if (key < node->getKey())
    {
        return searchNodeRecursive(node->getLeft(), key);
    }
    else if (key > node->getKey())
    {
        return searchNodeRecursive(node->getRight(), key);
    }
    return nullptr;
}
template <typename T>
T *BST<T>::searchRecursive(BSTNode<T> *node, T key)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    if (node->getKey() == key)
    {
        return &node->getKey();
    }

    if (key < node->getKey())
    {
        return searchRecursive(node->getLeft(), key);
    }
    else
    {
        return searchRecursive(node->getRight(), key);
    }
}

template <typename T>
BSTNode<T> *BST<T>::deleteRecursive(BSTNode<T> *node, T key)
{
    if (node == nullptr)
    {
        return node;
    }

    if (key < node->getKey())
    {
        node->setLeft(deleteRecursive(node->getLeft(), key));
    }
    else if (key > node->getKey())
    {
        node->setRight(deleteRecursive(node->getRight(), key));
    }
    else
    {
        if (node->getLeft() == nullptr)
        {
            BSTNode<T> *temp = node->getRight();
            delete node;
            return temp;
        }
        else if (node->getRight() == nullptr)
        {
            BSTNode<T> *temp = node->getLeft();
            delete node;
            return temp;
        }

        BSTNode<T> *temp = findMinNode(node->getRight());
        node->setKey(temp->getKey());
        node->setRight(deleteRecursive(node->getRight(), temp->getKey()));
    }

    return node;
}

template <typename T>
BSTNode<T> *BST<T>::findMinNode(BSTNode<T> *node) const
{
    if (node == nullptr)
    {
        return node;
    }

    while (node->getLeft() != nullptr)
    {
        node = node->getLeft();
    }
    return node;
}

template <typename T>
void BST<T>::inorderRecursive(BSTNode<T> *node) const
{
    if (node != nullptr)
    {
        inorderRecursive(node->getLeft());
        // Changed from direct cout << node->getKey()
        // We'll use a generic approach
        cout << "[Node Data] ";
        inorderRecursive(node->getRight());
    }
}

template <typename T>
void BST<T>::clearRecursive(BSTNode<T> *node)
{
    if (node == nullptr)
    {
        return;
    }

    clearRecursive(node->getLeft());
    clearRecursive(node->getRight());
    delete node;
}

// ========== CONSTRUCTOR AND DESTRUCTOR ==========

template <typename T>
BST<T>::BST()
{
    this->root = nullptr;
    nodeCount = 0;
}

template <typename T>
BST<T>::~BST()
{
    clearRecursive(root);
    root = nullptr;
}

// ========== BASIC OPERATIONS ==========

template <typename T>
void BST<T>::insert(T key)
{
    root = insertRecursive(root, key);
    nodeCount++;
}

template <typename T>
BSTNode<T> *BST<T>::searchNode(T key)
{
    return searchNodeRecursive(root, key);
}
template <typename T>
T *BST<T>::search(T key)
{
    return searchRecursive(root, key);
}

template <typename T>
void BST<T>::remove(T key)
{
    root = deleteRecursive(root, key);
    nodeCount--;
}

template <typename T>
void BST<T>::clear()
{
    clearRecursive(root);
    root = nullptr;
    nodeCount = 0;
}

// ========== TRAVERSAL OPERATIONS ==========

template <typename T>
void BST<T>::inorderTraversal() const
{
    inorderRecursive(root);
    cout << endl;
}

// ========== UTILITY OPERATIONS ==========

template <typename T>
int BST<T>::getSize() const
{
    return nodeCount;
}

template <typename T>
BSTNode<T> *BST<T>::getRoot() const
{
    return root;
}

template <typename T>
bool BST<T>::isEmpty() const
{
    return root == nullptr;
}

// ========== ADDITIONAL OPERATIONS ==========

template <typename T>
void BST<T>::preorderTraversal() const
{
    // Preorder: Root -> Left -> Right
    if (root == nullptr)
    {
        return;
    }

    // Using a manual stack simulation
    BSTNode<T> *stack[100]; // Fixed size stack for simplicity
    int top = -1;
    stack[++top] = root;

    while (top >= 0)
    {
        BSTNode<T> *current = stack[top--];

        // Process current node
        cout << "[Node Data] ";

        // Push right child first (so left is processed first)
        if (current->getRight() != nullptr)
        {
            stack[++top] = current->getRight();
        }

        // Push left child
        if (current->getLeft() != nullptr)
        {
            stack[++top] = current->getLeft();
        }
    }
    cout << endl;
}

template <typename T>
void BST<T>::postorderTraversal() const
{
    // Postorder: Left -> Right -> Root
    if (root == nullptr)
    {
        return;
    }

    // Using two manual stacks
    BSTNode<T> *stack1[100];
    BSTNode<T> *stack2[100];
    int top1 = -1;
    int top2 = -1;

    stack1[++top1] = root;

    while (top1 >= 0)
    {
        BSTNode<T> *current = stack1[top1--];
        stack2[++top2] = current;

        if (current->getLeft() != nullptr)
        {
            stack1[++top1] = current->getLeft();
        }

        if (current->getRight() != nullptr)
        {
            stack1[++top1] = current->getRight();
        }
    }

    while (top2 >= 0)
    {
        BSTNode<T> *current = stack2[top2--];
        cout << "[Node Data] ";
    }
    cout << endl;
}

template <typename T>
T *BST<T>::findMin() const
{
    BSTNode<T> *minNode = findMinNode(root);
    if (minNode != nullptr)
    {
        return &minNode->getKey();
    }
    return nullptr;
}

template <typename T>
T *BST<T>::findMax() const
{
    if (root == nullptr)
    {
        return nullptr;
    }

    BSTNode<T> *current = root;
    while (current->getRight() != nullptr)
    {
        current = current->getRight();
    }
    return &current->getKey();
}

// Added methods for transport-system compatibility
template <typename T>
void BST<T>::insertNode(T key)
{
    insert(key); // Alias for existing insert method
}

template <typename T>
bool BST<T>::removeNode(T key)
{
    remove(key); // Alias for existing remove method
    return true;
}

template <typename T>
void BST<T>::getAllElementsHelper(BSTNode<T> *node, MyArray<T> &arr) const
{
    if (node == nullptr)
    {
        return;
    }

    // Inorder traversal: left -> root -> right
    getAllElementsHelper(node->getLeft(), arr);
    arr.push_back(node->getKey());
    getAllElementsHelper(node->getRight(), arr);
}

template <typename T>
MyArray<T> BST<T>::getAllElements() const
{
    MyArray<T> result;
    getAllElementsHelper(root, result);
    return result;
}