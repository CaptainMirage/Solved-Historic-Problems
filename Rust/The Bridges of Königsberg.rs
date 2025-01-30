/*
Problem Description:
-----------------
The Bridges of Königsberg problem asks whether it is possible to walk through the city
of Königsberg crossing each of its seven bridges exactly once and returning to the
starting point. The city had seven bridges connecting two islands and the mainland,
forming a complex network that challenged mathematicians of the time.

In graph theory terms, the problem can be modeled as an undirected graph, where:
- Landmasses are represented as vertices (nodes)
- Bridges are represented as edges (connections between nodes)

The goal is to determine if an Eulerian circuit (a path that visits every edge exactly once
and returns to the starting point) or an Eulerian path (a path that visits every edge once
but doesn't necessarily return to the starting point) exists.

Historical Context:
----------------
In 1736, the mathematician Leonhard Euler analyzed the problem and proved that no solution
exists for the original bridge configuration. His findings introduced the concept of
Eulerian paths and circuits, establishing a foundation for graph theory.

Euler's theorem states that:
- An Eulerian circuit exists if all vertices have an even degree.
- An Eulerian path exists if exactly 0 or 2 vertices have an odd degree.

Dev Notes:
---------
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
it's not done stfu
i will have to add some more stuff to it
 */

 use std::collections::HashMap;

 /// Represents a graph structure using adjacency list
 struct Graph {
     adjacency_list: HashMap<char, Vec<char>>,
 }
 
 impl Graph {
     /// Creates a new graph with given edges
     fn new(edges: &[(char, char)]) -> Self {
         let mut adjacency_list = HashMap::new();
 
         for &(u, v) in edges {
             adjacency_list.entry(u).or_insert(vec![]).push(v);
             adjacency_list.entry(v).or_insert(vec![]).push(u);
         }
 
         Graph { adjacency_list }
     }
 
     /// Determines the degree of each node and checks for Eulerian path or circuit
     fn analyze_eulerian(&self) -> String {
         let mut odd_degree_count = 0;
 
         for (node, neighbors) in &self.adjacency_list {
             let degree = neighbors.len();
             println!("Vertex {} has degree {}", node, degree);
 
             if degree % 2 != 0 {
                 odd_degree_count += 1;
             }
         }
 
         match odd_degree_count {
             0 => "This graph has an Eulerian circuit (all vertices have an even degree).".to_string(),
             2 => "This graph has an Eulerian path (exactly two vertices have an odd degree).".to_string(),
             _ => "No Eulerian path or circuit exists.".to_string(),
         }
     }
 }
 
 /// Runs test cases to validate the graph logic
 fn run_tests() {
     let test_cases = vec![
         ("Königsberg Bridges", vec![
             ('A', 'B'), ('A', 'B'), ('A', 'C'),
             ('A', 'D'), ('C', 'B'), ('C', 'D'),
             ('B', 'D')
         ]),
         ("Eulerian Path (2 odd-degree vertices)", vec![
             ('A', 'B'), ('A', 'C'), ('B', 'C')
         ]),
         ("Eulerian Circuit (All even-degree vertices)", vec![
             ('A', 'B'), ('B', 'C'), ('C', 'A')
         ]),
         ("No Eulerian Path or Circuit (3 odd-degree vertices)", vec![
             ('A', 'B'), ('A', 'C'), ('A', 'D')
         ])
     ];
 
     for (name, bridges) in test_cases {
         println!("\nTest Case: {}", name);
         let graph = Graph::new(&bridges);
         let result = graph.analyze_eulerian();
         println!("Result: {}", result);
     }
 }
 
 fn main() {
     println!("Analyzing the Bridges of Königsberg problem..");
     run_tests();
 }
 