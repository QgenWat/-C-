#include <iostream>
#include <vector>
#include <algorithm>

void splitPositiveNegative(const std::vector<int>& original, std::vector<int>& positive, std::vector<int>& negative) {
    for (int num : original) {
        if (num >= 0) {
            positive.push_back(num);
        } else {
            negative.push_back(num);
        }
    }
    std::sort(positive.begin(), positive.end());
    std::sort(negative.begin(), negative.end());
}

int main() {
    std::vector<int> original = {3, -2, 5, -1, 0, 4, -3};
    std::vector<int> positive, negative;

    splitPositiveNegative(original, positive, negative);

    std::cout << "Неотрицательные числа: ";
    for (int num : positive) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "Отрицательные числа: ";
    for (int num : negative) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
