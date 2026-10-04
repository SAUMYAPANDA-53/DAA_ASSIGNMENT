/*----ALGORITHM-------Algorithm: Maximum Sum Increasing Subsequence (MSIS)

Input: An array A of n positive integers
Output: The maximum sum of a strictly increasing subsequence in A

1. Create an auxiliary array MSIS of size n.
2. For i from 0 to n - 1:
    a. Initialize MSIS[i] = A[i]
    b. For j from 0 to i - 1:
        i. If A[j] < A[i] and MSIS[i] < MSIS[j] + A[i]:
            Set MSIS[i] = MSIS[j] + A[i]
3. Set max_sum = 0
4. For i from 0 to n - 1:
    a. If MSIS[i] > max_sum:
        Set max_sum = MSIS[i]
5. Return max_sum
 */
#include <stdio.h>
#include <stdlib.h>

int maxSumIS(int A[], int n) {
    int *MSIS = (int *)malloc(n * sizeof(int)), max_sum = 0;

    for (int i = 0; i < n; i++) {
        MSIS[i] = A[i];
        for (int j = 0; j < i; j++)
            if (A[j] < A[i] && MSIS[i] < MSIS[j] + A[i])
                MSIS[i] = MSIS[j] + A[i];
        
        if (MSIS[i] > max_sum) max_sum = MSIS[i];
    }

    free(MSIS);
    return max_sum;
}

int main() {
    int n;
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;

    int *A = (int *)malloc(n * sizeof(int));
    printf("Enter %d positive integers: ", n);
    for (int i = 0; i < n; i++) scanf("%d", &A[i]);

    printf("Maximum Sum Increasing Subsequence = %d\n", maxSumIS(A, n));

    free(A);
    return 0;
}/*--------SAMPLE OUTPUT---------Enter number of elements: 6
Enter 6 positive integers: 3 1 4 6 2 8
Maximum Sum Increasing Subsequence = 21
*/