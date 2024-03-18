#include <iostream>
#include <unordered_set>

int sumOfSquares(int n) {
    int sum = 0;
    while (n != 0) {
        int digit = n % 10;
        sum += digit * digit;
        n /= 10;
    }
    return sum;
}

bool isHappy(int n, std::unordered_set<int>& visited) {
    if (n == 1) {
        return true;
    }
    if (visited.find(n) != visited.end()) {
        return false;
    }
    visited.insert(n);
    return isHappy(sumOfSquares(n), visited);
}

bool isHappy(int n) {
    std::unordered_set<int> visited;
    return isHappy(n, visited);
}

int main() {
    int number = 19;
    if (isHappy(number)) {
        std::cout << number << " - счастливое число" << std::endl;
    } else {
        std::cout << number << " - не счастливое число" << std::endl;
    }

    number = 2;
    if (isHappy(number)) {
        std::cout << number << " - счастливое число" << std::endl;
    } else {
        std::cout << number << " - не счастливое число" << std::endl;
    }

    return 0;
}
