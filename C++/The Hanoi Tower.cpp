// ReSharper disable All
/*
 * Problem Description:
 * -------------------
 * The Hanoi Tower is a mathematical puzzle involving three pegs and a set of disks of different sizes.
 * The objective is to move an entire stack of disks from one peg to another, following these strict rules:
 * 1. Only one disk can be moved at a time
 * 2. Each disk is moved from one peg to another
 * 3. No larger disk can be placed on top of a smaller disk
 * The minimum number of moves required is 2^n - 1, where n is the number of disks.
 *
 * Historical Context:
 * ------------------
 * The problem was first introduced by French mathematician Édouard Lucas in 1883.
 * Lucas was inspired by a fictional legend of a temple in Hanoi, Vietnam, where monks move 64 golden disks 
 * between three pegs, following the same rules. According to the legend, when the monks complete 
 * moving all 64 disks, the world will end. This mythical puzzle would require 2^64 - 1 moves, 
 * which would take approximately 585 billion years to complete.
 */


#include <iostream>
using namespace std;

class solution {
    public:
    static void hanoi_tower(int n, char source, char auxiliary, char destination) {
        // Base case: if only one disk, move directly
        if (n == 1) {
            std::cout << "Move disk 1 from {} to {}" << '\n';
            return;
        }
        // 1. Move n-1 disks from source to auxiliary
        hanoi_tower(n - 1, source, destination, auxiliary);

        // 2. Move the nth disk from source to destination
        std::cout << "Move disk 1 from {} to {}" << '\n';

        // 3. Move n-1 disks from auxiliary to destination
        hanoi_tower(n - 1, auxiliary, source, destination);
    }
};

int main(int argc, char* argv[]) {
    // set the disks amount
    int n = 12;
    solution::hanoi_tower(n, // amount of disks
                          'A', // source peg
                          'B', // axiliary peg
                          'C'); // destination peg
}
