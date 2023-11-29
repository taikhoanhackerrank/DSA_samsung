#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
    int V;
    vector<int> *adj;

public:
    Graph(int V) {
        this->V = V;
        adj = new vector<int>[V];
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void topologicalSort() {
        vector<int> indegree(V, 0);

        // Xây dựng mảng indegree
        for (int u = 0; u < V; u++) {
            for (int v : adj[u]) {
                indegree[v]++;
            }
        }

        queue<int> q;

        // Thêm tất cả đỉnh nguồn vào hàng đợi
        for (int i = 0; i < V; i++)
            if (indegree[i] == 0)
                q.push(i);

        // Sắp xếp tô pô
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            cout << u << " ";

            for (int v : adj[u]) {
                if (--indegree[v] == 0)
                    q.push(v);
            }
        }
    }
};

int main() {
    int x;
    cin>>x;
    Graph g(x);
    while(cin >> u >> v){
        g.addEdge(u, v);
    }
    cout << "Thứ tự tô pô của đồ thị: ";
    g.topologicalSort();

    return 0;
}
