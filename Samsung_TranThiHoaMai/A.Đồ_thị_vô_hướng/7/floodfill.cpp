#include<iostream>
using namespace std;

// Kích thước của bức ảnh
const int M = 8;
const int N = 8;

// Hàm Flood Fill
void floodFillUtil(int screen[][N], int x, int y, int prevC, int newC) {
    // Kiểm tra xem điểm có nằm ngoài bức ảnh hay không
    if (x < 0 || x >= M || y < 0 || y >= N) return;
    if (screen[x][y] != prevC) return;

    // Thay đổi màu sắc tại điểm hiện tại
    screen[x][y] = newC;

    // Gọi đệ quy cho các điểm xung quanh
    floodFillUtil(screen, x+1, y, prevC, newC);
    floodFillUtil(screen, x-1, y, prevC, newC);
    floodFillUtil(screen, x, y+1, prevC, newC);
    floodFillUtil(screen, x, y-1, prevC, newC);
}

// Hàm chính để gọi Flood Fill
void floodFill(int screen[][N], int x, int y, int newC) {
    int prevC = screen[x][y];
    floodFillUtil(screen, x, y, prevC, newC);
}

// Hàm để in ra bức ảnh
void printScreen(int screen[][N]) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            cout << screen[i][j] << " ";
        cout << endl;
    }
}

// Hàm main để chạy chương trình
int main() {
    int screen[M][N] = {{1, 1, 1, 1, 1, 1, 1, 1},
                        {1, 1, 1, 1, 1, 1, 0, 0},
                        {1, 0, 0, 1, 1, 0, 1, 1},
                        {1, 2, 2, 2, 2, 0, 1, 0},
                        {1, 1, 1, 2, 2, 0, 1, 0},
                        {1, 1, 1, 2, 2, 2, 2, 0},
                        {1, 1, 1, 1, 1, 2, 1, 1},
                        {1, 1, 1, 1, 1, 2, 2, 1},
                       };
    int x = 4, y = 4, newC = 3;
    printScreen(screen);
    floodFill(screen, x, y, newC);
    cout << "Sau khi áp dụng Flood Fill: \n";
    printScreen(screen);
    return 0;
}
