#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <numeric>

int random_int(int min, int max) {
    return min + rand() % (max - min + 1);
}

void find_top_three( std::vector<int>& arr, std::vector<int>& top_three, int start, int end) {
    std::vector<int> local_arr(arr.begin() + start, arr.begin() + end);
    std::partial_sort(local_arr.begin(), local_arr.begin() + 3, local_arr.end(), std::greater<int>());
    for (int i = 0; i < 3; ++i) {
        if (local_arr[i] > top_three[0]) {
            top_three[2] = top_three[1];
            top_three[1] = top_three[0];
            top_three[0] = local_arr[i];
        } else if (local_arr[i] > top_three[1]) {
            top_three[2] = top_three[1];
            top_three[1] = local_arr[i];
        } else if (local_arr[i] > top_three[2]) {
            top_three[2] = local_arr[i];
        }
    }
}

int main() {
    int size = 20;
    int num_threads = 4;

    std::vector<int> arr(size);
    std::vector<int> top_three(3, INT_MIN);

    srand(time(0));
    std::cout << "Исходный массив:\n";
    for (int i = 0; i < size; ++i) {
        arr[i] = random_int(1, 1000);
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        int start = i * (size / num_threads);
        int end = (i + 1) * (size / num_threads);
        if (i == num_threads - 1) {
            end = size;
        }
        threads.emplace_back(find_top_three, std::ref(arr), std::ref(top_three), start, end);
    }

    for (auto& t : threads) {
        t.join();
    }

    int sum = std::accumulate(top_three.begin(), top_three.end(), 0);
    std::cout << "Сумма трех самых больших элементов: " << sum << std::endl;

    return 0;
}
