/* ----ALGORITHM
Algorithm TWO_SET_PAIR_SUM(S1, S2, n, x):
    Sort S2 in ascending order  // O(n log n)[cite: 1]
    For each element u in S1:
        target = x - u
        If BINARY_SEARCH(S2, target) == true:
            Return true
    Return false
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Comparison function for qsort (ascending order)
int compare(const void *a, const void *b) {
    int int_a = *((int *)a);
    int int_b = *((int *)b);
    if (int_a < int_b) return -1;
    if (int_a > int_b) return 1;
    return 0;
}

// Binary search implementation to find target in array arr of size n
int binarySearch(int arr[], int n, int target) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target)
            return 1; // Found
        else if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return 0; // Not found
}

// Robust function to read n integers (handles spaces, commas, and newlines)
void readArray(int arr[], int n) {
    int count = 0;
    while (count < n) {
        char buffer[512];
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) break;
        char *token = strtok(buffer, " ,\n\t\r");
        while (token != NULL && count < n) {
            arr[count++] = atoi(token);
            token = strtok(NULL, " ,\n\t\r");
        }
    }
}

int main() {
    int n;
    printf("Enter the size of sets (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size.\n");
        return 1;
    }
    
    // Clear the leftover newline from the input buffer
    while (getchar() != '\n');

    int *S1 = (int *)malloc(n * sizeof(int));
    int *S2 = (int *)malloc(n * sizeof(int));

    printf("Enter %d elements for set S1 (spaces or commas work):\n", n);
    readArray(S1, n);

    printf("Enter %d elements for set S2 (spaces or commas work):\n", n);
    readArray(S2, n);

    int x;
    printf("Enter the target sum x: ");
    scanf("%d", &x);

    // Step 1: Sort S2 in O(n log n) time
    qsort(S2, n, sizeof(int), compare);

    // Step 2: Iterate through S1 and find ALL pairs (using binary search)
    int foundCount = 0;
    printf("\nFinding all pairs such that a (from S1) + b (from S2) = %d:\n", x);
    
    for (int i = 0; i < n; i++) {
        int a = S1[i];
        int b = x - a;

        if (binarySearch(S2, n, b)) {
            printf("Found pair: a = %d (from S1), b = %d (from S2)\n", a, b);
            foundCount++;
        }
    }

    if (foundCount == 0) {
        printf("No pair found that adds up to %d.\n", x);
    } else {
        printf("\nTotal unique match checks found: %d\n", foundCount);
    }

    free(S1);
    free(S2);
    return 0;
}/*  --- SAMPLE INPUT & OUTPUT ---
Enter the size of sets (n): 4
Enter 4 elements for set S1 (spaces or commas work):
1,4,3,5
Enter 4 elements for set S2 (spaces or commas work):
5,7,3,9
Enter the target sum x: 10

Finding all pairs such that a (from S1) + b (from S2) = 10:
Found pair: a = 1 (from S1), b = 9 (from S2)
Found pair: a = 3 (from S1), b = 7 (from S2)
Found pair: a = 5 (from S1), b = 5 (from S2)

Total unique match checks found: 3
*/