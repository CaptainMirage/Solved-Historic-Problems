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

Dev Notes:
---------
finally updated the code to have test cases, no comments for you tho
*/
#include <iostream>
using namespace std;

class solution {
public:
    static int josephus_prob(const int n, const int k) {
        if (n == 1) {return 0;}
        return (josephus_prob(n - 1, k) + k) % n;
    }
    
    static void test_cases(int test_number, int k, int length, int expected) {
        int actual = josephus_prob(length, k) + 1;
        
        printf("\nTest #%d debug :\n", test_number);
        printf("Expected result = %d\n", expected);
        printf("actual result = %d\n", actual);

        if (actual == expected) {
            printf("Test %d passed: k=%d, length=%d\n", test_number, k, length);
        } else {
            printf("Test %d failed: k=%d, length=%d\n", test_number, k, length);
        }
    }
};
int main() {
    solution::test_cases(1, 3, 42, 34);
    solution::test_cases(2, 1, 5, 5);
    solution::test_cases(3, 3, 15, 5);
    
    constexpr int n = 41;
    constexpr int k = 3;
    int survivor = solution::josephus_prob(n, k) + 1;
    printf("\nThe survivor is at position: %d", survivor);
}