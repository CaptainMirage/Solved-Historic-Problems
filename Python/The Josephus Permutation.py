"""
Problem Description:
-----------------
The Josephus Problem (or Josephus Permutation) is a theoretical counting-out game where n people 
are standing in a circle waiting to be eliminated. Starting from a specified point, you count off 
a certain number of people k and eliminate the kth person. The process is repeated with the 
remaining people, starting from the next person, going in the same direction and counting the 
same number of people, until only one person remains.

Historical Context:
----------------
The problem is named after Flavius Josephus, a Jewish historian from the 1st century. According
to legend, Josephus and 40 of his soldiers were trapped in a cave by Roman soldiers during the
Siege of Yodfat. They chose suicide over capture and decided to form a circle and kill every
third person until no one was left. Josephus, not wanting to die, quickly calculated where he
should stand to be the last survivor.

Implementation Notes:
------------------
Two solutions are provided:
1. Fast solution using collections.deque - O(n) time complexity
2. Slow solution using list operations - O(n²) time complexity
"""

# built-in libraries
from collections import deque
from time import perf_counter
from typing import List, Union

def fast_solution(array: List[Union[int, str]], k: int) -> List[Union[int, str]]:
    """
    Fast implementation of Josephus Permutation using deque.
    Time Complexity: O(n) where n is the length of the input array
    Space Complexity: O(n) for storing the result
    
    Args:
        array: List of elements to permute
        k: Skip value for the permutation (every kth person is eliminated)
    
    Returns:
        List containing the order of eliminations (Josephus permutation)
    """
    deck = deque(array)
    permutation = []

    while deck:
        deck.rotate(1 - k)  # Rotate k-1 positions counterclockwise
        item = deck.popleft()
        permutation.append(item)

    return permutation

def slow_solution(array: List[Union[int, str]], k: int) -> List[Union[int, str]]:
    """
    Traditional implementation of Josephus Permutation using list operations.
    Time Complexity: O(n²) where n is the length of the input array
    Space Complexity: O(n) for storing the result
    
    Args:
        array: List of elements to permute
        k: Skip value for the permutation (every kth person is eliminated)
    
    Returns:
        List containing the order of eliminations (Josephus permutation)
    """
    permutation = []
    index = 0

    while array:
        index = (index + k - 1) % len(array)
        item = array.pop(index)
        permutation.append(item)

    return permutation

def run_test_cases():
    """
    Comprehensive test cases for verifying the Josephus Permutation implementations.
    Includes edge cases and historical examples.
    """
    test_cases = [
        # Test case 1: Basic case (n=7, k=3)
        {"array": list(range(1, 8)), "k": 3, "expected": [3, 6, 2, 7, 5, 1, 4]},
        
        # Test case 2: Edge case - single element
        {"array": [1], "k": 3, "expected": [1]},
        
        # Test case 3: Edge case - k=1 (sequential elimination)
        {"array": list(range(1, 5)), "k": 1, "expected": [1, 2, 3, 4]},
        
        # Test case 4: Historical case (Josephus with 41 soldiers, k=3)
        {"array": list(range(1, 42)), "k": 3, "expected": None},  # Expected value omitted for brevity
        
        # Test case 5: Edge case - k equals array length
        {"array": list(range(1, 6)), "k": 5, "expected": [5, 4, 3, 2, 1]}
    ]

    for i, test in enumerate(test_cases, 1):
        fast_result = fast_solution(test["array"].copy(), test["k"])
        slow_result = slow_solution(test["array"].copy(), test["k"])
        
        # Verify both implementations produce same result
        assert fast_result == slow_result, f"Test {i}: Implementations produced different results"
        
        # Check against expected result if provided
        if test["expected"]:
            assert fast_result == test["expected"], f"Test {i}: Incorrect result"
        
        print(f"Test {i} passed: k={test['k']}, length={len(test['array'])}")

def benchmark_solutions(n: int, k: int) -> None:
    """
    Benchmark both solutions with given parameters.
    
    Args:
        n: Number of elements
        k: Skip value for the permutation
    """
    # Prepare test arrays
    fast_array = [i + 1 for i in range(n)]
    slow_array = [i + 1 for i in range(n)]
    
    # Test fast solution
    start_fast = perf_counter()
    fast_result = fast_solution(fast_array, k)
    time_fast = perf_counter() - start_fast
    
    # Test slow solution
    start_slow = perf_counter()
    slow_result = slow_solution(slow_array, k)
    time_slow = perf_counter() - start_slow
    
    print(f"\nPerformance Comparison (n={n:,}, k={k}):")
    print(f"Fast solution took: {time_fast:.6f} seconds")
    print(f"Slow solution took: {time_slow:.6f} seconds")
    print(f"Speed difference: {time_slow/time_fast:.2f}x")

if __name__ == "__main__":
    # Run test cases
    print("Running test cases...")
    run_test_cases()
    
    # Run performance benchmark
    print("\nRunning performance benchmark...")
    benchmark_solutions(1_000_000, 3)