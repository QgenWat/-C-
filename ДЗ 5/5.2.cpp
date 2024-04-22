#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>

int random_int(int min, int max) {
    return min + rand() % (max - min + 1);
}

void sortPart(std::vector<int>& arr, int start, int end) {
    std::sort(arr.begin() + start, arr.begin() + end);
}

void merge(std::vector<int>& arr, int start, int mid, int end) {
    std::vector<int> temp(end - start);
    int i = start, j = mid, k = 0;

    while (i < mid && j < end) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i < mid) {
        temp[k++] = arr[i++];
    }

    while (j < end) {
        temp[k++] = arr[j++];
    }

    for (int p = 0; p < k; p++) {
        arr[start + p] = temp[p];
    }
}

void parallelSort(std::vector<int>& arr, int numThreads) {
    int size = arr.size();
    int partSize = size / numThreads;

    std::vector<std::thread> threads;

    for (int i = 0; i < numThreads - 1; i++) {
        threads.emplace_back(sortPart, std::ref(arr), i * partSize, (i + 1) * partSize);
    }

    threads.emplace_back(sortPart, std::ref(arr), (numThreads - 1) * partSize, size);

    for (auto& thread : threads) {
        thread.join();
    }

    for (int mergeSize = partSize; mergeSize < size; mergeSize *= 2) {
        for (int i = 0; i < size - mergeSize; i += 2 * mergeSize) {
            int start = i;
            int mid = i + mergeSize;
            int end = i + 2 * mergeSize;

            if (end > size) {
                end = size;
            }

            merge(arr, start, mid, end);
        }
    }
}

int main() {
    int size = 20;
    int numThreads = 4;

    std::vector<int> arr(size);

    srand(time(0));
    std::cout << "Исходный массив:\n";
    for (int i = 0; i < size; ++i) {
        arr[i] = random_int(1, 1000);
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    parallelSort(arr, numThreads);

    std::cout << "Отсортированный массив:\n";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
