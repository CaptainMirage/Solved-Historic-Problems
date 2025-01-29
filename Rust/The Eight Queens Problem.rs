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

Dev Notes:
---------
i just translated the cpp version
to test the code, for now its with the test profile (cargo run --test)
*/
#[allow(unused_imports)]
use std::collections::HashSet;

/// Eight Queens solver struct
pub struct EightQueens {
    solutions: Vec<Vec<usize>>,
}

impl EightQueens {
    /// Create a new Eight Queens solver
    pub fn new() -> Self {
        Self { solutions: Vec::new() }
    }

    /// Solve the Eight Queens Problem
    pub fn solve(&mut self) -> &Vec<Vec<usize>> {
        let mut current_solution = vec![];
        self.backtrack(&mut current_solution);
        &self.solutions
    }

    /// Backtracking algorithm to find all valid queen placements
    fn backtrack(&mut self, current_solution: &mut Vec<usize>) {
        // Base case: we have a complete solution
        if current_solution.len() == 8 {
            self.solutions.push(current_solution.clone());
            return;
        }

        // Try placing a queen in each column of the current row
        for col in 0..8 {
            if self.is_safe(current_solution, col) {
                current_solution.push(col);
                self.backtrack(current_solution);
                current_solution.pop();
            }
        }
    }

    /// Check if placing a queen in the current column is safe
    fn is_safe(&self, current_solution: &[usize], col: usize) -> bool {
        let row = current_solution.len();

        // Check column conflicts and diagonal conflicts
        for (prev_row, &prev_col) in current_solution.iter().enumerate() {
            // Same column check
            if prev_col == col {
                return false;
            }

            // Diagonal conflict check
            let col_diff = (col as i32 - prev_col as i32).abs();
            let row_diff = row as i32 - prev_row as i32;
            if col_diff == row_diff {
                return false;
            }
        }

        true
    }

    /// Count the total number of solutions
    pub fn count_solutions(&self) -> usize {
        self.solutions.len()
    }

    /// Pretty print solutions
    pub fn print_solutions(&self) {
        for (idx, solution) in self.solutions.iter().enumerate() {
            println!("Solution #{}:", idx + 1);
            self.print_board(solution);
            println!();
        }
    }

    /// Visualize a solution on a text-based chessboard
    fn print_board(&self, solution: &[usize]) {
        for row in 0..8 {
            for col in 0..8 {
                if solution[row] == col {
                    print!("Q ");
                } else {
                    print!(". ");
                }
            }
            println!();
        }
    }
}

/// Test cases for Eight Queens Problem
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_eight_queens_solution_count() {
        let mut queens = EightQueens::new();
        queens.solve();

        // Verify the number of solutions (known to be 92 unique solutions)
        assert_eq!(queens.count_solutions(), 92);
    }

    #[test]
    fn test_solution_validity() {
        let mut queens = EightQueens::new();
        queens.solve();

        // Verify each solution is unique and valid
        let unique_solutions: HashSet<Vec<usize>> = queens.solutions.iter().cloned().collect();
        assert_eq!(unique_solutions.len(), 92);
    }

    #[test]
    fn test_solution_constraints() {
        let mut queens = EightQueens::new();
        queens.solve();

        for solution in &queens.solutions {
            // Verify each solution has 8 unique columns
            let unique_cols: HashSet<usize> = solution.iter().cloned().collect();
            assert_eq!(unique_cols.len(), 8, "Invalid solution with duplicate columns");

            // Verify no diagonal conflicts
            for (i, &col1) in solution.iter().enumerate() {
                for (j, &col2) in solution.iter().enumerate() {
                    if i != j {
                        let col_diff = (col1 as i32 - col2 as i32).abs();
                        let row_diff = (i as i32 - j as i32).abs();
                        assert_ne!(col_diff, row_diff, "Diagonal conflict found");
                    }
                }
            }
        }
    }
}

/// Example usage
fn main() {
    let mut queens = EightQueens::new();
    queens.solve();
    println!("Total solutions found: {}", queens.count_solutions());
    queens.print_solutions();
}