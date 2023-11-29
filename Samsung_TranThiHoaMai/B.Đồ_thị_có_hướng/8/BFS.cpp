#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Hàm thực hiện thuật toán BFS trên đồ thị
void BFS(vector<vector<int>>& graph, int source) {
    int numVertices = graph.size();
    vector<bool> visited(numVertices, false);   // Mảng lưu trạng thái đỉnh đã được thăm
    queue<int> q;   // Hàng đợi lưu các đỉnh đang xem xét

    visited[source] = true;   // Đánh dấu đỉnh nguồn đã được thăm
    q.push(source);   // Thêm đỉnh nguồn vào hàng đợi

    while (!q.empty()) {
        int currentVertex = q.front();
        q.pop();

        cout << currentVertex << " ";  // In ra đỉnh đang xét

        // Duyệt qua tất cả các đỉnh kề chưa được thăm
        for (int neighbor : graph[currentVertex]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;   // Đánh dấu đỉnh kề đã được thăm
                q.push(neighbor);   // Thêm đỉnh kề vào hàng đợi
            }
        }
    }
}

int main() {
    int numVertices, numEdges;
    cout << "Enter the number of vertices: ";
    cin >> numVertices;
    cout << "Enter the number of edges: ";
    cin >> numEdges;

    vector<vector<int>> graph(numVertices);

    cout << "Enter the edges (u v):" << endl;
    for (int i = 0; i < numEdges; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);   // Cho đồ thị vô hướng, cần thêm cả cạnh (v, u)
    }

    int source;
    cout << "Enter the source vertex: ";
    cin >> source;

    cout << "BFS traversal starting from vertex " << source << ": ";
    BFS(graph, source);

    return 0;
}
