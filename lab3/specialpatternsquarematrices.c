#include <stdio.h>
#include <stdlib.h>

// Function to add two special-pattern matrices: (R1, R2) = (A1, A2) + (B1, B2)
void specialAdd(int n, int A1[n][n], int A2[n][n], int B1[n][n], int B2[n][n], int R1[n][n], int R2[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            R1[i][j] = A1[i][j] + B1[i][j];
            R2[i][j] = A2[i][j] + B2[i][j];
        }
    }
}

// Function to subtract two special-pattern matrices: (R1, R2) = (A1, A2) - (B1, B2)
void specialSub(int n, int A1[n][n], int A2[n][n], int B1[n][n], int B2[n][n], int R1[n][n], int R2[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            R1[i][j] = A1[i][j] - B1[i][j];
            R2[i][j] = A2[i][j] - B2[i][j];
        }
    }
}

// Recursive function to multiply special-pattern matrices
void specialMultiply(int n, int A1[n][n], int A2[n][n], 
                           int B1[n][n], int B2[n][n], 
                           int C1[n][n], int C2[n][n]) {
    // Base case: 1x1 matrices
    if (n == 1) {
        int a1 = A1[0][0], a2 = A2[0][0];
        int b1 = B1[0][0], b2 = B2[0][0];
        C1[0][0] = a1 * b1 + a2 * b2;
        C2[0][0] = a1 * b2 + a2 * b1;
        return;
    }

    int k = n / 2;
    
    // Sub-blocks for recursive calls
    int A11[k][k], A12[k][k], A21[k][k], A22[k][k];
    int B11[k][k], B12[k][k], B21[k][k], B22[k][k];
    
    // Decompose A and B into sub-blocks
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A1[i][j];       A12[i][j] = A1[i][j + k];
            A21[i][j] = A2[i][j];       A22[i][j] = A2[i][j + k];
            B11[i][j] = B1[i][j];       B12[i][j] = B1[i][j + k];
            B21[i][j] = B2[i][j];       B22[i][j] = B2[i][j + k];
        }
    }

    // Allocate temporary matrices for 3 recursive multiplications
    int T1_1[k][k], T1_2[k][k];
    int T2_1[k][k], T2_2[k][k];
    int T3_1[k][k], T3_2[k][k];
    int S1_1[k][k], S1_2[k][k];
    int S2_1[k][k], S2_2[k][k];

    // T1 = A1 * B1
    specialMultiply(k, A11, A12, B11, B12, T1_1, T1_2);
    
    // T2 = A2 * B2
    specialMultiply(k, A21, A22, B21, B22, T2_1, T2_2);
    
    // S1 = A1 + A2, S2 = B1 + B2
    specialAdd(k, A11, A12, A21, A22, S1_1, S1_2);
    specialAdd(k, B11, B12, B21, B22, S2_1, S2_2);
    
    // T3 = S1 * S2
    specialMultiply(k, S1_1, S1_2, S2_1, S2_2, T3_1, T3_2);

    // Combine sub-blocks into C1 and C2
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C1[i][j]         = T1_1[i][j] + T2_1[i][j];
            C1[i][j + k]     = T1_2[i][j] + T2_2[i][j];
            C1[i + k][j]     = T1_2[i][j] + T2_2[i][j];
            C1[i + k][j + k] = T1_1[i][j] + T2_1[i][j];

            C2[i][j]         = T3_1[i][j] - T1_1[i][j] - T2_1[i][j];
            C2[i][j + k]     = T3_2[i][j] - T1_2[i][j] - T2_2[i][j];
            C2[i + k][j]     = T3_2[i][j] - T1_2[i][j] - T2_2[i][j];
            C2[i + k][j + k] = T3_1[i][j] - T1_1[i][j] - T2_1[i][j];
        }
    }
}

int main() {
    int k;
    printf("Enter power k for n = 2^k (e.g., 1 or 2): ");
    if (scanf("%d", &k) != 1) return 0;
    int n = 1 << k;

    int A1[n][n], A2[n][n], B1[n][n], B2[n][n];
    int C1[n][n], C2[n][n];

    printf("Enter elements for matrix A1 (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A1[i][j]);

    printf("Enter elements for matrix A2 (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A2[i][j]);

    printf("Enter elements for matrix B1 (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B1[i][j]);

    printf("Enter elements for matrix B2 (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B2[i][j]);

    specialMultiply(n, A1, A2, B1, B2, C1, C2);

    printf("\nResultant Matrix C1:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf("%d ", C1[i][j]);
        printf("\n");
    }

    printf("\nResultant Matrix C2:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf("%d ", C2[i][j]);
        printf("\n");
    }

    return 0;
}
/*  SAMPLE OUTPUT 
Enter power k for n = 2^k (e.g., 1 or 2): 1
Enter elements for matrix A1 (2x2):
1 2
2 1
Enter elements for matrix A2 (2x2):
2 3
3 2
Enter elements for matrix B1 (2x2):
4 6
6 4
Enter elements for matrix B2 (2x2):
4 5
5 4

Resultant Matrix C1:
39 36 
36 39 

Resultant Matrix C2:
40 37 
37 40 
*/