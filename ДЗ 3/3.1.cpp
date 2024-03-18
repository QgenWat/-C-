#include <iostream>
#include <vector>
#include <stdexcept>

size_t hashFunction(int key, size_t tableSize) {
    return key % tableSize;
}

class HashTable {
private:
    size_t size;
    std::vector<int> table;

public:
    HashTable(size_t size) : size(size) {
        table.resize(size, -1);
    }

    void insert(int key) {
        size_t index = hashFunction(key, size);
        size_t originalIndex = index;
        while (table[index] != -1) {
            index = (index + 1) % size;
            if (index == originalIndex) {
                throw std::runtime_error("Таблица заполнена");
            }
        }
        table[index] = key;
    }

    bool search(int key) {
        size_t index = hashFunction(key, size);
        size_t originalIndex = index;
        while (table[index] != key) {
            if (table[index] == -1) {
                return false;
            }
            index = (index + 1) % size;
            if (index == originalIndex) {
                return false;
            }
        }
        return true;
    }

    void remove(int key) {
        size_t index = hashFunction(key, size);
        size_t originalIndex = index;
        while (table[index] != key) {
            if (table[index] == -1) {
                throw std::out_of_range("Ключ не найден");
            }
            index = (index + 1) % size;
            if (index == originalIndex) {
                throw std::out_of_range("Ключ не найден");
            }
        }
        table[index] = -1; // Удаляем ключ
    }
};

int main() {
    HashTable ht(10);

    ht.insert(5);
    ht.insert(15);
    ht.insert(25);
    ht.insert(7);

    std::cout << "Ищем 15: " << (ht.search(15) ? "Найдено" : "Не найдено") << std::endl;
    std::cout << "Ищем 10: " << (ht.search(10) ? "Найдено" : "Не найдено") << std::endl;

    ht.remove(15);
    std::cout << "Ищем 15 после удаления: " << (ht.search(15) ? "Найдено" : "Не найдено") << std::endl;

    ht.insert(10);
    std::cout << "Ищем 10 после добавления: " << (ht.search(10) ? "Найдено" : "Не найдено") << std::endl;

    return 0;
}
