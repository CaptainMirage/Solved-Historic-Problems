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
im too lazy to add anything else at the moment so deal with it :D
*/
#include <iostream>
using namespace std;

class solution {
public:
    static int josephus_prob(const int n, const int k) {
        if (n == 1) {return 0;}
        return (josephus_prob(n - 1, k) + k) % n;
    }
};
int main() {
    constexpr int n = 5;
    constexpr int k = 2;
    std::cout << solution::josephus_prob(n, k) + 1;
}