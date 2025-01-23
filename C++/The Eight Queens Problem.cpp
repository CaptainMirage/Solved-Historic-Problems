/* 
Problem Description:
-----------------
The Eight Queens Problem is a classic chess puzzle challenging players to place 8 queens 
on a standard 8x8 chessboard such that no two queens can attack each other. This means 
no two queens can share the same row, column, or diagonal, requiring a precise 
arrangement that prevents any queen from threatening another.

Historical Context:
----------------
First posed by chess composer Max Bezzel in 1848, the Eight Queens Problem quickly 
became a significant challenge in combinatorial mathematics. It gained prominence as 
a classic example of backtracking algorithms and constraint satisfaction problems, 
attracting mathematicians and computer scientists for over a century.
*/

#include <iostream>
#include <vector>
#include <cassert>

class EightQueens {
private:
    std::vector<std::vector<int>> solutions;

    // Check if a queen can be placed on board[row][col]
    static bool isSafe(const std::vector<int>& board, int row, int col) {
        // Check this row on left side
        for (int i = 0; i < col; i++) {
            if (board[i] == row) return false;
        }
        
        // Check upper diagonal on left side
        for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
            if (board[j] == i) return false;
        }
        
        // Check lower diagonal on left side
        for (int i = row, j = col; j >= 0 && i < 8; i++, j--) {
            if (board[j] == i) return false;
        }
        
        return true;
    }

    // Recursive backtracking solver
    void solveNQueens(std::vector<int>& board, int col) {
        // Base case: If all queens are placed, save the solution
        if (col >= 8) {
            solutions.push_back(board);
            return;
        }
        
        // Consider this column and try placing this queen in all rows one by one
        for (int i = 0; i < 8; i++) {
            // Check if queen can be placed on board[i][col]
            if (isSafe(board, i, col)) {
                // Place this queen in board[i][col]
                board[col] = i;
                
                // Recur to place rest of the queens
                solveNQueens(board, col + 1);
                
                // If placing queen in board[i][col] doesn't lead to a solution,
                // then remove queen from board[i][col]
                board[col] = -1;
            }
        }
    }

public:
    // Constructor to solve the problem
    EightQueens() {
        std::vector<int> board(8, -1);
        solveNQueens(board, 0);
    }
    
    // Get total number of solutions
    int getSolutionCount() const {
        return static_cast<int>(solutions.size());
    }
    
    // Print all solutions
    void printSolutions() const {
        for (const auto& solution : solutions) {
            printBoard(solution);
            std::cout << "\n";
        }
    }
    
    // Print a single board configuration
    static void printBoard(const std::vector<int>& solution)
    {
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                if (solution[col] == row) {
                    std::cout << "Q ";
                } else {
                    std::cout << ". ";
                }
            }
            std::cout << "\n";
        }
    }
    
    // Get all solutions
    const std::vector<std::vector<int>>& getSolutions() const {
        return solutions;
    }
};

namespace {
    // Unit tests in anonymous namespace
    void runTests() {
        EightQueens queens;
        
        // Test: Verify number of solutions
        assert(queens.getSolutionCount() == 92);
        
        // Test: Verify solution uniqueness
        const auto& solutions = queens.getSolutions();
        for (size_t i = 0; i < solutions.size(); ++i) {
            for (size_t j = i + 1; j < solutions.size(); ++j) {
                assert(solutions[i] != solutions[j]);
            }
        }
        
        std::cout << "All tests passed!" << '\n';
    }
}

int main() {
    EightQueens queens;
    
    // Print solution count
    std::cout << "Total solutions: " << queens.getSolutionCount() << '\n';
    
    // Print first few solutions
    queens.printSolutions();
    
    // Run tests
    runTests();
    
    return 0;
}