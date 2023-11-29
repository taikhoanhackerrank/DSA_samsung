#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef pair<int, int> pii;

void primAlgorithm(int start, vector<vector<pii>> &adj, vector<bool> &visited, int &totalCost) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int a = pq.top().second; pq.pop();
        if (visited[a]) continue;
        visited[a] = true;
        totalCost += pq.top().first;

        for (auto u : adj[a]) {
            int b = u.first, w = u.second;
            if (!visited[b]) {
                pq.push({w, b});
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<pii>> adj(n);
    vector<bool> visited(n, false);
    int totalCost = 0;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            primAlgorithm(i, adj, visited, totalCost);
        }
    }

    cout << totalCost << endl;
    return 0;
}
