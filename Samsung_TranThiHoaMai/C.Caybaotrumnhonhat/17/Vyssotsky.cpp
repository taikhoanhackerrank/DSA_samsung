#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

int findSet(int v, vector<int>& parent) {
    if (v == parent[v])
        return v;
    return parent[v] = findSet(parent[v], parent);
}

void unionSets(int a, int b, vector<int>& parent, vector<int>& rank) {
    a = findSet(a, parent);
    b = findSet(b, parent);
    if (a != b) {
        if (rank[a] < rank[b])
            swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    sort(edges.begin(), edges.end());

    vector<int> parent(n), rank(n, 0);
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    vector<Edge> result;
    for (Edge& e : edges) {
        if (findSet(e.u, parent) != findSet(e.v, parent)) {
            result.push_back(e);
            unionSets(e.u, e.v, parent, rank);
        } else {
            // Detect cycle and remove the heaviest edge
            int u = e.u, v = e.v;
            Edge heaviestEdge = e;
            while (u != v) {
                if (parent[u] == u) {
                    u = parent[v];
                    swap(u, v);
                } else {
                    if (heaviestEdge.weight < parent[u]) {
                        parent[u] = heaviestEdge.weight;
                    }
                    u = parent[u];
                }
            }
            // Remove heaviest edge
            result.erase(remove(result.begin(), result.end(), heaviestEdge), result.end());
        }
    }

    int totalWeight = 0;
    for (Edge& e : result) {
        cout << e.u << " -- " << e.v << " : " << e.weight << endl;
        totalWeight += e.weight;
    }

    cout << totalWeight << endl;
    return 0;
}
