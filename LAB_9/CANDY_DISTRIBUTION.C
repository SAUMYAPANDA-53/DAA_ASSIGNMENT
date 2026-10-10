/*-----PSEUDOCODE---------
Algorithm CandyDistribution(ratings, n):
    // Step 1: Initialize an array of size n with 1s (each child gets at least one candy)
    Initialize array candies of size n with all elements set to 1
    
    // Step 2: Left-to-Right pass (Forward check)
    For i from 1 to n - 1:
        If ratings[i] > ratings[i - 1] then
            candies[i] = candies[i - 1] + 1
        End If
    End For
    
    // Step 3: Right-to-Left pass (Backward check)
    For i from n - 2 down to 0:
        If ratings[i] > ratings[i + 1] then
            candies[i] = max(candies[i], candies[i + 1] + 1)
        End If
    End For
    
    // Step 4: Calculate the total minimum candies needed
    totalCandies = 0
    For i from 0 to n - 1:
        totalCandies = totalCandies + candies[i]
    End For
    
    Return totalCandies
*/

#include <stdio.h>

// Function to find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to calculate the minimum candies using Bi-directional Slope Greedy approach
int candyDistribution(int ratings[], int n) {
    if (n <= 0) return 0;

    int candies[n];
    
    // Step 1: Each child must get at least one candy
    for (int i = 0; i < n; i++) {
        candies[i] = 1;
    }

    // Step 2: Left-to-Right pass
    for (int i = 1; i < n; i++) {
        if (ratings[i] > ratings[i - 1]) {
            candies[i] = candies[i - 1] + 1;
        }
    }

    // Step 3: Right-to-Left pass
    for (int i = n - 2; i >= 0; i--) {
        if (ratings[i] > ratings[i + 1]) {
            candies[i] = max(candies[i], candies[i + 1] + 1);
        }
    }

    // Step 4: Find the minimum total number of candies needed
    int totalCandies = 0;
    for (int i = 0; i < n; i++) {
        totalCandies += candies[i];
    }

    return totalCandies;
}

int main() {
    // Predefined input representation for validation
    int ratings[] = {1, 0, 2};
    int n = sizeof(ratings) / sizeof(ratings[0]);

    int minCandies = candyDistribution(ratings, n);
    printf("Minimum total number of candies needed: %d\n", minCandies);

    return 0;
}