#include <iostream>
#include <string>
#include <regex>
#include <iterator>
#include <algorithm>
#include <map>

int main() {
    std::map<std::string, int> word_counter;
    std::cout << "Text: ";
    std::string text;
    std::getline(std::cin, text);
    std::regex reg("\\w+");
    for (auto it = std::sregex_iterator(text.begin(), text.end(), reg); it != std::sregex_iterator(); ++it) {
        std::string word = (*it)[0];
        std::transform(word.begin(), word.end(), word.begin(), ::toupper);
        word_counter[word]++;
    }
    
    std::pair<std::string, int> max("", -1);
    for (const auto& pair : word_counter) {
        if (pair.second > max.second || (pair.second == max.second && pair.first < max.first)) {
            max = pair;
        }
    }
    std::cout << max.first << " " << max.second << " times" << '\n';
    return 0;
}
// Программа работает только с английскими символами