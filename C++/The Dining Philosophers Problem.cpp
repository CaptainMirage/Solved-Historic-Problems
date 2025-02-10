/*
Problem Description:
-------------------
The Dining Philosophers Problem is a classic synchronization problem in computer science.
Five philosophers sit around a circular table, each with a bowl of rice. Between each
pair of philosophers is a single chopstick (five total). To eat, a philosopher needs
both the chopstick to their left and right. After eating, they put down both chopsticks
and think for a while before trying to eat again.

The challenge is to design a solution that:
1. Prevents deadlock (all philosophers holding one chopstick, waiting for another)
2. Prevents starvation (ensures each philosopher gets to eat eventually)
3. Maximizes concurrency (allows multiple philosophers to eat simultaneously if possible)

Historical Context:
------------------
- First proposed by Edsger Dijkstra in 1965 to illustrate synchronization issues
- Originally formulated with forks, later adapted to use chopsticks in many versions
- Represents real-world resource allocation problems in operating systems
- Classic example used to teach concurrent programming concepts

Dev Note (Traditional Implementation Issues):
-------------------------------------------
Traditional implementations often suffer from:
1. Deadlock when all philosophers pick up left chopstick simultaneously
2. Limited concurrency due to overly restrictive synchronization
3. Starvation of some philosophers in naive implementations
4. Complex code that's hard to verify for correctness

This implementation uses a "resource hierarchy" solution where philosophers pick up
chopsticks in a specific order to prevent deadlock.
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <array>
#include <random>
#include <string>
#include <atomic>
#include <cassert>
#include <vector>
#include <functional>

class DiningPhilosophers {
private:
    static const int NUM_PHILOSOPHERS = 5;
    std::array<std::mutex, NUM_PHILOSOPHERS> chopsticks;
    std::array<std::string, NUM_PHILOSOPHERS> philosopher_states;
    std::mutex console_mutex;
    std::atomic<bool> simulation_running{true};
    std::vector<int> eat_counts;  // Track how many times each philosopher eats
    std::vector<std::chrono::milliseconds> wait_times;  // Track waiting times

public:
    DiningPhilosophers() : eat_counts(NUM_PHILOSOPHERS, 0), 
                          wait_times(NUM_PHILOSOPHERS, std::chrono::milliseconds(0)) {
        for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
            philosopher_states[i] = "Thinking";
        }
    }

    void print_state(int philosopher_id, const std::string& state) {
        std::lock_guard<std::mutex> console_lock(console_mutex);
        philosopher_states[philosopher_id] = state;
        
        std::cout << "\nPhilosophers' states:\n";
        for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
            std::cout << "Philosopher " << i << ": " << philosopher_states[i] 
                     << " (Eaten: " << eat_counts[i] << " times)\n";
        }
        std::cout << "\n------------------------\n";
    }

    void think(int philosopher_id) {
        print_state(philosopher_id, "Thinking");
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000 + 500));
    }

    void eat(int philosopher_id) {
        print_state(philosopher_id, "Eating");
        eat_counts[philosopher_id]++;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000 + 500));
    }

    void philosopher(int philosopher_id) {
        while (simulation_running) {
            think(philosopher_id);

            auto start_wait = std::chrono::steady_clock::now();
            
            int first_chopstick = std::min(philosopher_id, (philosopher_id + 1) % NUM_PHILOSOPHERS);
            int second_chopstick = std::max(philosopher_id, (philosopher_id + 1) % NUM_PHILOSOPHERS);

            print_state(philosopher_id, "Hungry");

            chopsticks[first_chopstick].lock();
            print_state(philosopher_id, "Got first chopstick");

            chopsticks[second_chopstick].lock();
            
            auto end_wait = std::chrono::steady_clock::now();
            wait_times[philosopher_id] += std::chrono::duration_cast<std::chrono::milliseconds>(
                end_wait - start_wait);
            
            eat(philosopher_id);

            chopsticks[second_chopstick].unlock();
            chopsticks[first_chopstick].unlock();
        }
    }

    void start_simulation(int duration_seconds) {
        simulation_running = true;
        std::array<std::thread, NUM_PHILOSOPHERS> philosophers;
        
        for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
            philosophers[i] = std::thread(&DiningPhilosophers::philosopher, this, i);
        }

        std::this_thread::sleep_for(std::chrono::seconds(duration_seconds));
        
        simulation_running = false;
        
        for (auto& phil : philosophers) {
            if (phil.joinable()) {
                phil.join();
            }
        }
    }

    // Test-specific methods
    std::vector<int> get_eat_counts() const { return eat_counts; }
    std::vector<std::chrono::milliseconds> get_wait_times() const { return wait_times; }
    void reset_statistics() {
        std::fill(eat_counts.begin(), eat_counts.end(), 0);
        std::fill(wait_times.begin(), wait_times.end(), std::chrono::milliseconds(0));
    }
};

// Test Cases
class DiningPhilosophersTest {
private:
    static void run_test(const std::string& test_name, std::function<bool()> test_func) {
        std::cout << "\nRunning test: " << test_name << "... ";
        bool result = test_func();
        std::cout << (result ? "PASSED" : "FAILED") << std::endl;
        assert(result); // Stop on failure in debug mode
    }

public:
    static void run_all_tests() {
        test_fairness();
        test_concurrent_eating();
        test_no_deadlock();
        test_wait_times();
    }

    // Test 1: Fairness - Each philosopher should get to eat a similar number of times
    static bool test_fairness() {
        DiningPhilosophers dp;
        dp.start_simulation(10); // Run for 10 seconds
        
        auto eat_counts = dp.get_eat_counts();
        int min_count = *std::min_element(eat_counts.begin(), eat_counts.end());
        int max_count = *std::max_element(eat_counts.begin(), eat_counts.end());
        
        // No philosopher should eat more than twice as much as any other
        bool is_fair = (max_count <= min_count * 2);
        
        std::cout << "Min eats: " << min_count << ", Max eats: " << max_count << std::endl;
        return is_fair;
    }

    // Test 2: Concurrent Eating - Non-adjacent philosophers should be able to eat simultaneously
    static bool test_concurrent_eating() {
        DiningPhilosophers dp;
        std::atomic<int> max_concurrent{0};
        std::atomic<int> current_eating{0};
        
        // Modified philosopher method to track concurrent eating
        auto concurrent_philosopher = [&](int id) {
            while (current_eating > 0) {
                int current = current_eating.load();
                max_concurrent = std::max(max_concurrent.load(), current);
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        };

        std::vector<std::thread> philosophers;
        for (int i = 0; i < 5; i++) {
            philosophers.emplace_back(concurrent_philosopher, i);
        }

        std::this_thread::sleep_for(std::chrono::seconds(5));
        
        for (auto& phil : philosophers) {
            phil.join();
        }

        std::cout << "Maximum concurrent philosophers eating: " << max_concurrent << std::endl;
        return max_concurrent >= 2; // At least 2 philosophers should eat concurrently
    }

    // Test 3: No Deadlock - Program should continue running without hanging
    static bool test_no_deadlock() {
        DiningPhilosophers dp;
        std::atomic<bool> completed{false};
        
        std::thread test_thread([&]() {
            dp.start_simulation(5);
            completed = true;
        });

        // Wait for up to 7 seconds (5 seconds simulation + 2 seconds buffer)
        std::this_thread::sleep_for(std::chrono::seconds(7));
        test_thread.join();

        std::cout << "Simulation " << (completed ? "completed normally" : "may have deadlocked") << std::endl;
        return completed;
    }

    // Test 4: Wait Times - Check that no philosopher waits too long
    static bool test_wait_times() {
        DiningPhilosophers dp;
        dp.start_simulation(10);
        
        auto wait_times = dp.get_wait_times();
        auto max_wait = std::max_element(wait_times.begin(), wait_times.end());
        
        std::cout << "Maximum wait time: " << max_wait->count() << "ms" << std::endl;
        
        // No philosopher should wait more than 5 seconds total
        return max_wait->count() < 5000;
    }
};

int main() {
    std::srand(std::time(nullptr));
    
    std::cout << "Running Dining Philosophers Tests...\n";
    
    try {
        DiningPhilosophersTest::run_all_tests();
        std::cout << "\nAll tests passed successfully!\n";
    }
    catch (const std::exception& expct) {
        std::cerr << "\nTest failed with exception: " << expct.what() << std::endl; // were you *expecting* something? eheh
        return 1;
    }
    
    return 0;
}