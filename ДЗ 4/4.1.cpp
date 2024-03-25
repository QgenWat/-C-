#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>

std::random_device rd;
std::mt19937 gen(rd());

int generateRandomNumber(int min, int max) {
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

void fillContainerWithRandomNumbers(std::vector<int>& container, int size) {
    for (int i = 0; i < size; ++i) {
        container.push_back(generateRandomNumber(0, 10000));
    }
}

void bubbleSort(std::vector<int>& container) {
    int n = container.size();
    for (int i = 0; i < n-1; ++i) {
        for (int j = 0; j < n-i-1; ++j) {
            if (container[j] > container[j+1]) {
                std::swap(container[j], container[j+1]);
            }
        }
    }
}

void quickSort(std::vector<int>& container, int low, int high) {
    if (low < high) {
        int pivot = container[high];
        int i = low - 1;
        for (int j = low; j <= high - 1; ++j) {
            if (container[j] < pivot) {
                ++i;
                std::swap(container[i], container[j]);
            }
        }
        std::swap(container[i + 1], container[high]);
        int partitionIndex = i + 1;
        quickSort(container, low, partitionIndex - 1);
        quickSort(container, partitionIndex + 1, high);
    }
}

int main() {
    const int SIZE = 10000;
    std::vector<int> container;

    fillContainerWithRandomNumbers(container, SIZE);

    auto startBubbleSort = std::chrono::steady_clock::now();
    bubbleSort(container);
    auto endBubbleSort = std::chrono::steady_clock::now();
    std::chrono::duration<double> bubbleSortTime = endBubbleSort - startBubbleSort;

    fillContainerWithRandomNumbers(container, SIZE);

    auto startQuickSort = std::chrono::steady_clock::now();
    quickSort(container, 0, SIZE - 1);
    auto endQuickSort = std::chrono::steady_clock::now();
    std::chrono::duration<double> quickSortTime = endQuickSort - startQuickSort;

    std::cout << "Время выполнения сортировки пузырьком: " << bubbleSortTime.count() << " секунд\n";
    std::cout << "Время выполнения быстрой сортировки: " << quickSortTime.count() << " секунд\n";

    if (bubbleSortTime < quickSortTime) {
        std::cout << "Сортировка пузырьком быстрее.\n";
    } else {
        std::cout << "Быстрая сортировка быстрее.\n";
    }

    return 0;
}
