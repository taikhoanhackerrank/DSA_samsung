#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Định nghĩa cấu trúc cạnh
struct Edge {
    int src, dest, weight;
};

// Định nghĩa cấu trúc đại diện cho một cây con
struct Subset {
    int parent;
    int rank;
    bool inMST;
};

// Tìm đại diện của một tập hợp (cây con)
int find(vector<Subset>& subsets, int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Hợp nhất hai tập hợp (cây con)
void Union(vector<Subset>& subsets, int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Thuật toán Boruvka cải tiến để tìm cây bao trùm nhỏ nhất
void BoruvkaMST(vector<Edge>& edges, int V) {
    // Lưu trữ cây bao trùm nhỏ nhất
    vector<Edge> minSpanningTree;

    // Tạo một mảng lưu trữ các cây con
    vector<Subset> subsets(V);

    // Khởi tạo mỗi đỉnh là một cây con
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
        subsets[v].inMST = false;
    }

    // Số cây con hiện tại
    int numTrees = V;

    // Lặp cho đến khi chỉ còn một cây
    while (numTrees > 1) {
        // Tìm cạnh có trọng số nhỏ nhất cho mỗi cây con
        vector<Edge> cheapest(V);
        for (int i = 0; i < V; i++) {
            cheapest[i].weight = INT_MAX;
        }

        for (int i = 0; i < edges.size(); i++) {
            int set1 = find(subsets, edges[i].src);
            int set2 = find(subsets, edges[i].dest);

            if (set1 != set2) {
                if (edges[i].weight < cheapest[set1].weight)
                    cheapest[set1] = edges[i];
                if (edges[i].weight < cheapest[set2].weight)
                    cheapest[set2] = edges[i];
            }
        }

        // Thêm cạnh có trọng số nhỏ nhất từ mỗi cây con vào cây bao trùm
        for (int i = 0; i < V; i++) {
            if (cheapest[i].weight != INT_MAX) {
                int set1 = find(subsets, cheapest[i].src);
                int set2 = find(subsets, cheapest[i].dest);

                if (set1 != set2) {
                    minSpanningTree.push_back(cheapest[i]);

                    // Merge hai cây con
                    Union(subsets, set1, set2);
                    subsets[set1].inMST = true;

                    // Giảm số cây con
                    numTrees--;
                }
            }
        }

        // Cập nhật cây con cho lần lặp tiếp theo
        for (int v = 0; v < V; v++) {
            int set = find(subsets, v);
            subsets[set].inMST = false;
        }
    }

    // In cây bao trùm nhỏ nhất
    cout << "Cây bao trùm nhỏ nhất:\n";
    for (int i = 0; i < minSpanningTree.size(); i++) {
        cout << minSpanningTree[i].src << " - " << minSpanningTree[i].dest << "   Trọng số: " << minSpanningTree[i].weight << endl;
    }
}

int main() {
    int V, E;
    cout << "Nhập số đỉnh V: ";
    cin >> V;
    cout << "Nhập số cạnh E: ";
    cin >> E;

    vector<Edge> edges(E);
    for (int i = 0; i < E; i++) {
        cout << "Nhập thông tin cạnh " << i + 1 << " (nguồn đích trọng số): ";
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
    }

    BoruvkaMST(edges, V);

    return 0;
}
