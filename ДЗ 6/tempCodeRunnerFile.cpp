#include <iostream>
#include <thread>
#include <mutex>

const int NUM_PHILOSOPHERS = 5;
std::mutex forks[NUM_PHILOSOPHERS];

void philosopher(int id) {
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;

    while (true) {
        // Философ размышляет
        std::cout << "Philosopher " << id << " is thinking." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        // Философ голоден и пытается взять вилки
        std::unique_lock<std::mutex> left_lock(forks[left_fork]);
        std::unique_lock<std::mutex> right_lock(forks[right_fork]);

        // Философ ест
        std::cout << "Philosopher " << id << " is eating." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        // Философ возвращает вилки на стол
        right_lock.unlock();
        left_lock.unlock();
    }
}

int main() {
    std::thread philosophers[NUM_PHILOSOPHERS];

    // Создание потоков для каждого философа
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers[i] = std::thread(philosopher, i);
    }

    // Ожидание завершения работы каждого потока
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers[i].join();
    }

    return 0;
}
