#include <stdio.h>
#include <string.h>

#define MAX 100

// Helper function to return the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to compute LCS length and reconstruct the string
void lcs(char *X, char *Y) {
    int m = strlen(X);
    int n = strlen(Y);

    // Dynamic Programming table L[m+1][n+1]
    int L[m + 1][n + 1];

    // Build the DP table in bottom-up manner
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                L[i][j] = 0;
            } else if (X[i - 1] == Y[j - 1]) {
                L[i][j] = L[i - 1][j - 1] + 1;
            } else {
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
            }
        }
    }

    // Length of LCS is stored in L[m][n]
    int lcs_length = L[m][n];
    printf("Length of Longest Common Subsequence: %d\n", lcs_length);

    // Reconstruct the actual LCS string
    char lcs_str[lcs_length + 1];
    lcs_str[lcs_length] = '\0'; // Set null terminator

    int i = m, j = n;
    int index = lcs_length - 1;

    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs_str[index] = X[i - 1]; // Character is part of LCS
            i--;
            j--;
            index--;
        } else if (L[i - 1][j] > L[i][j - 1]) {
            i--; // Move up
        } else {
            j--; // Move left
        }
    }

    printf("Longest Common Subsequence: %s\n", lcs_str);
}

int main() {
    char X[MAX], Y[MAX];

    printf("Enter first string (X): ");
    scanf("%s", X);

    printf("Enter second string (Y): ");
    scanf("%s", Y);

    lcs(X, Y);

    return 0;
}/*------SAMPLE OUTPUT----------
Enter first string (X): ASRED
Enter second string (Y): RDTASR
Length of Longest Common Subsequence: 3
Longest Common Subsequence: ASR
*/