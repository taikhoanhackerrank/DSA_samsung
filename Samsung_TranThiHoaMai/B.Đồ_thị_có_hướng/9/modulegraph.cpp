#include <iostream>
#include <list>
#include <vector>
#include <stack>
using namespace std;

class Graph {
    int V; // Số đỉnh
    list<int> *adj; // Danh sách kề

    void DFSUtil(int v, vector<bool> &visited) {
        visited[v] = true;

        for (auto i = adj[v].begin(); i != adj[v].end(); ++i)
            if (!visited[*i])
                DFSUtil(*i, visited);
    }

    Graph getTranspose() {
        Graph g(V);
        for (int v = 0; v < V; v++)
            for(auto i = adj[v].begin(); i != adj[v].end(); ++i)
                g.adj[*i].push_back(v);
        return g;
    }

public:
    Graph(int V) {
        this->V = V;
        adj = new list<int>[V];
    }

    void addEdge(int u, int v) { adj[u].push_back(v); }

    bool isStronglyConnected() {
        vector<bool> visited(V, false);
        DFSUtil(0, visited);
        for (int i = 0; i < V; i++)
            if (visited[i] == false)
                return false;

        Graph gr = getTranspose();

        fill(visited.begin(), visited.end(), false);
        gr.DFSUtil(0, visited);
        for (int i = 0; i < V; i++)
            if (visited[i] == false)
                return false;

        return true;
    }

    bool isEulerianCycle() {
        if (!isStronglyConnected())
            return false;

        vector<int> in(V, 0), out(V, 0);
        for (int u = 0; u < V; u++) {
            for (auto v : adj[u])
                out[u]++, in[v]++;
        }

        for (int i = 0; i < V; i++)
            if (in[i] != out[i])
                return false;

        return true;
    }
};

int main() {
    int x;
    cin>>x;
    Graph g(x);
    while(cin >> u >> v){
        g.addEdge(u, v);
    }

    if (g.isEulerianCycle())
        cout << "Đồ thị có chu trình Euler" << endl;
    else
        cout << "Đồ thị không có chu trình Euler" << endl;

    return 0;
}
