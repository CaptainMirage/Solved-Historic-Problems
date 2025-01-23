/* 
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
the default implementation is for the actual situation josephus was in
this is a mathematical way of doing it, you could simulate it, but it would take too long
*/

fn josephus_recursive(n: usize, k: usize) -> usize {
    if n == 1 {
        0  // Base case: the last person standing (0-indexed)
    } else {
        (josephus_recursive(n - 1, k) + k) % n
    }
}

fn run_test(test_number: usize, k: usize, length: usize, expected: usize) {
    let actual = josephus_recursive(length, k) + 1;

    println!("\nTest {} debug:", test_number);
    println!("Expected result: {:?}", expected);
    println!("Actual result:   {:?}", actual);

    if actual == expected {
        println!("Test {} passed: k={}, length={}", test_number, k, length);
    } else {
        println!("Test {} failed: k={}, length={}", test_number, k, length);
    }
}


fn main() {
    run_test(1, 3, 15, 5);
    run_test(2, 1, 5, 5);
    run_test(3, 3, 42, 34);
    
    let n = 41; // number of ppl standing in the circle
    let k = 3; // k-th person is eliminated each round
    let survivor = josephus_recursive(n, k) + 1;  // Convert to 1-based index
    println!("\nThe survivor is at position: {}", survivor);
}
