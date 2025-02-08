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

Dev Notes:
---------
im just translating the rust version, did you think i would use my brain?
*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

 /// Represents a graph structure using adjacency list
class Graph {
private:
    // Equivalent to Rust's HashMap<char, Vec<char>>
    std::unordered_map<char, std::vector<char>> adjacency_list;

public:
    // Default constructor
    Graph() = default;

    // Creates a new graph with given edges
    Graph(const std::vector<std::pair<char, char>>& edges) {
        for (const auto& [u, v] : edges) {
            adjacency_list[u].push_back(v);
            adjacency_list[v].push_back(u);
        }
    }

    // Getter for adjacency list (useful for testing and verification)
    const std::unordered_map<char, std::vector<char>>& get_adjacency_list() const {
        return adjacency_list;
    }

    // Determines the degree of each node and checks for Eulerian path or circuit
    std::string analyze_elerian() const {
        int odd_degree_const = 0;
        for (const auto& [node, neighbors] : adjacency_list) {
            int degree = neighbors.size();
            std::cout << "Vertex" << node << "has degree" << degree;

            if (degree % 2 != 0) {
                odd_degree_const++;
            }
        }

        if (odd_degree_const == 0) {
            return "This graph has an Eulerian circuit (all vertices have an even degree).";
        } else if (odd_degree_const == 2) {
            return "This graph has an Eulerian path (exactly two vertices have an odd degree).";
        } else { return "No Eulerian path or circuit exists."; }
    }
};

// Runs test cases to validate the graph logic
void run_tests() {
    std::vector<std::pair<std::string, std::vector<std::pair<char, char>>>> test_cases = {
        {"Konigsberg Bridges", {
            {'A', 'B'}, {'A', 'B'}, {'A', 'C'},
            {'A', 'D'}, {'C', 'B'}, {'C', 'D'},
            {'B', 'D'}
            }},
        {"Eulerian Path (2 odd-degree vertices)", {
            {'A', 'B'}, {'A', 'C'}, {'B', 'C'}
            }},
        {"Eulerian Circuit (All even-degree vertices)", {
            {'A', 'B'}, {'B', 'C'}, {'C', 'A'}
            }},
        {"No Eulerian Path or Circuit (3 odd-degree vertices)", {
            {'A', 'B'}, {'A', 'C'}, {'A', 'D'}
            }}
    };

    for (const auto& [name, bridges] : test_cases) {
        std::cout << "Test Case: " << name << "\n";
        Graph graph(bridges);
        std::cout << "Result: " << '\n' << graph.analyze_elerian() << "\n";
    }
}

int main() {
    std::cout << "Analyzing the Bridges of Konigsberg problem..\n";
    run_tests();
    return 0;
}