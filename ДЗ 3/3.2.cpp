#include <iostream>
#include <map>
#include <string>

class GenealogyTree {
private:
    std::map<std::string, int> heights;
public:
    GenealogyTree(const std::string& rootName) {
        heights[rootName] = 0;
    }

    void addMember(const std::string& member, const std::string& parent) {
        if (heights.find(parent) == heights.end()) {
            std::cerr << "Parent " << parent << " does not exist!\n";
            return;
        }
        heights[member] = heights[parent] + 1;
    }

    void printTree() {
        for (const auto& entry : heights) {
            std::cout << "Member: " << entry.first << ", Height: " << entry.second << std::endl;
        }
    }
};

int main() {
    std::string rootName;
    rootName = "Адам";

    GenealogyTree tree(rootName);

    tree.addMember("Ева", rootName);
    tree.addMember("Майкл", "Ева");
    tree.addMember("Миша", "Ева");
    tree.addMember("Егор", "Миша");

    tree.printTree();

    return 0;
}
