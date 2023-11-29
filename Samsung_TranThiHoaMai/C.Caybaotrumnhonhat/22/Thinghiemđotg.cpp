#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <cstdlib>

using namespace std;

// Định nghĩa cạnh trong đồ thị
struct Edge {
    int src, dest, weight;
};

// Định nghĩa đồ thị
class Graph {
    int V;
    vector<Edge> edges;

public:
    Graph(int vertices) {
        V = vertices;
    }

    // Thêm cạnh vào đồ thị
    void addEdge(int src, int dest, int weight) {
        Edge edge = {src, dest, weight};
        edges.push_back(edge);
    }

    // Thuật toán Prim lười
    double primLazy() {
        clock_t start_time = clock();

        // Khởi tạo các biến cần thiết
        vector<bool> visited(V, false);
        vector<int> key(V, INT_MAX);
        key[0] = 0;

        // Duyệt qua các đỉnh
        int mstWeight = 0;
        for (int count = 0; count < V - 1; count++) {
            // Tìm đỉnh có key nhỏ nhất chưa được thăm
            int minKey = INT_MAX;
            int minIndex = -1;
            for (int v = 0; v < V; v++) {
                if (!visited[v] && key[v] < minKey) {
                    minKey = key[v];
                    minIndex = v;
                }
            }

            // Đánh dấu đỉnh đã thăm
            visited[minIndex] = true;
            mstWeight += minKey;

            // Cập nhật key của các đỉnh kề chưa được thăm
            for (const Edge& edge : edges) {
                if (!visited[edge.dest] && edge.src == minIndex && edge.weight < key[edge.dest]) {
                    key[edge.dest] = edge.weight;
                }
            }
        }

        clock_t end_time = clock();
        return double(end_time - start_time) / CLOCKS_PER_SEC;
    }

    // Thuật toán Prim dùng hàng đợi
    double primQueue() {
        clock_t start_time = clock();

        // Khởi tạo các biến cần thiết
        vector<bool> visited(V, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // Chọn đỉnh bắt đầu
        int start = 0;
        visited[start] = true;

        // Thêm các cạnh kề của đỉnh bắt đầu vào hàng đợi
        for (const Edge& edge : edges) {
            if (edge.src == start) {
                pq.push(make_pair(edge.weight, edge.dest));
            }
        }

        // Duyệt qua các đỉnh
        int mstWeight = 0;
        while (!pq.empty()) {
            pair<int, int> front = pq.top();
            pq.pop();
            int weight = front.first;
            int u = front.second;

            // Kiểm tra xem có thêm đỉnh vào cây khung không
            if (!visited[u]) {
                mstWeight += weight;
                visited[u] = true;

                // Thêm các cạnh kề của đỉnh vừa thêm vào hàng đợi
                for (const Edge& edge : edges) {
                    if (edge.src == u && !visited[edge.dest]) {
                        pq.push(make_pair(edge.weight, edge.dest));
                    }
                }
            }
        }

        clock_t end_time = clock();
        return double(end_time - start_time) / CLOCKS_PER_SEC;
    }

    // Thuật toán Kruskal
    double kruskal() {
        clock_t start_time = clock();

        // Sắp xếp các cạnh theo thứ tự không giảm của trọng số
        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.weight < b.weight;
        });

        // Khởi tạo các biến cần thiết
        vector<int> parent(V);
        vector<int>rank(V, 0);

        // Hàm tìm gốc của một tập hợp
        auto find = [&](int i) {
            if (parent[i] != i) {
                parent[i] = find(parent[i]);
            }
            return parent[i];
        };

        // Hàm hợp nhất hai tập hợp
        auto merge = [&](int x, int y) {
            int rootX = find(x);
            int rootY = find(y);

            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        };

        int mstWeight = 0;
        for (const Edge& edge : edges) {
            int rootSrc = find(edge.src);
            int rootDest = find(edge.dest);

            // Kiểm tra xem cạnh có tạo chu trình hay không
            if (rootSrc != rootDest) {
                merge(rootSrc, rootDest);
                mstWeight += edge.weight;
            }
        }

        clock_t end_time = clock();
        return double(end_time - start_time) / CLOCKS_PER_SEC;
    }
};

int main() {
    int V = 1000; // Số đỉnh
    int E = 5000; // Số cạnh

    Graph graph(V);

    // Tạo ngẫu nhiên các cạnh với trọng số từ 1 đến 100
    srand(time(NULL));
    for (int i = 0; i < E; i++) {
        int src = rand() % V;
        int dest = rand() % V;
        int weight = rand() % 100 + 1;
        graph.addEdge(src, dest, weight);
    }

    // Đo thời gian chạy của thuật toán Prim lười
    double primLazyTime = graph.primLazy();
    cout << "Prim (Lazy) Running Time: " << primLazyTime << " seconds" << endl;

    // Đo thời gian chạy của thuật toán Prim dùng hàng đợi
    double primQueueTime = graph.primQueue();
    cout << "Prim (Queue) Running Time: " << primQueueTime << " seconds" << endl;

    // Đo thời gian chạy của thuật toán Kruskal
    double kruskalTime = graph.kruskal();
    cout << "Kruskal Running Time: " << kruskalTime << " seconds" << endl;

    return 0;
}
