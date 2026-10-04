/*---------ALGORITHM---------ALGORITHM EditDistanceWithTraceback(A, B):
    m = length(A)
    n = length(B)
    
    // Step 1: Initialize DP Table
    Create 2D array dp[0..m][0..n]
    
    For i = 0 to m:
        dp[i][0] = i
    For j = 0 to n:
        dp[0][j] = j

    // Step 2: Fill DP Table
    For i = 1 to m:
        For j = 1 to n:
            if A[i-1] == B[j-1]:
                cost = 0
            else:
                cost = 1
                
            dp[i][j] = MIN(
                dp[i-1][j] + 1,        // Deletion
                dp[i][j-1] + 1,        // Insertion
                dp[i-1][j-1] + cost    // Substitution / Match
            )

    // Step 3: Traceback Operations
    i = m, j = n
    ops = empty list

    While i > 0 or j > 0:
        if i > 0 and j > 0 and A[i-1] == B[j-1] and dp[i][j] == dp[i-1][j-1]:
            Append "Keep " + A[i-1] to ops
            i = i - 1, j = j - 1
        else if i > 0 and j > 0 and dp[i][j] == dp[i-1][j-1] + 1:
            Append "Substitute " + A[i-1] + " -> " + B[j-1] to ops
            i = i - 1, j = j - 1
        else if i > 0 and dp[i][j] == dp[i-1][j] + 1:
            Append "Delete " + A[i-1] to ops
            i = i - 1
        else:
            Append "Insert " + B[j-1] to ops
            j = j - 1

    // Step 4: Output Result
    Print "Minimum Distance: " + dp[m][n]
    Print Reverse(ops)
*/

#include <stdio.h>
#include <string.h>

int min3(int a, int b, int c) {
    if (a <= b && a <= c) return a;
    if (b <= a && b <= c) return b;
    return c;
}

void edit_distance(char *A, char *B) {
    int m = strlen(A), n = strlen(B);
    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int cost = (A[i - 1] == B[j - 1]) ? 0 : 1;
            dp[i][j] = min3(dp[i - 1][j] + 1,        // Delete
                            dp[i][j - 1] + 1,        // Insert
                            dp[i - 1][j - 1] + cost); // Replace / Match
        }
    }

    printf("\nMinimum Edit Distance: %d\n\nTraceback:\n", dp[m][n]);

    int i = m, j = n, count = 0;
    char ops[m + n][50];

    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && A[i - 1] == B[j - 1] && dp[i][j] == dp[i - 1][j - 1]) {
            sprintf(ops[count++], "Keep '%c'", A[--i]);
            j--;
        } else if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + 1) {
            sprintf(ops[count++], "Substitute '%c' -> '%c'", A[--i], B[--j]);
        } else if (i > 0 && dp[i][j] == dp[i - 1][j] + 1) {
            sprintf(ops[count++], "Delete '%c'", A[--i]);
        } else {
            sprintf(ops[count++], "Insert '%c'", B[--j]);
        }
    }

    for (int k = count - 1; k >= 0; k--) {
        printf("- %s\n", ops[k]);
    }
}

int main() {
    char A[100], B[100];

    printf("Enter String A: ");
    scanf("%99s", A);

    printf("Enter String B: ");
    scanf("%99s", B);

    edit_distance(A, B);

    return 0;
}/*------SAMPLE OUTPUT----------Enter String A: SAMMYT
Enter String B: SMMYAT

Minimum Edit Distance: 2

Traceback:
- Keep 'S'
- Delete 'A'
- Keep 'M'
- Keep 'M'
- Keep 'Y'
- Insert 'A'
- Keep 'T'
*/