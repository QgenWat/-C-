#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

const int NUM_PHILOSOPHERS = 5;
std::vector<std::mutex> forks(NUM_PHILOSOPHERS);
std::mutex print_mutex;

void philosopher(int id) {
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;

    while (true) {
        {
            std::lock_guard<std::mutex> guard(print_mutex);
            std::cout << "Философ №" << id+1 << " думает." << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        {
            std::unique_lock<std::mutex> left_lock(forks[left_fork], std::defer_lock);
            std::unique_lock<std::mutex> right_lock(forks[right_fork], std::defer_lock);
            std::lock(left_lock, right_lock);
            {
                std::lock_guard<std::mutex> guard(print_mutex);
                std::cout << "Филосов №" << id+1 << " кушает." << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        {
            std::lock_guard<std::mutex> guard(print_mutex);
            std::cout << "Философ №" << id+1 << " кладет вилки." << std::endl;
        }
    }
}

int main() {
    std::vector<std::thread> philosophers(NUM_PHILOSOPHERS);
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers[i] = std::thread(philosopher, i);
    }
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers[i].join();
    }

    return 0;
}
