#include <iostream>
#include <chrono>
#include <random>
#include <set>
#include <map>

std::random_device rd;
std::mt19937 gen(rd());

int generateRandomNumber(int min, int max) {
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

void fillContainer(std::set<int>& container, int size) {
    while (container.size() < size) {
        container.insert(generateRandomNumber(0, 10000));
    }
}

void fillRedBlackTree(std::map<int, int>& redBlackTree, int size) {
    while (redBlackTree.size() < size) {
        int num = generateRandomNumber(0, 10000);
        redBlackTree[num] = num;
    }
}

int main() {
    const int SIZE = 500;
    std::set<int> containerSet;
    std::map<int, int> redBlackTree;

    fillContainer(containerSet, SIZE);
    fillRedBlackTree(redBlackTree, SIZE);

    auto startSetSearch = std::chrono::steady_clock::now();
    for (int i = 0; i < SIZE; ++i) {
        containerSet.find(generateRandomNumber(0, 10000));
    }
    auto endSetSearch = std::chrono::steady_clock::now();
    std::chrono::duration<double> setSearchTime = endSetSearch - startSetSearch;

    auto startRBTreeSearch = std::chrono::steady_clock::now();
    for (int i = 0; i < SIZE; ++i) {
        redBlackTree.find(generateRandomNumber(0, 10000));
    }
    auto endRBTreeSearch = std::chrono::steady_clock::now();
    std::chrono::duration<double> RBTreeSearchTime = endRBTreeSearch - startRBTreeSearch;

    auto startSetInsert = std::chrono::steady_clock::now();
    for (int i = 0; i < SIZE; ++i) {
        containerSet.insert(generateRandomNumber(0, 10000));
    }
    auto endSetInsert = std::chrono::steady_clock::now();
    std::chrono::duration<double> setInsertTime = endSetInsert - startSetInsert;

    auto startRBTreeInsert = std::chrono::steady_clock::now();
    for (int i = 0; i < SIZE; ++i) {
        int num = generateRandomNumber(0, 10000);
        redBlackTree[num] = num;
    }
    auto endRBTreeInsert = std::chrono::steady_clock::now();
    std::chrono::duration<double> RBTreeInsertTime = endRBTreeInsert - startRBTreeInsert;

    std::cout << "Время поиска в std::set: " << setSearchTime.count() << " секунд\n";
    std::cout << "Время поиска в красно-черном дереве: " << RBTreeSearchTime.count() << " секунд\n";

    std::cout << "Время добавления нового элемента в std::set: " << setInsertTime.count() << " секунд\n";
    std::cout << "Время добавления нового элемента в красно-черное дерево: " << RBTreeInsertTime.count() << " секунд\n";

    return 0;
}
