"""
The Eight Queens Problem
------------------------
Problem Description:
    Place eight chess queens on an 8x8 chessboard so that no two queens 
    threaten each other. Thus, a solution requires that no two queens 
    share the same row, column, or diagonal.

Historical Context:
    - First proposed by Max Bezzel in 1848
    - Franz Nauck published the first solutions in 1850
    - Gauss studied the problem and found 72 distinct solutions
    - The problem has 92 distinct solutions, considering rotations and reflections
    - It's a classic example of a constraint satisfaction problem in computer science

Implementation Strategy:
    - Uses backtracking algorithm
    - Time Complexity: O(n!)
    - Space Complexity: O(n^2)
"""

def is_safe(board, row, col, n):
    # Check row on left side
    for j in range(col):
        if board[row][j] == 1:
            return False
    
    # Check upper diagonal on left side
    for i, j in zip(range(row, -1, -1), range(col, -1, -1)):
        if board[i][j] == 1:
            return False
    
    # Check lower diagonal on left side
    for i, j in zip(range(row, n, 1), range(col, -1, -1)):
        if board[i][j] == 1:
            return False
    
    return True

def solve_n_queens(board, col, n):
    if col >= n:
        return True

    for i in range(n):
        if is_safe(board, i, col, n):
            board[i][col] = 1
            if solve_n_queens(board, col + 1, n):
                return True
            board[i][col] = 0

    return False

def print_solution(board):
    for row in board:
        print(" ".join(map(str, row)))

def eight_queens():
    n = 8
    board = [[0 for x in range(n)] for y in range(n)]
    
    if solve_n_queens(board, 0, n) == False:
        print("Solution does not exist")
        return False
    
    print("Solution found:")
    print_solution(board)
    return True

def find_all_solutions(n=8):
    """Find all possible solutions for n-queens problem."""
    solutions = []
    board = [[0 for x in range(n)] for y in range(n)]
    
    def save_solution(board):
        solution = []
        for row in board:
            solution.append(row.copy())
        solutions.append(solution)
    
    def solve_all(col):
        if col >= n:
            save_solution(board)
            return
        
        for i in range(n):
            if is_safe(board, i, col, n):
                board[i][col] = 1
                solve_all(col + 1)
                board[i][col] = 0
    
    solve_all(0)
    return solutions

def run_tests():
    """Test cases to verify the implementation."""
    # Test 1: Verify solution exists for 8 queens
    board = [[0 for x in range(8)] for y in range(8)]
    assert solve_n_queens(board, 0, 8) == True, "Test 1 Failed: No solution found for 8 queens"
    
    # Test 2: Verify number of solutions
    solutions = find_all_solutions(8)
    assert len(solutions) > 0, "Test 2 Failed: No solutions found"
    print(f"Found {len(solutions)} solutions")
    
    # Test 3: Verify solution validity
    for solution in solutions[:1]:  # Check first solution
        for i in range(8):
            row_sum = sum(solution[i])
            assert row_sum == 1, f"Test 3 Failed: Invalid row {i}"
    
    print("All tests passed successfully!")

if __name__ == "__main__":
    print("Running Eight Queens Problem solver...")
    eight_queens()
    print("\nRunning tests...")
    run_tests()

