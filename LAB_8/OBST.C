/*-------PSEUDOCODE------------
ALGORITHM OptimalBST(p, q, n):
    For i = 1 to n + 1:
        e[i][i - 1] = q[i - 1]
        w[i][i - 1] = q[i - 1]

    For l = 1 to n:                  // l is chain length
        For i = 1 to n - l + 1:
            j = i + l - 1
            e[i][j] = INFINITY
            w[i][j] = w[i][j - 1] + p[j] + q[j]
            For r = i to j:          // try all roots r
                t = e[i][r - 1] + e[r + 1][j] + w[i][j]
                if t < e[i][j]:
                    e[i][j] = t

    RETURN e[1][n]
*/
#include <stdio.h>
#define MAX 100
#define INF 1e9

int main() {
    int n;
    float p[MAX], q[MAX], e[MAX][MAX], w[MAX][MAX];

    printf("Enter number of keys (n): ");
    scanf("%d", &n);

    printf("Enter %d probabilities (p1 to p%d): ", n, n);
    for (int i = 1; i <= n; i++) scanf("%f", &p[i]);

    printf("Enter %d dummy probabilities (q0 to q%d): ", n + 1, n);
    for (int i = 0; i <= n; i++) scanf("%f", &q[i]);

    // Base cases
    for (int i = 1; i <= n + 1; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    // Dynamic Programming
    for (int l = 1; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            e[i][j] = INF;
            w[i][j] = w[i][j - 1] + p[j] + q[j];

            for (int r = i; r <= j; r++) {
                float t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (t < e[i][j]) {
                    e[i][j] = t;
                }
            }
        }
    }

    printf("Minimum Expected Search Cost: %.4f\n", e[1][n]);
    return 0;
}
/*-------SAMPLE OUTPUT----------
Enter number of keys (n): 5
Enter 5 probabilities (p1 to p5): .2
.3
.4
.1
.4
Enter 6 dummy probabilities (q0 to q5): .4
.2
.1 
.4
.7
.8
Minimum Expected Search Cost: 12.0000
*/