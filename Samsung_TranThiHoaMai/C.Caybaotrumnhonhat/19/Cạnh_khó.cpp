#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, weight;
    bool inMST; // Indicates if the edge is in the MST
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

    vector<Edge> edges(m), mstEdges;
    vector<int> parent(n), rank(n, 0);
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
        edges[i].inMST = false;
    }

    sort(edges.begin(), edges.end());

    for (Edge& e : edges) {
        if (findSet(e.u, parent) != findSet(e.v, parent)) {
            e.inMST = true;
            mstEdges.push_back(e);
            unionSets(e.u, e.v, parent, rank);
        }
    }

    for (Edge& e : mstEdges) {
        int totalWeightWithEdge = 0, totalWeightWithoutEdge = 0;
        vector<int> tempParent = parent, tempRank = rank;

        // Total weight with the current edge
        for (Edge& edge : mstEdges) {
            if (edge.u == e.u && edge.v == e.v) continue; // Skip the current edge
            if (findSet(edge.u, tempParent) != findSet(edge.v, tempParent)) {
                totalWeightWithEdge += edge.weight;
                unionSets(edge.u, edge.v, tempParent, tempRank);
            }
        }

        // Reset parent and rank for without edge computation
        tempParent = parent;
        tempRank = rank;

        // Total weight without the current edge
        for (Edge& edge : edges) {
            if (edge.u == e.u && edge.v == e.v) continue; // Skip the current edge
            if (findSet(edge.u, tempParent) != findSet(edge.v, tempParent)) {
                totalWeightWithoutEdge += edge.weight;
                unionSets(edge.u, edge.v, tempParent, tempRank);
            }
        }

        if (totalWeightWithEdge < totalWeightWithoutEdge) {
            cout <<  e.u << " -- " << e.v << " : " << e.weight << endl;
        }
    }

    return 0;
}
