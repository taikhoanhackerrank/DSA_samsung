#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Định nghĩa cấu trúc cạnh
struct Edge {
    int src, dest, weight;
};

// Định nghĩa cấu trúc đại diện cho một cây
struct Subset {
    int parent;
    int rank;
};

// Tìm đại diện của một tập hợp (cây) bằng phương pháp nén đường dẫn (path compression)
int find(vector<Subset>& subsets, int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Hợp nhất hai tập hợp (cây) bằng cách gộp theo rank
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

// Thuật toán Boruvka để tìm cây bao trùm nhỏ nhất
void BoruvkaMST(vector<Edge>& edges, int V) {
    // Lưu trữ cây bao trùm nhỏ nhất
    vector<Edge> minSpanningTree;

    // Tạo một mảng lưu trữ các cây
    vector<Subset> subsets(V);

    // Khởi tạo mỗi đỉnh là một cây đơn lẻ
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Số cây hiện tại
    int numTrees = V;

    // Lặp cho đến khi chỉ còn một cây
    while (numTrees > 1) {
        // Lưu trữ cạnh có trọng số nhỏ nhất cho mỗi cây
        vector<Edge> cheapest(V);

        // Khởi tạo giá trị cheapest cho mỗi cây là vô cực
        for (int v = 0; v < V; v++) {
            cheapest[v].weight = INT_MAX;
        }

        // Tìm cạnh có trọng số nhỏ nhất cho mỗi cây
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

        // Thêm cạnh có trọng số nhỏ nhất từ mỗi cây vào cây bao trùm
        for (int v = 0; v < V; v++) {
            if (cheapest[v].weight != INT_MAX) {
                int set1 = find(subsets, cheapest[v].src);
                int set2 = find(subsets, cheapest[v].dest);

                if (set1 != set2) {
                    minSpanningTree.push_back(cheapest[v]);
                    Union(subsets, set1, set2);
                    numTrees--;
                }
            }
        }
    }

    // In cây bao trùm nhỏ nhất
    cout << "Cây bao trùm nhỏ nhất:\n";
    for (int i = 0; i < minSpanningTree.size(); i++) {
        cout << minSpanningTree[i].src << " - " << minSpanningTree[i].dest << " : " << minSpanningTree[i].weight << "\n```cpp
    }
}

int main() {
    // Số đỉnh và số cạnh
    int V, E;
    cout << "Nhập số đỉnh: ";
    cin >> V;
    cout << "Nhập số cạnh: ";
    cin >> E;

    // Khởi tạo danh sách cạnh
    vector<Edge> edges(E);

    // Nhập thông tin về các cạnh
    cout << "Nhập thông tin về các cạnh:\n";
    for (int i = 0; i < E; i++) {
        cout << "Cạnh " << i + 1 << ":\n";
        cout << "Đỉnh nguồn: ";
        cin >> edges[i].src;
        cout << "Đỉnh đích: ";
        cin >> edges[i].dest;
        cout << "Trọng số: ";
        cin >> edges[i].weight;
    }

    // Gọi thuật toán Boruvka
    BoruvkaMST(edges, V);

    return 0;
}
