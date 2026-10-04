/*-------ALGORITHM------------
ALGORITHM LongestIncreasingSubsequence_DP(A, n)
    Input: Array A of n integers
    Output: Length of the longest strictly increasing subsequence

    if n == 0 then
        return 0
    end if

    // Initialize DP array where DP[i] represents LIS ending at index i
    Declare array DP of size n
    maxLen = 1

    for i = 0 to n - 1 do
        DP[i] = 1   // Base case: every single element is an IS of length 1

        for j = 0 to i - 1 do
            if A[j] < A[i] then
                DP[i] = max(DP[i], DP[j] + 1)
            end if
        end for

        maxLen = max(maxLen, DP[i])
    end for

    return maxLen
END ALGORITHM
*/


#include <stdio.h>
#include <stdlib.h>

// Dynamic Programming Approach: O(n^2) time, O(n) space
int lengthOfLIS_DP(int* nums, int numsSize) {
    if (numsSize <= 0) return 0;

    int* dp = (int*)malloc(numsSize * sizeof(int));
    int maxLen = 1;

    for (int i = 0; i < numsSize; i++) {
        dp[i] = 1; // Base case: single element has LIS of length 1
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i]) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                }
            }
        }
        if (dp[i] > maxLen) {
            maxLen = dp[i];
        }
    }

    free(dp);
    return maxLen;
}

// Binary Search Helper for Optimal Approach
int binarySearch(int* tails, int size, int target) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (tails[mid] >= target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

// Optimal Approach using Binary Search: O(n log n) time, O(n) space
int lengthOfLIS_Optimal(int* nums, int numsSize) {
    if (numsSize <= 0) return 0;

    int* tails = (int*)malloc(numsSize * sizeof(int));
    int length = 0;

    for (int i = 0; i < numsSize; i++) {
        int idx = binarySearch(tails, length, nums[i]);
        tails[idx] = nums[i];
        if (idx == length) {
            length++;
        }
    }

    free(tails);
    return length;
}

int main() {
    int n;

    printf("Enter the number of elements in the array: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input size.\n");
        return 1;
    }

    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d integers separated by spaces:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("\nInput Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    int lis_dp = lengthOfLIS_DP(arr, n);
    int lis_optimal = lengthOfLIS_Optimal(arr, n);

    printf("Length of LIS (DP - O(n^2)): %d\n", lis_dp);
    printf("Length of LIS (Optimal - O(n log n)): %d\n", lis_optimal);

    free(arr);
    return 0;
}/*----SAMPLE OUTPUT----------
Enter the number of elements in the array: 7
Enter 7 integers separated by spaces:
3 2 1 3 4 5 2

Input Array: 3 2 1 3 4 5 2 
Length of LIS (DP - O(n^2)): 4
Length of LIS (Optimal - O(n log n)): 4
*/