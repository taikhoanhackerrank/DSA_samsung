#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <unordered_set>

using namespace std;

typedef pair<int, int> pii; // Pair of weight and vertex

int dijkstraForTwoSets(const vector<vector<pii>>& adj, const unordered_set<int>& S, const unordered_set<int>& T, int V) {
    vector<int> dist(V, INT_MAX);
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    // Initialize distances of source vertices to 0 and add them to the priority queue
    for (int source : S) {
        dist[source] = 0;
        pq.push({0, source});
    }

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        // Stop if we reach any vertex in T
        if (T.find(u) != T.end()) {
            return dist[u];
        }

        for (const auto& [v, weight] : adj[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return INT_MAX; // Return INT_MAX if there is no path from S to T
}

int main() {
    int V, E;
    cin >> V >> E;

    vector<vector<pii>> adj(V);
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    int numS, numT;
    cin >> numS >> numT;

    unordered_set<int> S, T;
    for (int i = 0, vertex; i < numS; i++) {
        cin >> vertex;
        S.insert(vertex);
    }

    for (int i = 0, vertex; i < numT; i++) {
        cin >> vertex;
        T.insert(vertex);
    }

    int shortestPath = dijkstraForTwoSets(adj, S, T, V);

    if (shortestPath == INT_MAX) {
        cout << "No path exists from S to T." << endl;
    } else {
        cout << "Shortest path from S to T is " << shortestPath << endl;
    }

    return 0;
}
