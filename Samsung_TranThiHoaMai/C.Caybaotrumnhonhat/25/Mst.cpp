// biến thể của thuật toán prim

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <unordered_set>

using namespace std;

typedef pair<int, int> pii; // pair of weight and vertex

struct Edge {
    int u, v, weight;
};

int main() {
    int V, E; // Number of vertices and edges
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<Edge> edges(E); // Assuming E is manageable to be read at once
    // In real scenario, read edges in chunks that fit into memory

    cout << "Enter edges (u, v, weight):" << endl;
    for (int i = 0; i < E; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    vector<int> key(V, INT_MAX);
    vector<bool> inMST(V, false);
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    // Start with vertex 0
    pq.push({0, 0});
    key[0] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        inMST[u] = true;

        // Process only a subset of edges that fit into memory
        for (const auto &e : edges) {
            int v = (e.u == u) ? e.v : (e.v == u) ? e.u : -1;
            if (v != -1 && !inMST[v] && e.weight < key[v]) {
                key[v] = e.weight;
                pq.push({key[v], v});
            }
        }
    }

    // Printing result
    int totalWeight = 0;
    for (int i = 0; i < V; ++i) {
        totalWeight += key[i];
        cout << "Vertex " << i << " - Key " << key[i] << endl;
    }
    cout << totalWeight << endl;

    return 0;
}
