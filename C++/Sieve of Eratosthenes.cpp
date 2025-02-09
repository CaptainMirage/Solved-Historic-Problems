/*
Problem Description:
-----------------
The Sieve of Eratosthenes is an ancient algorithm for finding all prime numbers up to 
a given limit n. It works by iteratively marking the multiples of each prime number as 
composite, starting from 2. The numbers that remain unmarked are prime numbers.
The algorithm is particularly efficient for finding all primes up to a moderate size limit.

Historical Context:
----------------
Named after Eratosthenes of Cyrene (276-194 BC), a Greek mathematician, astronomer, and
geographer who served as chief librarian at the Library of Alexandria. This algorithm
was one of his most significant contributions to mathematics, demonstrating an elegant
and systematic approach to identifying prime numbers. It remained the most efficient
known method for finding primes until the development of modern computing algorithms
in the 20th century.

Dev Note:
---------
i would add a starting limit and an ending limit but its meant to be an answer for the problem
and i also cant be bothered :D
work in progress
*/
#include <iostream>
#include <vector>

struct Sieve_struct {
    size_t limit;
    std::vector<bool> primes;
};

class Sieve {
    public:
    static Sieve_struct initialize(size_t limit) {
        std::vector<bool> primes = std::vector<bool>(limit + 1, true);

        if (limit >= 1) {
            primes[0] = false;
            primes[1] = false;
        }

        int sqrt_limit = sqrt(limit);
        for (int i = 2; i <= sqrt_limit; i++) {
            if (primes[i]) {
                for (int j = i * i; j <= limit; j += i) {
                    primes[j] = false;
                }
            }
        }

        return Sieve_struct{limit, primes}; 
    }

    static std::vector<size_t> get_primes(const Sieve_struct& sieve) {
        std::vector<size_t> prime_nums;
        for (size_t i = 0; i < sieve.limit; i++) {
            if (sieve.primes[i]) {
                prime_nums.push_back(i);
            }
        }
        return prime_nums;
    }
};

int main() {
    int limit = 30;
    Sieve_struct sieve = Sieve::initialize(limit);
    std::vector<size_t> primes = Sieve::get_primes(sieve);
    
    std::cout << "Prime numbers up to " << limit << ": ";
    for (const auto& prime : primes) {
        std::cout << prime << " ";
    }
    std::cout << std::endl;
    
    return 0;
}