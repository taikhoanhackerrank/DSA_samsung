#include <iostream>
#include <vector>

using namespace std;

class Graph {
private:
    int V; // Số đỉnh
    vector<vector<int>> adj; // Danh sách kề
    int time; // Biến thời gian để đánh dấu các đỉnh

    // Hàm DFS để kiểm tra cầu
    void isEdgeConnected(int u, vector<int>& disc, vector<int>& low, vector<int>& parent, vector<bool>& isCutVertex) {
        int children = 0;
        disc[u] = low[u] = ++time;

        for (int v : adj[u]) {
            if (disc[v] == -1) { // Nếu đỉnh v chưa được duyệt
                children++;
                parent[v] = u;
                isEdgeConnected(v, disc, low, parent, isCutVertex);

                low[u] = min(low[u], low[v]);

                // Điều kiện để u là đỉnh cắt (cut vertex) nếu u không phải gốc của cây DFS và low[v] >= disc[u]
                if (parent[u] != -1 && low[v] >= disc[u]) {
                    isCutVertex[u] = true;
                }
            } else if (v != parent[u]) { // Nếu v đã được duyệt và không phải cha của u
                low[u] = min(low[u], disc[v]);
            }
        }

        // Điều kiện để u là đỉnh cắt (cut vertex) nếu u là gốc của cây DFS và có nhiều hơn một con
        if (parent[u] == -1 && children > 1) {
            isCutVertex[u] = true;
        }
    }

public:
    Graph(int vertices) : V(vertices) {
        adj.resize(V);
        time = 0;
    }

    // Thêm cạnh vào đồ thị
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Kiểm tra xem đồ thị có tính chất liên thông cạnh hay không
    bool isEdgeConnectedGraph() {
        vector<int> disc(V, -1); // Thời gian đầu tiên mà đỉnh được duyệt qua
        vector<int> low(V, -1); // Thời gian nhỏ nhất mà một đỉnh có thể truy cập được từ cây DFS
        vector<int> parent(V, -1); // Cha của mỗi đỉnh trong cây DFS
        vector<bool> isCutVertex(V, false); // Mảng đánh dấu các đỉnh cắt

        // Duyệt qua từng đỉnh để kiểm tra đỉnh cắt
        for (int i = 0; i < V; i++) {
            if (disc[i] == -1) {
                isEdgeConnected(i, disc, low, parent, isCutVertex);
            }
        }

        // Kiểm tra xem có đỉnh cắt nào không
        for (int i = 0; i < V; i++) {
            if (isCutVertex[i]) {
                return false; // Nếu có ít nhất một đỉnh cắt, đồ thị không liên thông cạnh
            }
        }

        return true; // Nếu không có đỉnh cắt, đồ thị liên thông cạnh
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

    bool isEdgeConnected = graph.isEdgeConnectedGraph();

    if (isEdgeConnected) {
        cout << "Đồ thị là đồ thị liên thông cạnh." << endl;
    } else {
        cout << "Đồ thị không phải là đồ thị liên thông cạnh." << endl;
    }

    return 0;
}

