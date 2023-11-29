#include <iostream>
#include <list>
#include <stack>
#include <vector>
using namespace std;

class Graph {
    int V;
    list<int> *adj;

    void topologicalSortUtil(int v, vector<bool> &visited, stack<int> &Stack) {
        visited[v] = true;

        for (auto i = adj[v].begin(); i != adj[v].end(); ++i)
            if (!visited[*i])
                topologicalSortUtil(*i, visited, Stack);

        Stack.push(v);
    }

public:
    Graph(int V) {
        this->V = V;
        adj = new list<int>[V];
    }

    void addEdge(int v, int w) { adj[v].push_back(w); }

    bool hasUniqueTopologicalSort() {
        stack<int> Stack;
        vector<bool> visited(V, false);

        for (int i = 0; i < V; i++)
            if (!visited[i])
                topologicalSortUtil(i, visited, Stack);

        int u = Stack.top();
        Stack.pop();

        while (!Stack.empty()) {
            int v = Stack.top();
            Stack.pop();

            if (find(adj[u].begin(), adj[u].end(), v) == adj[u].end())
                return false;
            u = v;
        }

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

    if (g.hasUniqueTopologicalSort())
        cout << "Đồ thị có thứ tự tô pô duy nhất" << endl;
    else
        cout << "Đồ thị không có thứ tự tô pô duy nhất" << endl;

    return 0;
}
