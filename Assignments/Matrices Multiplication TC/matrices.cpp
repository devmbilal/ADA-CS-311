#include <iostream>
#include <climits>
#include <chrono>

using namespace std;
using namespace std::chrono;

#define MAX 31

// Function to generate random dimensions for the matrices
void generateDimensions(int* dimensions, int n) {
    for (int i = 0; i <= n; i++) {
        dimensions[i] = rand() % 100 + 1; // Random number between 1 and 100
    }
}

// Function to calculate the optimal number of multiplications
void matrixChainOrder(int* p, int n, int m[MAX][MAX], int s[MAX][MAX]) {
    for (int i = 1; i <= n; i++)
        m[i][i] = 0;

    for (int l = 2; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}

// Function to print the optimal order
void printOptimalOrder(int s[MAX][MAX], int i, int j) {
    if (i == j)
        cout << "A" << i;
    else {
        cout << "(";
        printOptimalOrder(s, i, s[i][j]);
        printOptimalOrder(s, s[i][j] + 1, j);
        cout << ")";
    }
}

int main() {
    srand(time(0));
    int m[MAX][MAX], s[MAX][MAX];
    int dimensions[MAX];

    int sizes[] = {5, 10, 15, 20, 25, 30};
    for (int i = 0; i < 6; i++) {
        int n = sizes[i];
        generateDimensions(dimensions, n);

        auto start = high_resolution_clock::now();
        matrixChainOrder(dimensions, n, m, s);
        auto stop = high_resolution_clock::now();

        cout << "For " << n << " matrices:\n";
        cout << "Optimal number of multiplications: " << m[1][n] << endl;
        cout << "Optimal order: ";
        printOptimalOrder(s, 1, n);
        cout << endl;

        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Execution time: " << duration.count() << " microseconds" << endl << endl;
    }

    return 0;
}