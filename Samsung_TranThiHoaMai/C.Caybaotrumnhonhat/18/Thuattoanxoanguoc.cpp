#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct Edge {
    int u, v, weight;
    bool included;
    bool operator<(const Edge& other) const {
        return weight > other.weight;
    }
};

int findSet(int v, vector<int>& parent) {
    if (v == parent[v])
        return v;
    return parent[v] = findSet(parent[v], parent);
}

bool isConnected(int a, int b, vector<int>& parent) {
    return findSet(a, parent) == findSet(b, parent);
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
        edges[i].included = true;
    }

    sort(edges.begin(), edges.end());

    vector<int> parent(n), rank(n, 0);
    iota(parent.begin(), parent.end(), 0);

    for (Edge& e : edges) {
        unionSets(e.u, e.v, parent, rank);
    }

    for (Edge& e : edges) {
        vector<int> tempParent = parent;
        vector<int> tempRank = rank;
        int uSet = findSet(e.u, tempParent);
        int vSet = findSet(e.v, tempParent);

        if (uSet != vSet) {
            tempParent[uSet] = vSet;
            if (tempRank[uSet] == tempRank[vSet])
                tempRank[vSet]++;

            bool stillConnected = true;
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    if (!isConnected(i, j, tempParent)) {
                        stillConnected = false;
                        break;
                    }
                }
                if (!stillConnected)
                    break;
            }

            if (stillConnected) {
                e.included = false;
                parent = tempParent;
                rank = tempRank;
            }
        }
    }

    int totalWeight = 0;
    for (Edge& e : edges) {
        if (e.included) {
            cout << e.u << " -- " << e.v << " : " << e.weight << endl;
            totalWeight += e.weight;
        }
    }

    cout << totalWeight << endl;
    return 0;
}
