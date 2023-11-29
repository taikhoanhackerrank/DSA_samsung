#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef pair<int, int> pii; // Pair of weight and vertex

vector<int> dijkstraMultipleSources(const vector<vector<pii>>& adj, const vector<int>& sources, int V) {
    vector<int> dist(V, INT_MAX);
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    // Initialize distances of source vertices to 0 and add them to the priority queue
    for (int source : sources) {
        dist[source] = 0;
        pq.push({0, source});
    }

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const auto& [v, weight] : adj[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
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

    int numSources;
    cin >> numSources;

    vector<int> sources(numSources);
    for (int i = 0; i < numSources; i++) {
        cin >> sources[i];
    }

    vector<int> shortestPaths = dijkstraMultipleSources(adj, sources, V);

    for (int i = 0; i < V; i++) {
        cout <<  i << " is " << shortestPaths[i] << endl;
    }

    return 0;
}
