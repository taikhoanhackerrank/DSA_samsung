#include<bits/stdc++.h>

using namespace std;

class Graph {
private:
    int V; // Số đỉnh
    vector<vector<int>> adj; // Danh sách kề

    // Hàm DFS để kiểm tra đồ thị có biconnected hay không
    bool isBiconnected(int u, vector<bool>& visited, vector<int>& disc, vector<int>& low, vector<int>& parent) {
        static int time = 0;
        int children = 0;
        visited[u] = true;
        disc[u] = low[u] = ++time;

        for (int v : adj[u]) {
            if (!visited[v]) {
                children++;
                parent[v] = u;
                if (isBiconnected(v, visited, disc, low, parent))
                    return true;

                low[u] = min(low[u], low[v]);

                if ((parent[u] == -1 && children > 1) || (parent[u] != -1 && low[v] >= disc[u]))
                    return true;
            } else if (v != parent[u]) {
                low[u] = min(low[u], disc[v]);
            }
        }

        return false;
    }

public:
    Graph(int vertices) : V(vertices) {
        adj.resize(V);
    }

    // Thêm cạnh vào đồ thị
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Kiểm tra đồ thị có phải là biconnected hay không
    bool isBiconnectedGraph() {
        vector<bool> visited(V, false);
        vector<int> disc(V, -1);
        vector<int> low(V, -1);
        vector<int> parent(V, -1);

        if (isBiconnected(0, visited, disc, low, parent)) {
            return false; // Nếu có điểm articulation thì không biconnected
        }

        // Kiểm tra xem tất cả các đỉnh đã được duyệt qua
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                return false;
            }
        }

        return true;
    }
};

int main() {
    int V, E;
    cin >> V >> E;

    Graph graph(V);

    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        graph.addEdge(u, v);
    }

    bool isBiconnected = graph.isBiconnectedGraph();

    if (isBiconnected) {
        cout << "Đồ thị là đồ thị biconnected." << endl;
    } else {
        cout << "Đồ thị không phải là đồ thị biconnected." << endl;
    }

    return 0;
}

