#include <iostream>
#include <vector>
#include <string>

template <typename Container>
void Print(const Container& container, const std::string& delimiter) {
    auto it = container.begin();
    if (it != container.end()) {
        std::cout << *it;
        ++it;
    }
    for (; it != container.end(); ++it) {
        std::cout << delimiter << *it;
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> data = {1, 2, 3};
    Print(data, ", ");

    std::vector<std::string> words = {"яблоко", "апельсин", "банан"};
    Print(words, " ");  

    return 0;
}
