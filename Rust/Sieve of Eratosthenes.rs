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
nothing much to say
*/

pub struct Sieve {
    limit: usize,
    primes: Vec<bool>,
}

impl Sieve {
    pub fn new(limit: usize) -> Sieve {
        // Initialize all numbers as prime
        let mut primes = vec![true; limit + 1];

        // 0 and 1 are not prime
        if limit >= 1 {
            primes[0] = false;
            primes[1] = false;
        }

        // Apply sieve
        let sqrt_limit = (limit as f64).sqrt() as usize;
        for i in 2..=sqrt_limit {
            if primes[i] {
                // Mark multiples as non-prime
                let mut j = i * i;
                while j <= limit {
                    primes[j] = false;
                    j += i;
                }
            }
        }

        Sieve { limit, primes }
    }

    pub fn get_primes(&self) -> Vec<usize> {
        (2..=self.limit)
            .filter(|&i| self.primes[i])
            .collect()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_small_number() {
        let sieve = Sieve::new(10);
        assert_eq!(sieve.get_primes(), vec![2, 3, 5, 7]);
    }

    #[test]
    fn test_with_square() {
        let sieve = Sieve::new(25);
        assert_eq!(sieve.get_primes(), vec![2, 3, 5, 7, 11, 13, 17, 19, 23]);
    }

    #[test]
    fn test_minimal() {
        let sieve = Sieve::new(2);
        assert_eq!(sieve.get_primes(), vec![2]);
    }

    #[test]
    fn test_edge_case() {
        let sieve = Sieve::new(1);
        assert_eq!(sieve.get_primes(), Vec::<usize>::new());
    }
}

fn main() {
    // Example usage
    let sieve = Sieve::new(100000);
    println!("Prime numbers up to 30: {:?}", sieve.get_primes());
}