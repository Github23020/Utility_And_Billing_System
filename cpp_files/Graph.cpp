#include "../h_files/Graph.h"
#include <iostream>


using namespace std;

// Constructor
Graph::Graph(int nodes) : nodeCount(nodes) {
    if (nodes <= 0) {
        matrix = nullptr;
        return;
    }

    // Create adjacency matrix
    matrix = new int*[nodes];
    for (int i = 0; i < nodes; i++) {
        matrix[i] = new int[nodes];
    }

    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            matrix[i][j] = 0;
        }
    }
}

// Destructor
Graph::~Graph() {
    if (matrix) {
        for (int i = 0; i < nodeCount; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
}

// Add connection
void Graph::addConnection(int from, int to) {
    if (from < 0 || from >= nodeCount || to < 0 || to >= nodeCount) {
        cout << " Must be between 0 and " << (nodeCount-1) << endl;
        return;
    }

    matrix[from][to] = 1;
    matrix[to][from] = 1;
    cout << "Connected service area " << from << " to " << to << endl;
}

// Check if two service areas are connected
bool Graph::isConnected(int from, int to) const {
    if (from < 0 || from >= nodeCount || to < 0 || to >= nodeCount) {
        return false;
    }
    return matrix[from][to] == 1;
}

// Display
void Graph::displayConnections() const {
    cout << "\n=== Service Area Connectivity ===" << endl;
    cout << "Total service areas: " << nodeCount << endl << endl;

    bool hasAnyConnections = false;

    for (int i = 0; i < nodeCount; i++) {
        cout << "Area " << i << " connects to: ";
        bool areaHasConnections = false;

        for (int j = 0; j < nodeCount; j++) {
            if (matrix[i][j] == 1) {
                cout << j << " ";
                areaHasConnections = true;
                hasAnyConnections = true;
            }
        }

        if (!areaHasConnections) {
            cout << "(none)";
        }
        cout << endl;
    }

    if (!hasAnyConnections) {
        cout << "\nNo connections exist " << endl;
    }
}

// Get number of service areas
int Graph::getNodeCount() const {
    return nodeCount;
}

// Convert graph to JSON format
json Graph::toJson() const {
    json j;

    j["nodeCount"] = nodeCount;

    json matrixArray = json::array();
    for (int i = 0; i < nodeCount; i++) {
        json rowArray = json::array();
        for (int j = 0; j < nodeCount; j++) {
            rowArray.push_back(matrix[i][j]);
        }
        matrixArray.push_back(rowArray);
    }

    j["matrix"] = matrixArray;
    return j;
}

// Load graph from JSON format
void Graph::fromJson(const json& j) {
    // Clear existing matrix
    if (matrix) {
        for (int i = 0; i < nodeCount; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix = nullptr;
    }

    // Get new dimensions
    nodeCount = j["nodeCount"];

    if (nodeCount <= 0) {
        matrix = nullptr;
        return;
    }

    // Create new matrix
    matrix = new int*[nodeCount];
    for (int i = 0; i < nodeCount; i++) {
        matrix[i] = new int[nodeCount];
    }

    // Load matrix data
    json matrixArray = j["matrix"];
    for (int i = 0; i < nodeCount; i++) {
        json rowArray = matrixArray[i];
        for (int j = 0; j < nodeCount; j++) {
            matrix[i][j] = rowArray[j];
        }
    }
}

