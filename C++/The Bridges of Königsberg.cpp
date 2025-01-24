/* 
Problem Description:
-----------------
The Bridges of Königsberg problem asks whether it is possible to walk through the city 
of Königsberg crossing each of its seven bridges exactly once and returning to the 
starting point. The city had seven bridges connecting two islands and the mainland, 
forming a complex network that challenged mathematicians of the time.

Historical Context:
----------------
In 1736, Leonhard Euler solved this problem, which is considered the birth of graph 
theory and topology. Euler proved that such a path was impossible, demonstrating that 
the configuration of bridges made a single traversal of all bridges unachievable. 
This breakthrough laid the foundation for modern network theory and mathematical graph analysis.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

class KonigsbergBridges {
private:
    // Representation of graph using adjacency list
    std::unordered_map<int, std::vector<int>> graph;
    int totalBridges;

public:
    // Constructor to initialize the graph
    KonigsbergBridges() {
        // Original Königsberg bridge configuration
        // 4 land masses (nodes): 0, 1, 2, 3
        // Bridges connecting these masses
        graph[0] = {1, 1, 2, 3};  // Node 0 has connections
        graph[1] = {0, 0, 2, 3};  // Node 1 has connections
        graph[2] = {0, 1, 3, 3};  // Node 2 has connections
        graph[3] = {0, 1, 2, 2};  // Node 3 has connections
        totalBridges = 7;
    }

    // Check if Eulerian path exists
    bool hasEulerianPath() {
        return checkEulerianCondition();
    }

    // Count odd-degree vertices
    int countOddDegreeVertices() {
        int oddVertices = 0;
        for (const auto& node : graph) {
            if (node.second.size() % 2 != 0) {
                oddVertices++;
            }
        }
        return oddVertices;
    }

    // Check Eulerian path conditions
    bool checkEulerianCondition() {
        int oddVertices = countOddDegreeVertices();
        
        // Eulerian path exists if 0 or 2 vertices have odd degree
        return (oddVertices == 0 || oddVertices == 2);
    }

    // Get total number of bridges
    int getBridgeCount() const {
        return totalBridges;
    }
};

namespace {
    // Unit tests
    void runTests() {
        KonigsbergBridges bridges;

        // Test: Total number of bridges
        assert(bridges.getBridgeCount() == 7);

        // Test: Eulerian path condition
        assert(bridges.hasEulerianPath() == false);

        // Test: Count of odd-degree vertices
        assert(bridges.countOddDegreeVertices() == 4);

        std::cout << "All Königsberg Bridges tests passed!" << std::endl;
    }
}

int main() {
    KonigsbergBridges bridges;

    std::cout << "Total Bridges: " << bridges.getBridgeCount() << std::endl;
    std::cout << "Eulerian Path Possible: " << 
        (bridges.hasEulerianPath() ? "Yes" : "No") << std::endl;
    std::cout << "Odd-Degree Vertices: " << 
        bridges.countOddDegreeVertices() << std::endl;

    // Run tests
    runTests();

    return 0;
}