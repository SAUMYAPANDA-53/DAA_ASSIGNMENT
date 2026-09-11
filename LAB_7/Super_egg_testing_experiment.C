#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Utility function to find maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to solve Egg Dropping Problem using Dynamic Programming
int super_egg_drop(int E, int F) {
    // DP table where dp[i][j] represents min trials for i eggs and j floors
    int dp[E + 1][F + 1];

    // Base case 1: 0 or 1 floor
    for (int i = 1; i <= E; i++) {
        dp[i][0] = 0;
        dp[i][1] = 1;
    }

    // Base case 2: 1 egg requires j trials for j floors
    for (int j = 1; j <= F; j++) {
        dp[1][j] = j;
    }

    // Fill the rest of the DP table
    for (int i = 2; i <= E; i++) {
        for (int j = 2; j <= F; j++) {
            dp[i][j] = INT_MAX;
            
            // Try dropping from every floor k from 1 to j
            for (int k = 1; k <= j; k++) {
                int res = 1 + max(dp[i - 1][k - 1], dp[i][j - k]);
                if (res < dp[i][j]) {
                    dp[i][j] = res;
                }
            }
        }
    }

    return dp[E][F];
}

int main() {
    int E, F;

    printf("=== Super Egg Testing Experiment ===\n");
    printf("Enter number of eggs (E): ");
    if (scanf("%d", &E) != 1 || E <= 0) {
        printf("Invalid input for eggs.\n");
        return 1;
    }

    printf("Enter number of floors (F): ");
    if (scanf("%d", &F) != 1 || F < 0) {
        printf("Invalid input for floors.\n");
        return 1;
    }

    int min_attempts = super_egg_drop(E, F);

    printf("\nMinimum number of droppings guaranteed in worst case for %d eggs and %d floors: %d\n", 
           E, F, min_attempts);

    return 0;
}
/*--------SAMPLE OUTPUT--------
=== Super Egg Testing Experiment ===
Enter number of eggs (E): 5
Enter number of floors (F): 4

Minimum number of droppings guaranteed in worst case for 5 eggs and 4 floors: 3
*/