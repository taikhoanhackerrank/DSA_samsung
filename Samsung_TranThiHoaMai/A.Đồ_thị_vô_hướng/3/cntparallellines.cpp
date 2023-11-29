/*1. Khởi tạo biến count = 0 để đếm số cạnh song song.
2. Lặp qua từng cặp đỉnh (u, v) trong đồ thị, với u < v.
   a. Nếu có cạnh nối giữa đỉnh u và đỉnh v (tức ma trận kề[u][v] hoặc ma trận kề[v][u] bằng 1), thì:
      i. Tăng giá trị của count lên 1.
3. Kết thúc vòng lặp.
4. Giá trị của biến count chính là số cạnh song song trong đồ thị.
*/
#include<bits/stdc++.h>

using namespace std;

int countParallelEdges(const vector<vector<int>>& adjacencyMatrix) {
    int numVertices = adjacencyMatrix.size();
    int count = 0;

    for (int u = 0; u < numVertices; ++u) {
        for (int v = u + 1; v < numVertices; ++v) {
            if (adjacencyMatrix[u][v] == 1 || adjacencyMatrix[v][u] == 1) {
                // Có cạnh nối giữa đỉnh u và đỉnh v hoặc ngược lại
                count++;
            }
        }
    }

    return count;
}

int main() {
    int numVertices, numEdges;
    cin >> numVertices;

    // Khởi tạo ma trận kề với các phần tử ban đầu bằng 0
    vector<vector<int>> adjacencyMatrix(numVertices, vector<int>(numVertices, 0));

    cin >> numEdges;
    int u, v;
    while(cin >> u >> v){
        if (u >= 0 && u < numVertices && v >= 0 && v < numVertices) {
            adjacencyMatrix[u][v] = 1;
            adjacencyMatrix[v][u] = 1; // Đồ thị vô hướng, nên cả 2 chiều đều 1
        }
    }
    int parallelEdges = countParallelEdges(adjacencyMatrix);

    cout << parallelEdges << endl;

    return 0;
}
