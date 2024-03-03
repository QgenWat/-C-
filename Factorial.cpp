#include <iostream>
#include <vector>

void printFactorialRepresentation(int n) {
    std::vector<int> factorialDigits;

    int factorial = 1;
    while (n > 0) {
        factorialDigits.push_back(n % (factorial + 1));
        n /= (factorial + 1);
        factorial++;
    }

    for (int i = factorialDigits.size() - 1; i >= 0; i--) {
        std::cout << factorialDigits[i];
        if (i > 0) {
            std::cout << ".";
        }
    }
}

int main() {
    int number = 17;
    printFactorialRepresentation(number);
    std::cout << std::endl;

    number = 196;
    printFactorialRepresentation(number);
    std::cout << std::endl;

    number = 7394;
    printFactorialRepresentation(number);
    std::cout << std::endl;

    return 0;
}
