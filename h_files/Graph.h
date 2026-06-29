#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include "../User_Authentication/json.hpp"

using json = nlohmann::json;

class Graph {
private:
    int** matrix;      // adjacency matrix
    int nodeCount;     // total number of nodes

public:
    // Constructor & Destructor
    Graph(int nodes = 0);
    ~Graph();

    // Basic connection methods for service areas
    void addConnection(int from, int to);
    bool isConnected(int from, int to) const;
    void displayConnections() const;
    int getNodeCount() const;

    // JSON methods that match UtilityJsonHelper expectations
    json toJson() const;           // Changed: returns json, not int**
    void fromJson(const json& j);  // Changed: takes json parameter

};

#endif // GRAPH_H