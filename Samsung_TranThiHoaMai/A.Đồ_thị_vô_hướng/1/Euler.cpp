#include<bits/stdc++.h>
using namespace std;

// Hàm kiểm tra đồ thị liên thông bằng DFS
bool checkConnected(const unordered_map<int, vector<int>>& adjacencyList) {
    unordered_set<int> visited;
    vector<int> stack;
    stack.push_back(adjacencyList.begin()->first); // Chọn một đỉnh bất kỳ làm đỉnh xuất phát

    while (!stack.empty()) {
        int vertex = stack.back();
        stack.pop_back();
        if (visited.find(vertex) == visited.end()) {
            visited.insert(vertex);
            for (int neighbor : adjacencyList.at(vertex)) {
                if (visited.find(neighbor) == visited.end()) {
                    stack.push_back(neighbor);
                }
            }
        }
    }

    return visited.size() == adjacencyList.size();
}

// Hàm kiểm tra xem đồ thị có chu trình Euler không
bool isEulerianCycle(const vector<pair<int, int>>& edges) {
    // Tạo danh sách kề
    unordered_map<int, vector<int>> adjacencyList;

    // Đếm số bậc của mỗi đỉnh
    unordered_map<int, int> degrees;

    // Tính số bậc và tạo danh sách kề
    for (const auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u);
        degrees[u]++;
        degrees[v]++;
    }

    // Kiểm tra xem đồ thị liên thông không
    bool isConnected = checkConnected(adjacencyList);

    for (const auto& degree : degrees) {
        if (degree.second % 2 != 0) {
            return false; // Đỉnh có bậc lẻ, không phải chu trình Euler
        }
    }

    return isConnected;
}

int main() {
    vector<pair<int, int>> edges;
    string input;
    getline(cin, input);
    istringstream iss(input);
    int u, v;

    while (iss >> u >> v) {
        edges.emplace_back(u, v);
    }

    if (isEulerianCycle(edges)) {
        cout << "Đồ thị có chu trình Euler." << endl;
    } else {
        cout << "Đồ thị không có chu trình Euler." << endl;
    }

    return 0;
}
