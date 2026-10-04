#include <stdio.h>
#include <limits.h>

// Function to find the minimum number of coins needed
int minCoins(int C[], int n, int V) {
    int dp[V + 1];

    // Base case: 0 amount requires 0 coins
    dp[0] = 0;

    // Initialize all other positions with infinity (INT_MAX)
    for (int i = 1; i <= V; i++) {
        dp[i] = INT_MAX;
    }

    // Compute minimum coins required for all values from 1 to V
    for (int i = 1; i <= V; i++) {
        for (int j = 0; j < n; j++) {
            if (C[j] <= i) {
                int sub_res = dp[i - C[j]];
                if (sub_res != INT_MAX && sub_res + 1 < dp[i]) {
                    dp[i] = sub_res + 1;
                }
            }
        }
    }

    // Return -1 if target amount cannot be formed
    return (dp[V] == INT_MAX) ? -1 : dp[V];
}

int main() {
    int n, V;

    // 1. Get the number of coin denominations
    printf("Enter the number of coin denominations: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of coins.\n");
        return 1;
    }

    int C[n];

    // 2. Get the coin denominations array from user
    printf("Enter the coin denominations:\n");
    for (int i = 0; i < n; i++) {
        printf("Coin %d: ", i + 1);
        scanf("%d", &C[i]);
    }

    // 3. Get the target amount V
    printf("Enter the target amount V: ");
    scanf("%d", &V);

    if (V < 0) {
        printf("Target amount cannot be negative.\n");
        return 1;
    }

    // Solve and display result
    int result = minCoins(C, n, V);

    if (result != -1) {
        printf("\nMinimum coins needed for target %d is: %d\n", V, result);
    } else {
        printf("\nAmount %d cannot be made with the given coin denominations.\n", V);
    }

    return 0;
}
/* --------- SAMPLE OUTPUT ----------
 Enter the number of coin denominations: 3
 Enter the coin denominations:
 Coin 1: 1
 Coin 2: 3
 Coin 3: 5
 Enter the target amount V: 10

 Minimum coins needed for target 10 is: 2 */