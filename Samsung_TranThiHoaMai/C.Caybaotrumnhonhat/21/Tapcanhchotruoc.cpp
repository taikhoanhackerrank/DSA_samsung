// Bắt đầu bằng việc thêm tất cả các cạnh trong tập S vào cây bao trùm.
// Sử dụng thuật toán Kruskal để thêm các cạnh còn lại từ G vào cây bao trùm, nhưng chỉ thêm những cạnh không tạo thành chu trình với các cạnh đã có trong cây.


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
    int n, m, s;
    cin >> n >> m >> s;

    vector<Edge> edges(m), edgesInS(s);
    vector<int> parent(n), rank(n, 0);
    for (int i = 0; i < n; i++)
        parent[i] = i;

    for (int i = 0; i < s; i++)
        cin >> edgesInS[i].u >> edgesInS[i].v >> edgesInS[i].weight;

    for (int i = 0; i < m - s; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;

    // Add edges from S to the MST
    for (Edge& e : edgesInS) {
        unionSets(e.u, e.v, parent, rank);
    }

    // Add other edges using Kruskal's algorithm
    sort(edges.begin(), edges.end());
    for (Edge& e : edges) {
        if (findSet(e.u, parent) != findSet(e.v, parent)) {
            unionSets(e.u, e.v, parent, rank);
        }
    }

    // Printing the result
    for (Edge& e : edgesInS)
        cout << e.u << " -- " << e.v << " : " << e.weight << endl;

    for (Edge& e : edges) {
        if (findSet(e.u, parent) == findSet(e.v, parent))
            cout << e.u << " -- " << e.v << " : " << e.weight << endl;
    }

    return 0;
}
