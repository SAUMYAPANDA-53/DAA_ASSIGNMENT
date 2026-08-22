/* ALGORITHM 

Algorithm K_SUM(S, n, k, T):
    Sort S in ascending order  // O(n log n)[cite: 1]
    If k == 2:
        left = 1, right = n
        While left < right:
            sum = S[left] + S[right]
            If sum == T: Return true
            Else if sum < T: left = left + 1
            Else: right = right - 1
        Return false
    Else:
        For i = 1 to n - (k - 1):
            If K_SUM(S excluding S[i], n - 1, k - 1, T - S[i]) == true:
                Return true
        Return false
*/

#include <stdio.h>
#include <stdlib.h>

// Comparison function required by qsort for sorting integers
int compare(const void *a, const void *b) {
    int int_a = *((const int *)a);
    int int_b = *((const int *)b);
    if (int_a < int_b) return -1;
    if (int_a > int_b) return 1;
    return 0;
}

// Binary search function to find element x in S[low...high]
int binarySearch(int S[], int low, int high, int x) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (S[mid] == x)
            return 1; // Found
        if (S[mid] < x)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return 0; // Not found
}

// Recursive helper function for k-sum
int kSumHelper(int S[], int start, int end, int k, int target) {
    // Base case: when k = 1, check if target exists via binary search
    if (k == 1) {
        return binarySearch(S, start, end, target);
    }

    // Iterate through possible choices for the first of the k elements
    for (int i = start; i <= end - k + 1; i++) {
        // Recurse for k-1 elements with the reduced target
        if (kSumHelper(S, i + 1, end, k - 1, target - S[i])) {
            return 1;
        }
    }
    return 0;
}

// Main function to check if k numbers in S sum up to T
int hasKSum(int S[], int n, int k, int target) {
    if (k <= 0 || k > n) {
        return 0; // Invalid k value
    }

    // Step 1: Sort the array in O(n log n) time
    qsort(S, n, sizeof(int), compare);

    // Step 2: Find k-sum using recursive helper and binary search
    return kSumHelper(S, 0, n - 1, k, target);
}

int main() {
    // Test Case 1: 3-SUM problem
    int S1[] = {1, 15, 4, 20, 9, 8, 12};
    int n1 = sizeof(S1) / sizeof(S1[0]);
    int k1 = 3;
    int target1 = 24; // e.g., 4 + 8 + 12 = 24

    printf("--- Test Case 1 (3-SUM) ---\n");
    printf("Set S1: { ");
    for (int i = 0; i < n1; i++) printf("%d ", S1[i]);
    printf("}\n");
    printf("Parameters: k = %d, Target T = %d\n", k1, target1);

    if (hasKSum(S1, n1, k1, target1)) {
        printf("Result: SUCCESS! There exist %d integers in S1 that add up to %d.\n\n", k1, target1);
    } else {
        printf("Result: No such %d integers found that add up to %d.\n\n", k1, target1);
    }

    // Test Case 2: 4-SUM problem
    int S2[] = {2, 7, 4, 0, 9, 5, 1, 3};
    int n2 = sizeof(S2) / sizeof(S2[0]);
    int k2 = 4;
    int target2 = 20; 

    printf("--- Test Case 2 (4-SUM) ---\n");
    printf("Set S2: { ");
    for (int i = 0; i < n2; i++) printf("%d ", S2[i]);
    printf("}\n");
    printf("Parameters: k = %d, Target T = %d\n", k2, target2);

    if (hasKSum(S2, n2, k2, target2)) {
        printf("Result: SUCCESS! There exist %d integers in S2 that add up to %d.\n", k2, target2);
    } else {
        printf("Result: No such %d integers found that add up to %d.\n", k2, target2);
    }

    return 0;
}
/*  SAMPLE TEST CASES 
--- Test Case 1 (3-SUM) ---
Set S1: { 1 15 4 20 9 8 12 }
Parameters: k = 3, Target T = 24
Result: SUCCESS! There exist 3 integers in S1 that add up to 24.

--- Test Case 2 (4-SUM) ---
Set S2: { 2 7 4 0 9 5 1 3 }
Parameters: k = 4, Target T = 20
Result: SUCCESS! There exist 4 integers in S2 that add up to 20.
*/