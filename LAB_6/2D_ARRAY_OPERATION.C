#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 100

// (i) Matrix Addition: O(n^2)
void matrix_addition(int n, double A[MAX_N][MAX_N], double B[MAX_N][MAX_N], double C[MAX_N][MAX_N]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// (ii) Matrix Multiplication: O(n^3)
void matrix_multiplication(int n, double A[MAX_N][MAX_N], double B[MAX_N][MAX_N], double C[MAX_N][MAX_N]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// (iii) Finding if zero matrix: O(n^2)
int is_zero_matrix(int n, double A[MAX_N][MAX_N]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j] != 0) return 0;
        }
    }
    return 1;
}

// (iv) Finding if symmetric matrix: O(n^2)
int is_symmetric(int n, double A[MAX_N][MAX_N]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j] != A[j][i]) return 0;
        }
    }
    return 1;
}

// (v) Computing determinant using Gaussian Elimination: O(n^3)
double compute_determinant(int n, double A[MAX_N][MAX_N]) {
    double mat[MAX_N][MAX_N];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mat[i][j] = A[i][j];

    double det = 1.0;
    for (int i = 0; i < n; i++) {
        int pivot = i;
        while (pivot < n && fabs(mat[pivot][i]) < 1e-9) pivot++;
        if (pivot == n) return 0.0;
        if (pivot != i) {
            for (int j = 0; j < n; j++) {
                double temp = mat[i][j];
                mat[i][j] = mat[pivot][j];
                mat[pivot][j] = temp;
            }
            det = -det;
        }
        det *= mat[i][i];
        for (int j = i + 1; j < n; j++) {
            double factor = mat[j][i] / mat[i][i];
            for (int k = i; k < n; k++) {
                mat[j][k] -= factor * mat[i][k];
            }
        }
    }
    return det;
}

// (vi) Transposing the matrix in situ (in place): O(n^2)
void transpose_in_place(int n, double A[MAX_N][MAX_N]) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
    }
}

void print_matrix(int n, double A[MAX_N][MAX_N]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.2f ", A[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    printf("Enter the size of the square matrix (n): ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_N) {
        printf("Invalid size!\n");
        return 1;
    }

    double A[MAX_N][MAX_N];
    double B[MAX_N][MAX_N];
    double C[MAX_N][MAX_N];

    printf("Enter elements for Matrix A (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }

    printf("Enter elements for Matrix B (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &B[i][j]);
        }
    }

    // (i) Addition
    matrix_addition(n, A, B, C);
    printf("\n--- (i) Matrix Addition (A + B) ---\n");
    print_matrix(n, C);

    // (ii) Multiplication
    matrix_multiplication(n, A, B, C);
    printf("\n--- (ii) Matrix Multiplication (A * B) ---\n");
    print_matrix(n, C);

    // (iii) Zero Matrix check
    printf("\n--- (iii) Zero Matrix Check ---\n");
    printf("Matrix A is a zero matrix? %s\n", is_zero_matrix(n, A) ? "Yes" : "No");
    printf("Matrix B is a zero matrix? %s\n", is_zero_matrix(n, B) ? "Yes" : "No");

    // (iv) Symmetric check
    printf("\n--- (iv) Symmetry Check ---\n");
    printf("Matrix A is symmetric? %s\n", is_symmetric(n, A) ? "Yes" : "No");
    printf("Matrix B is symmetric? %s\n", is_symmetric(n, B) ? "Yes" : "No");

    // (v) Determinants
    printf("\n--- (v) Determinants ---\n");
    printf("Determinant of Matrix A: %.2f\n", compute_determinant(n, A));
    printf("Determinant of Matrix B: %.2f\n", compute_determinant(n, B));

    // (vi) In-place Transpose
    transpose_in_place(n, A);
    printf("\n--- (vi) In-place Transpose of Matrix A ---\n");
    print_matrix(n, A);

    return 0;
} /* ----------SAMPLE OUTPUT-----------
Enter elements for Matrix A (2x2):
1 2
2 1
Enter elements for Matrix B (2x2):
3 4
4 3

--- (i) Matrix Addition (A + B) ---
    4.00     6.00 
    6.00     4.00 

--- (ii) Matrix Multiplication (A * B) ---
   11.00    10.00 
   10.00    11.00 

--- (iii) Zero Matrix Check ---
Matrix A is a zero matrix? No
Matrix B is a zero matrix? No

--- (iv) Symmetry Check ---
Matrix A is symmetric? Yes
Matrix B is symmetric? Yes

--- (v) Determinants ---
Determinant of Matrix A: -3.00
Determinant of Matrix B: -7.00

--- (vi) In-place Transpose of Matrix A ---
    1.00     2.00 
    2.00     1.00 
*/