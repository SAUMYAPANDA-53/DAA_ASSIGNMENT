/*--------ALGORITHM---------
Algorithm MatrixChainOrder(p, n):
    Input: Array p of dimensions where matrix A_i has dimension p[i-1] x p[i], n matrices
    Output: Minimum multiplication cost and optimal split table s

    Declare table m[1..n][1..n] initialized to 0
    Declare table s[1..n][1..n]

    for L = 2 to n do                      // L is chain length
        for i = 1 to n - L + 1 do
            j = i + L - 1
            m[i][j] = INFINITY
            for k = i to j - 1 do
                cost = m[i][k] + m[k+1][j] + p[i-1] * p[k] * p[j]
                if cost < m[i][j] then
                    m[i][j] = cost
                    s[i][j] = k

    return m, s

Algorithm PrintOptimalParentheses(s, i, j):
    if i == j then
        print "A" + i
    else
        print "("
        PrintOptimalParentheses(s, i, s[i][j])
        PrintOptimalParentheses(s, s[i][j] + 1, j)
        print ")"
*/
/*-----CODE-------*/
#include <stdio.h>
#include <limits.h>

#define MAX 10

// Helper function to recursively print optimal parenthesization
void printOptimal(int s[MAX][MAX], int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        printOptimal(s, i, s[i][j]);
        printOptimal(s, s[i][j] + 1, j);
        printf(")");
    }
}

// Matrix Chain Multiplication Dynamic Programming Function
void matrixChainOrder(int p[], int n) {
    int m[MAX][MAX] = {0};
    int s[MAX][MAX] = {0};

    // L is the chain length
    for (int L = 2; L <= n; L++) {
        for (int i = 1; i <= n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;

            for (int k = i; k <= j - 1; k++) {
                int cost = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("Minimum Scalar Multiplications: %d\n", m[1][n]);
    printf("Optimal Parenthesization: ");
    printOptimal(s, 1, n);
    printf("\n");
}

int main() {
    // Array p defines dimensions:
    // A1 = 10x30, A2 = 30x5, A3 = 5x60
    int p[] = {10, 30, 5, 60};
    int n = (sizeof(p) / sizeof(p[0])) - 1; // Number of matrices

    printf("Dimensions array: ");
    for (int i = 0; i <= n; i++) printf("%d ", p[i]);
    printf("\n\n");

    matrixChainOrder(p, n);

    return 0;
}
/*------SAMPLE OUTPUT------
Dimensions array: 10 30 5 60 

Minimum Scalar Multiplications: 4500
Optimal Parenthesization: ((A1A2)A3)
*/