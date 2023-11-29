#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool isBipartite(vector<vector<int>>& graph) {
    int V = graph.size();
    vector<int> color(V, -1); // Mảng lưu màu của từng đỉnh, -1 là chưa được tô màu

    // Duyệt qua từng đỉnh của đồ thị
    for (int start = 0; start < V; start++) {
        if (color[start] == -1) { // Nếu đỉnh chưa được tô màu
            color[start] = 0; // Tô màu đỉnh bắt đầu là màu 0
            queue<int> q;
            q.push(start);

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                // Duyệt qua các đỉnh kề với u
                for (int v : graph[u]) {
                    if (color[v] == -1) {
                        color[v] = 1 - color[u]; // Đổi màu
                        q.push(v);
                    } else if (color[v] == color[u]) {
                        // Đã có cạnh nối giữa hai đỉnh cùng màu, không phải bipartite
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

bool hasOddCycle(vector<vector<int>>& graph) {
    int V = graph.size();
    vector<bool> visited(V, false);
    vector<int> parent(V, -1);

    for (int start = 0; start < V; start++) {
        if (!visited[start]) {
            queue<int> q;
            q.push(start);
            visited[start] = true;

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (int v : graph[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        parent[v] = u;
                        q.push(v);
                    } else if (parent[u] != v) {
                        // Đã duyệt đỉnh v từ đỉnh u và u không phải cha của v
                        // => Có chu trình độ dài lẻ
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

int main() {
    int V, E;
    cin >> V >> E;

    vector<vector<int>> graph(V);

    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); // Đồ thị vô hướng, nên cạnh kép
    }

    bool isBipartiteGraph = isBipartite(graph);
    bool hasOddLengthCycle = hasOddCycle(graph);

    if (isBipartiteGraph) {
        cout << "Đồ thị là đồ thị hai mầu (bipartite)." << endl;
    } else {
        cout << "Đồ thị không phải là đồ thị hai mầu (không bipartite)." << endl;
    }

    if (hasOddLengthCycle) {
        cout << "Đồ thị chứa chu trình độ dài lẻ." << endl;
    } else {
        cout << "Đồ thị không chứa chu trình độ dài lẻ." << endl;
    }

    return 0;
}

