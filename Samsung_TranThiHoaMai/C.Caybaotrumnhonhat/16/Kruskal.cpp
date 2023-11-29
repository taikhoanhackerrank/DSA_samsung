#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, weight;
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

int findSet(int v, vector<int> &parent) {
    if (v == parent[v])
        return v;
    return parent[v] = findSet(parent[v], parent);
}

void unionSets(int a, int b, vector<int> &parent, vector<int> &rank) {
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
    vector<int> parent(n), rank(n, 0);
    for (int i = 0; i < n; i++)
        parent[i] = i;

    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    sort(edges.begin(), edges.end());

    int cost = 0;
    for (Edge e : edges) {
        if (findSet(e.u, parent) != findSet(e.v, parent)) {
            cost += e.weight;
            unionSets(e.u, e.v, parent, rank);
            cout << e.u << " -- " << e.v << " : " << e.weight << endl;
        }
    }

    cout << cost << endl;
    return 0;
}
