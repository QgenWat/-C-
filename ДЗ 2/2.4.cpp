#include <iostream>
#include <stack>
#include <unordered_map>
#include <string>

using namespace std;

bool isValid(string s) {
    stack<char> brackets;
    unordered_map<char, char> matching;
    matching.insert(make_pair(')', '('));
    matching.insert(make_pair(']', '['));
    matching.insert(make_pair('}', '{'));

    for (int i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (c == '(' || c == '[' || c == '{') {
            brackets.push(c);
        } else {
            if (brackets.empty() || brackets.top() != matching[c]) {
                return false;
            }
            brackets.pop();
        }
    }

    return brackets.empty();
}

int main() {
    string input;
    cout << "Введите последовательность скобок: ";
    cin >> input;

    if (isValid(input)) {
        cout << "Веденная последовательно - правильная" << endl;
    } else {
        cout << "Введенная последовательность - неправильная" << endl;
    }

    return 0;
}
