#include <iostream>
#include <list>
#include <stack>
#include <vector>
using namespace std;

class Graph {
    int V;
    list<int> *adj;

    void fillOrder(int v, vector<bool> &visited, stack<int> &Stack) {
        visited[v] = true;

        for (auto i = adj[v].begin(); i != adj[v].end(); ++i)
            if (!visited[*i])
                fillOrder(*i, visited, Stack);

        Stack.push(v);
    }

    void DFSUtil(int v, vector<bool> &visited) {
        visited[v] = true;
        cout << v << " ";

        for (auto i = adj[v].begin(); i != adj[v].end(); ++i)
            if (!visited[*i])
                DFSUtil(*i, visited);
    }

public:
    Graph(int V) {
        this->V = V;
        adj = new list<int>[V];
    }

    void addEdge(int v, int w) { adj[v].push_back(w); }

    Graph getTranspose() {
        Graph g(V);
        for (int v = 0; v < V; v++)
            for (auto i = adj[v].begin(); i != adj[v].end(); ++i)
                g.adj[*i].push_back(v);
        return g;
    }

    void printSCCs() {
        stack<int> Stack;

        vector<bool> visited(V, false);

        for (int i = 0; i < V; i++)
            if (!visited[i])
                fillOrder(i, visited, Stack);

        Graph gr = getTranspose();

        fill(visited.begin(), visited.end(), false);

        while (!Stack.empty()) {
            int v = Stack.top();
            Stack.pop();

            if (!visited[v]) {
                gr.DFSUtil(v, visited);
                cout << endl;
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

    cout << "Các thành phần liên thông mạnh trong đồ thị là:\n";
    g.printSCCs();

    return 0;
}

