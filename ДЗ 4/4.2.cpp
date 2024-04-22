#include <iostream>
#include <chrono>
#include <random>
#include <map>

std::random_device rd;
std::mt19937 gen(rd());

int generateRandomNumber(int min, int max) {
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}
enum class Color { RED, BLACK };

template <typename Key, typename Value>
struct Node {
    Key key;
    Value value;
    Color color;
    Node* parent;
    Node* left;
    Node* right;

    Node(const Key& k, const Value& v, Color c = Color::RED, Node* p = nullptr, Node* l = nullptr, Node* r = nullptr)
        : key(k), value(v), color(c), parent(p), left(l), right(r) {}
};

template <typename Key, typename Value>
class RedBlackTree {
private:
    Node<Key, Value>* root;

    void rotateLeft(Node<Key, Value>* x) {
        Node<Key, Value>* y = x->right;
        x->right = y->left;
        if (y->left != nullptr)
            y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rotateRight(Node<Key, Value>* x) {
        Node<Key, Value>* y = x->left;
        x->left = y->right;
        if (y->right != nullptr)
            y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    void fixInsertion(Node<Key, Value>* z) {
        while (z->parent != nullptr && z->parent->color == Color::RED) {
            if (z->parent == z->parent->parent->left) {
                Node<Key, Value>* y = z->parent->parent->right;
                if (y != nullptr && y->color == Color::RED) {
                    z->parent->color = Color::BLACK;
                    y->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        rotateLeft(z);
                    }
                    z->parent->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    rotateRight(z->parent->parent);
                }
            } else {
                Node<Key, Value>* y = z->parent->parent->left;
                if (y != nullptr && y->color == Color::RED) {
                    z->parent->color = Color::BLACK;
                    y->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rotateRight(z);
                    }
                    z->parent->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    rotateLeft(z->parent->parent);
                }
            }
        }
        root->color = Color::BLACK;
    }

    Node<Key, Value>* minimum(Node<Key, Value>* x) {
        while (x->left != nullptr)
            x = x->left;
        return x;
    }

public:
    RedBlackTree() : root(nullptr) {}

    void insert(const Key& key, const Value& value) {
        Node<Key, Value>* z = new Node<Key, Value>(key, value);
        Node<Key, Value>* y = nullptr;
        Node<Key, Value>* x = root;
        while (x != nullptr) {
            y = x;
            if (z->key < x->key)
                x = x->left;
            else
                x = x->right;
        }
        z->parent = y;
        if (y == nullptr)
            root = z;
        else if (z->key < y->key)
            y->left = z;
        else
            y->right = z;
        z->color = Color::RED;
        fixInsertion(z);
    }

    Node<Key, Value>* find(const Key& key) {
        Node<Key, Value>* current = root;
        while (current != nullptr) {
            if (key == current->key)
                return current;
            else if (key < current->key)
                current = current->left;
            else
                current = current->right;
        }
        return nullptr;
    }
};

int main() {
    RedBlackTree<int, int> rbTree;
    std::map<int, int> map;

    for (int i = 0; i < 500; ++i) {
        int num = generateRandomNumber(0, 10000);
        rbTree.insert(num, num);
    }

    for (int i = 0; i < 500; ++i) {
        int num = generateRandomNumber(0, 10000);
        map[num] = num;
    }

    auto startRBTSearch = std::chrono::steady_clock::now();
    for (int i = 0; i < 500; ++i) {
        rbTree.find(generateRandomNumber(0, 10000));
    }
    auto endRBTSearch = std::chrono::steady_clock::now();
    std::chrono::duration<double> RBTSearchTime = endRBTSearch - startRBTSearch;

    auto startMapSearch = std::chrono::steady_clock::now();
    for (int i = 0; i < 500; ++i) {
        map.find(generateRandomNumber(0, 10000));
    }
    auto endMapSearch = std::chrono::steady_clock::now();
    std::chrono::duration<double> mapSearchTime = endMapSearch - startMapSearch;

    std::cout << "Время поиска в красно-черном дереве: " << RBTSearchTime.count() << " секунд\n";
    std::cout << "Время поиска в std::map: " << mapSearchTime.count() << " секунд\n";

    return 0;
}
