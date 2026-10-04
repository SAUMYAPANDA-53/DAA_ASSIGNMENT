#include <stdio.h>
#include <stdlib.h>

int totalWays = 0;

// Function to recursively find and print all valid coin combinations
void findCombinations(int coins[], int n, int V, int index, int currentCombination[], int coinCount) {
    // Base Case: Target amount reached
    if (V == 0) {
        totalWays++;
        printf("  Way %d: { ", totalWays);
        for (int i = 0; i < coinCount; i++) {
            printf("%d ", currentCombination[i]);
        }
        printf("}\n");
        return;
    }

    // Base Case: Target exceeded or no more coins available
    if (V < 0 || index >= n) {
        return;
    }

    // Option 1: Include the current coin coins[index] (stay on current index for infinite supply)
    currentCombination[coinCount] = coins[index];
    findCombinations(coins, n, V - coins[index], index, currentCombination, coinCount + 1);

    // Option 2: Exclude the current coin and move to the next denomination
    findCombinations(coins, n, V, index + 1, currentCombination, coinCount);
}

int main() {
    int n, V;

    printf("Enter number of coin denominations: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    int *coins = (int *)malloc(n * sizeof(int));
    if (coins == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter the coin denominations:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &coins[i]);
    }

    printf("Enter the target amount (V): ");
    if (scanf("%d", &V) != 1 || V < 0) {
        printf("Invalid target amount.\n");
        free(coins);
        return 1;
    }

    // Array to store the current combination path
    // Max capacity bound by V (when smallest coin is 1)
    int *currentCombination = (int *)malloc((V + 1) * sizeof(int));

    printf("\n--- Combinations forming amount %d ---\n", V);
    findCombinations(coins, n, V, 0, currentCombination, 0);

    if (totalWays == 0) {
        printf("No valid coin combinations found.\n");
    }

    printf("\nTotal distinct ways: %d\n", totalWays);

    free(coins);
    free(currentCombination);
    return 0;
}
/*--------SAMPLE OUTPUT---------
Enter number of coin denominations: 3
Enter the coin denominations:
2
3
4
Enter the target amount (V): 5

--- Combinations forming amount 5 ---
  Way 1: { 2 3 }

Total distinct ways: 1
*/