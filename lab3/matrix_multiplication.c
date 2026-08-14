#include <stdio.h>
#include <stdlib.h>

// Function to add two matrices A and B of size n x n
void add(int n, int A[][n], int B[][n], int C[][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Function to subtract two matrices A and B of size n x n
void sub(int n, int A[][n], int B[][n], int C[][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Function to implement Strassen's Algorithm recursively
void strassen(int n, int A[][n], int B[][n], int C[][n]) {
    // Base case: if matrix size is 1 x 1
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    // Declare submatrices using VLA
    int A11[k][k], A12[k][k], A21[k][k], A22[k][k];
    int B11[k][k], B12[k][k], B21[k][k], B22[k][k];
    int M1[k][k], M2[k][k], M3[k][k], M4[k][k], M5[k][k], M6[k][k], M7[k][k];
    int tempA[k][k], tempB[k][k];
    int C11[k][k], C12[k][k], C21[k][k], C22[k][k];

    // Divide matrices into 4 submatrices
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // Step 1: M1 = (A11 + A22) * (B11 + B22)
    add(k, A11, A22, tempA);
    add(k, B11, B22, tempB);
    strassen(k, tempA, tempB, M1);

    // Step 2: M2 = (A21 + A22) * B11
    add(k, A21, A22, tempA);
    strassen(k, tempA, B11, M2);

    // Step 3: M3 = A11 * (B12 - B22)
    sub(k, B12, B22, tempB);
    strassen(k, A11, tempB, M3);

    // Step 4: M4 = A22 * (B21 - B11)
    sub(k, B21, B11, tempB);
    strassen(k, A22, tempB, M4);

    // Step 5: M5 = (A11 + A12) * B22
    add(k, A11, A12, tempA);
    strassen(k, tempA, B22, M5);

    // Step 6: M6 = (A21 - A11) * (B11 + B12)
    sub(k, A21, A11, tempA);
    add(k, B11, B12, tempB);
    strassen(k, tempA, tempB, M6);

    // Step 7: M7 = (A12 - A22) * (B21 + B22)
    sub(k, A12, A22, tempA);
    add(k, B21, B22, tempB);
    strassen(k, tempA, tempB, M7);

    // Calculate C submatrices:
    add(k, M1, M4, tempA);
    sub(k, tempA, M5, tempB);
    add(k, tempB, M7, C11);

    add(k, M3, M5, C12);

    add(k, M2, M4, C21);

    sub(k, M1, M2, tempA);
    add(k, tempA, M3, tempB);
    add(k, tempB, M6, C22);

    // Combine C submatrices into result matrix C
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }
}

int main() {
    int n;

    printf("--- STRASSEN'S MATRIX MULTIPLICATION ---\n");
    printf("Enter the size of the square matrix (must be a power of 2, e.g., 2, 4, 8): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size!\n");
        return 1;
    }

    int A[n][n], B[n][n], C[n][n];

    printf("Enter elements of matrix A (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter elements of matrix B (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    // Initialize result matrix with zeros
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
        }
    }

    // Perform Strassen's Multiplication
    strassen(n, A, B, C);

    // Display Result Matrix
    printf("\n--- RESULTANT MATRIX C (A x B) ---\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d \t", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}/* SAMPLE INPUT 
--- STRASSEN'S MATRIX MULTIPLICATION ---
Enter the size of the square matrix (must be a power of 2, e.g., 2, 4, 8): 2
Enter elements of matrix A (2x2):
1 2
3 4
Enter elements of matrix B (2x2):
2 3
4 5

------- SAMPLE OUTPUT -----

--- RESULTANT MATRIX C (A x B) ---
10      13 
22      29 */