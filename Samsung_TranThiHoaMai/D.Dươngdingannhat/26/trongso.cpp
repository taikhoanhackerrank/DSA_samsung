#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef pair<int, int> pii; // Pair of weight and vertex

struct Edge {
    int u, v;
};

int main() {
    int V, E;
    cin >> V >> E;

    vector<int> vertexWeights(V);
    vector<vector<pii>> adj(V); // Adjacency list for the transformed graph
    vector<Edge> edges(E);

    for (int i = 0; i < V; i++) {
        cin >> vertexWeights[i];
    }

    for (int i = 0; i < E; i++) {
        cin >> edges[i].u >> edges[i].v;
        int u = edges[i].u, v = edges[i].v;
        adj[u].push_back({v, vertexWeights[v]}); // Edge weight is the vertex weight of the destination
    }

    // Dijkstra's algorithm
    vector<int> dist(V, INT_MAX);
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    int startVertex;
    cin >> startVertex;

    pq.push({0, startVertex});
    dist[startVertex] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto& [v, weight] : adj[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    // Print shortest paths
    for (int i = 0; i < V; i++) {
        cout << i << " is " << dist[i] << endl;
    }

    return 0;
}
