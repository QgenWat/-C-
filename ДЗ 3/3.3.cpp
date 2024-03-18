#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void calculate_heights(map<string, string>& parent_map, map<string, int>& heights, string node) {
    if (parent_map.find(node) == parent_map.end()) {
        heights[node] = 0;
    } else {
        if (heights.find(parent_map[node]) != heights.end()) {
            heights[node] = heights[parent_map[node]] + 1;
        } else {
            calculate_heights(parent_map, heights, parent_map[node]);
            heights[node] = heights[parent_map[node]] + 1;
        }
    }
}

int main() {
    int N;
    cin >> N;

    map<string, string> parent_map; 
    map<string, int> heights;

    for (int i = 0; i < N - 1; ++i) {
        string child, parent;
        cin >> child >> parent;
        parent_map[child] = parent;
    }

    for (auto it = parent_map.begin(); it != parent_map.end(); ++it) {
        calculate_heights(parent_map, heights, it->first);
    }

    vector<string> sorted_names;
    for (auto it = parent_map.begin(); it != parent_map.end(); ++it) {
        sorted_names.push_back(it->first);
    }
    sorted_names.push_back("Peter_I");

    sort(sorted_names.begin(), sorted_names.end());
    cout << endl;

    for (const string& name : sorted_names) {
        cout << name << " " << heights[name] << endl;
    }

    return 0;
}
