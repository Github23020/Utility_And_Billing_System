#pragma once

#include <iostream>
#include <limits>
#include "MyArray.h"
using namespace std;

const int INF = numeric_limits<int>::max();

template <typename T>
class Graph
{
private:
    int vertices;          // Number of vertices
    int **adjacencyMatrix; // 2D matrix to store edge weights (using int for weights)
    T *vertexData;         // Stores data for each vertex

public:
    // ========== CONSTRUCTORS AND DESTRUCTOR ==========
    Graph();
    Graph(int v);
    ~Graph();

    // ========== BASIC GRAPH OPERATIONS ==========
    bool isValidVertex(int vertex_index) const;
    int getVertices() const;

    // ========== VERTEX DATA OPERATIONS ==========
    void addVertexData(int vertex, T data);
    T getVertexData(int vertex);

    // ========== EDGE OPERATIONS ==========
    void addEdge(int from, int to, int weight);
    void removeEdge(int from, int to);
    void deleteEdge(int source, int dest);
    void setWeight(int source, int dest, int weight);
    int getWeight(int from, int to);
    bool checkEdgeStatus(int source, int dest);

    // ========== GRAPH MODIFICATION OPERATIONS ==========
    void expandMatrix();
    void updateEdge(int old_source, int old_destination, int new_source, int new_destination, int weight);

    // ========== GRAPH QUERY OPERATIONS ==========
    int getDegree(int vertex_index);
    int *getNeighbours(int vertex_index, int &count);

    // ========== DISPLAY OPERATIONS ==========
    void printGraph() const;
    void displayGraph() const;

    // ========== MENU OPERATION ==========
    void menu() const;

    // ========== ADDED FOR TRANSPORT-SYSTEM COMPATIBILITY ==========
    int *getNeighbors(int vertex);              // Alias for getNeighbours (American spelling)
    MyArray<int> getNeighborsArray(int vertex); // Returns neighbors as MyArray
    int getWeight(int v1, int v2) const;        // Const overload for getWeight
};

// =============================================================
//                     GRAPH IMPLEMENTATION
// =============================================================

// ========== CONSTRUCTORS AND DESTRUCTOR ==========

template <typename T>
Graph<T>::Graph()
{
    vertices = 0;
    adjacencyMatrix = nullptr;
    vertexData = nullptr;
}

template <typename T>
Graph<T>::Graph(int v)
{
    vertices = v;
    vertexData = new T[v];

    // Initialize adjacency matrix
    adjacencyMatrix = new int *[v];
    for (int i = 0; i < v; i++)
    {
        adjacencyMatrix[i] = new int[v];
        for (int j = 0; j < v; j++)
        {
            adjacencyMatrix[i][j] = INF;
        }
        adjacencyMatrix[i][i] = 0;
    }
}

