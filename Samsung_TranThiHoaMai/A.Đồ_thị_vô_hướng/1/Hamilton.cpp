#include<bits/stdc++.h>
using namespace std;

bool isSafe(int v, const vector<vector<int>>& graph, vector<int>& path, int pos) {
    // Kiểm tra xem có cạnh từ đỉnh trước đó đến v không
    if (graph[path[pos - 1]][v] == 0) {
        return false;
    }

    // Kiểm tra xem đỉnh v đã được chọn trước đó chưa
    for (int i = 0; i < pos; ++i) {
        if (path[i] == v) {
            return false;
        }
    }

    return true;
}

bool hamiltonianCycleUtil(const vector<vector<int>>& graph, vector<int>& path, int pos) {
    if (pos == graph.size()) {
        // Kiểm tra xem có cạnh từ đỉnh cuối cùng đến đỉnh đầu tiên không
        if (graph[path[pos - 1]][path[0]] == 1) {
            return true;
        }
        return false;
    }

    for (int v = 1; v < graph.size(); ++v) {
        if (isSafe(v, graph, path, pos)) {
            path[pos] = v;
            if (hamiltonianCycleUtil(graph, path, pos + 1)) {
                return true;
            }
            path[pos] = -1;
        }
    }

    return false;
}

bool hasHamiltonianCycle(const vector<vector<int>>& graph) {
    vector<int> path(graph.size(), -1);
    path[0] = 0; // Bắt đầu từ đỉnh 0

    if (hamiltonianCycleUtil(graph, path, 1)) {
        cout << "Đồ thị có chu trình Hamilton: ";
        for (int vertex : path) {
            cout << vertex << " ";
        }
        cout << "0" << endl;
        return true;
    }

    cout << "Đồ thị không có chu trình Hamilton." << endl;
    return false;
}

int main() {
int numVertices = 8;
// Khởi tạo ma trận kề với các phần tử ban đầu bằng 0
vector<vector<int>> adjacencyMatrix(numVertices, vector<int>(numVertices, 0));
int u, v;
while(cin >> u >> v){
    if (u >= 0 && u < numVertices && v >= 0 && v < numVertices) {
        adjacencyMatrix[u][v] = 1;
        adjacencyMatrix[v][u] = 1; // Đồ thị vô hướng, nên cả 2 chiều đều 1
    }
}

hasHamiltonianCycle(adjacencyMatrix);

return 0;
}
