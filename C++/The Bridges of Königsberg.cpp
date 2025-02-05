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
work in progress
*/

#include <unordered_map>
#include <vector>
#include <utility>

class Graph {
private:
    // Equivalent to Rust's HashMap<char, Vec<char>>
    std::unordered_map<char, std::vector<char>> adjacency_list;

public:
    // Default constructor
    Graph() = default;

    // Constructor from vector of edges (equivalent to Rust's new function)
    Graph(const std::vector<std::pair<char, char>>& edges) {
        for (const auto& [u, v] : edges) {
            // Add edge in both directions for undirected graph
            adjacency_list[u].push_back(v);
            adjacency_list[v].push_back(u);
        }
    }

    // Alternative constructor using iterator range
    template<typename Iterator>
    Graph(Iterator begin, Iterator end) {
        for (auto it = begin; it != end; ++it) {
            const char u = it->first;
            const char v = it->second;
            adjacency_list[u].push_back(v);
            adjacency_list[v].push_back(u);
        }
    }

    // Getter for adjacency list (useful for testing and verification)
    const std::unordered_map<char, std::vector<char>>& get_adjacency_list() const {
        return adjacency_list;
    }
};