template <typename T>
Graph<T>::~Graph()
{
    if (adjacencyMatrix)
    {
        for (int i = 0; i < vertices; i++)
        {
            delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;
    }

    if (vertexData)
    {
        delete[] vertexData;
    }
}

// ========== BASIC GRAPH OPERATIONS ==========

template <typename T>
bool Graph<T>::isValidVertex(int vertex_index) const
{
    return (vertex_index >= 0 && vertex_index < vertices);
}

template <typename T>
int Graph<T>::getVertices() const
{
    return vertices;
}

// ========== VERTEX DATA OPERATIONS ==========

template <typename T>
void Graph<T>::addVertexData(int vertex, T data)
{
    if (vertex >= 0 && vertex < vertices)
    {
        vertexData[vertex] = data;
    }
}

template <typename T>
T Graph<T>::getVertexData(int vertex)
{
    if (vertex >= 0 && vertex < vertices)
    {
        return vertexData[vertex];
    }
    return T();
}

// ========== EDGE OPERATIONS ==========

template <typename T>
void Graph<T>::addEdge(int from, int to, int weight)
{
    if (from >= 0 && from < vertices && to >= 0 && to < vertices)
    {
        adjacencyMatrix[from][to] = weight;
        adjacencyMatrix[to][from] = weight; // Bidirectional graph
    }
}

template <typename T>
void Graph<T>::removeEdge(int from, int to)
{
    if (from >= 0 && from < vertices && to >= 0 && to < vertices)
    {
        adjacencyMatrix[from][to] = INF;
        adjacencyMatrix[to][from] = INF;
    }
}

template <typename T>
void Graph<T>::deleteEdge(int source, int dest)
{
    // Alias for removeEdge
    removeEdge(source, dest);
}

template <typename T>
void Graph<T>::setWeight(int source, int dest, int weight)
{
    // Alias for addEdge (overwrites existing weight)
    addEdge(source, dest, weight);
}

template <typename T>
int Graph<T>::getWeight(int from, int to)
{
    if (from >= 0 && from < vertices && to >= 0 && to < vertices)
    {
        return adjacencyMatrix[from][to];
    }
    return INF;
}

template <typename T>
bool Graph<T>::checkEdgeStatus(int source, int dest)
{
    if (source >= 0 && source < vertices && dest >= 0 && dest < vertices)
    {
        return (adjacencyMatrix[source][dest] != INF && source != dest);
    }
    return false;
}

// ========== GRAPH MODIFICATION OPERATIONS ==========

template <typename T>
void Graph<T>::expandMatrix()
{
    // Create new matrix with size vertices + 1
    int newSize = vertices + 1;
    int **tempMatrix = new int *[newSize];

    // Allocate and copy old data
    for (int i = 0; i < newSize; i++)
    {
        tempMatrix[i] = new int[newSize];
        for (int j = 0; j < newSize; j++)
        {
            if (i < vertices && j < vertices)
            {
                // Copy existing data
                tempMatrix[i][j] = adjacencyMatrix[i][j];
            }
            else if (i == j)
            {
                // New diagonal element
                tempMatrix[i][j] = 0;
            }
            else
            {
                // New edge (no connection)
                tempMatrix[i][j] = INF;
            }
        }
    }

    // Create new vertex data array
    T *tempVertexData = new T[newSize];
    for (int i = 0; i < vertices; i++)
    {
        tempVertexData[i] = vertexData[i];
    }
    // Initialize new vertex with default value
    tempVertexData[vertices] = T();

    // Delete old arrays
    if (adjacencyMatrix)
    {
        for (int i = 0; i < vertices; i++)
        {
            delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;
    }

    if (vertexData)
    {
        delete[] vertexData;
    }

    // Update pointers and size
    adjacencyMatrix = tempMatrix;
    vertexData = tempVertexData;
    vertices = newSize;
}

template <typename T>
void Graph<T>::updateEdge(int old_source, int old_destination, int new_source, int new_destination, int weight)
{
    if (!isValidVertex(old_source) || !isValidVertex(old_destination) ||
        !isValidVertex(new_source) || !isValidVertex(new_destination))
    {
        cout << "Invalid vertices" << endl;
        return;
    }

    // Remove old edge if it exists
    if (adjacencyMatrix[old_source][old_destination] != INF && old_source != old_destination)
    {
        removeEdge(old_source, old_destination);
    }

    // Add new edge
    addEdge(new_source, new_destination, weight);
}

// ========== GRAPH QUERY OPERATIONS ==========

template <typename T>
int Graph<T>::getDegree(int vertex_index)
{
    if (!isValidVertex(vertex_index))
    {
        cout << "Invalid Vertex Index" << endl;
        return -1;
    }

    int count = 0;
    for (int i = 0; i < vertices; i++)
    {
        if (adjacencyMatrix[vertex_index][i] != INF && vertex_index != i)
        {
            count++;
        }
    }
    return count;
}

template <typename T>
int *Graph<T>::getNeighbours(int vertex_index, int &count)
{
    count = 0;

    if (!isValidVertex(vertex_index))
    {
        cout << "Invalid Vertex Index" << endl;
        return nullptr;
    }

    // First pass: count neighbors
    for (int i = 0; i < vertices; i++)
    {
        if (adjacencyMatrix[vertex_index][i] != INF && vertex_index != i)
        {
            count++;
        }
    }

    if (count == 0)
    {
        return nullptr;
    }

    // Second pass: allocate array and fill with neighbor indices
    int *neighbors = new int[count];
    int index = 0;
    for (int i = 0; i < vertices; i++)
    {
        if (adjacencyMatrix[vertex_index][i] != INF && vertex_index != i)
        {
            neighbors[index] = i;
            index++;
        }
    }

    return neighbors;
}

// ========== DISPLAY OPERATIONS ==========

template <typename T>
void Graph<T>::printGraph() const
{
    cout << "\nAdjacency Matrix:" << endl;
    cout << "   ";
    for (int i = 0; i < vertices; i++)
    {
        cout << i << "  ";
    }
    cout << endl;

    for (int i = 0; i < vertices; i++)
    {
        cout << i << ": ";
        for (int j = 0; j < vertices; j++)
        {
            if (adjacencyMatrix[i][j] == INF)
            {
                cout << "∞  ";
            }
            else if (adjacencyMatrix[i][j] == 0 && i != j)
            {
                cout << "0  ";
            }
            else
            {
                cout << adjacencyMatrix[i][j] << "  ";
            }
        }
        cout << endl;
    }
}

template <typename T>
void Graph<T>::displayGraph() const
{
    // Alias for printGraph
    printGraph();
}

// ========== MENU OPERATION ==========

template <typename T>
void Graph<T>::menu() const
{
    cout << "\n=================== GRAPH MENU =====================" << endl;
    cout << "1. Add Edge" << endl;
    cout << "2. Remove Edge" << endl;
    cout << "3. Update Edge" << endl;
    cout << "4. Check Edge Status" << endl;
    cout << "5. Get Degree of Vertex" << endl;
    cout << "6. Get Neighbours" << endl;
    cout << "7. Display Graph" << endl;
    cout << "8. Add Vertex Data" << endl;
    cout << "9. Get Vertex Data" << endl;
    cout << "10. Expand Graph (Add Vertex)" << endl;
    cout << "11. Get Edge Weight" << endl;
    cout << "12. Set Edge Weight" << endl;
    cout << "==================================================" << endl;
}

// ========== ADDED FOR TRANSPORT-SYSTEM COMPATIBILITY ==========

template <typename T>
int *Graph<T>::getNeighbors(int vertex)
{
    int count = 0;
    return getNeighbours(vertex, count); // Alias for existing getNeighbours
}

template <typename T>
int Graph<T>::getWeight(int v1, int v2) const
{
    if (v1 >= 0 && v1 < vertices && v2 >= 0 && v2 < vertices)
    {
        return adjacencyMatrix[v1][v2];
    }
    return INF;
}

template <typename T>
MyArray<int> Graph<T>::getNeighborsArray(int vertex)
{
    MyArray<int> neighbors;
    if (vertex >= 0 && vertex < vertices)
    {
        for (int i = 0; i < vertices; i++)
        {
            if (adjacencyMatrix[vertex][i] != INF && i != vertex)
            {
                neighbors.pushBack(i);
            }
        }
    }
    return neighbors;
}