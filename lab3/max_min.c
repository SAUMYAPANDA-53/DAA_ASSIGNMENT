/*Algorithm FindMaxMin(arr, low, high, max, min)
Input: 
    - arr: An array of numbers
    - low, high: Starting and ending indices of the current segment
Output: 
    - max: Maximum element in arr[low...high]
    - min: Minimum element in arr[low...high]

1.  // Case 1: Only one element
    if low == high then
        *max = arr[low]
        *min = arr[low]
        return
    end if

2.  // Case 2: Two elements
    if high == low + 1 then
        if arr[low] > arr[high] then
            *max = arr[low]
            *min = arr[high]
        else
            *max = arr[high]
            *min = arr[low]
        end if
        Increment comparison count
        return
    end if

3.  // Case 3: More than two elements (Divide and Conquer)
    mid = low + (high - low) / 2
    
    // Declare local variables for sub-results
    FindMaxMin(arr, low, mid, max1, min1)
    FindMaxMin(arr, mid + 1, high, max2, min2)

    // Combine step: compare maximums and minimums of both halves
    if max1 > max2 then
        *max = max1
    else
        *max = max2
    end if

    if min1 < min2 then
        *min = min1
    else
        *min = min2
    end if
    
    Increment comparison counts for the combinations
    */

#include <stdio.h>

// Global variable to track the number of comparisons
int comparisons = 0;

// Divide and Conquer function to find Max and Min
void findMaxMin(int arr[], int low, int high, int *max, int *min) {
    // If there is only one element
    if (low == high) {
        *max = arr[low];
        *min = arr[low];
        return;
    }

    // If there are two elements
    if (high == low + 1) {
        comparisons++; // 1 comparison
        if (arr[low] > arr[high]) {
            *max = arr[low];
            *min = arr[high];
        } else {
            *max = arr[high];
            *min = arr[low];
        }
        return;
    }

    // If there are more than two elements, divide into two halves
    int mid = low + (high - low) / 2;
    int max1, min1, max2, min2;

    // Conquer: recursively find max and min in left and right halves
    findMaxMin(arr, low, mid, &max1, &min1);
    findMaxMin(arr, mid + 1, high, &max2, &min2);

    // Combine: compare results of both halves
    comparisons++; // Comparison for maximums
    if (max1 > max2) {
        *max = max1;
    } else {
        *max = max2;
    }

    comparisons++; // Comparison for minimums
    if (min1 < min2) {
        *min = min1;
    } else {
        *min = min2;
    }
}

int main() {
    int n;

    printf("--- MAX AND MIN USING D&C APPROACH ---\n");
    printf("Enter the number of elements in the array (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size!\n");
        return 1;
    }

    int arr[n];
    printf("Enter %d elements (space or comma separated):\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        
        // Robustly consume any trailing commas, spaces, or tabs left by scanf
        int ch;
        do {
            ch = getchar();
        } while (ch == ',' || ch == ' ' || ch == '\t');
        if (ch != '\n' && ch != EOF) {
            ungetc(ch, stdin);
        }
    }

    comparisons = 0;
    int max, min;

    // Call D&C function
    findMaxMin(arr, 0, n - 1, &max, &min);

    // Display Results
    printf("\n--- RESULTS ---");
    printf("\nMaximum element: %d", max);
    printf("\nMinimum element: %d", min);
    printf("\nTotal comparisons made: %d", comparisons);
    
    // Validation check for 3n/2 bound
    double bound = (3.0 * n) / 2.0;
    printf("\nTheoretical upper bound (3n/2): %.2f", bound);
    printf("\nValidation: Comparisons (%d) <= 3n/2 (%.2f) is %s.\n", 
           comparisons, bound, (comparisons <= bound) ? "SATISFIED" : "NOT SATISFIED");

    return 0;
}/* SAMPLE OUTPUT
--- LAB QUESTION 3: MAX AND MIN USING D&C APPROACH ---
Enter the number of elements in the array (n): 5
Enter 5 elements (space or comma separated):
1,4,2,5,6

--- RESULTS ---
Maximum element: 6
Minimum element: 1
Total comparisons made: 6
Theoretical upper bound (3n/2): 7.50
Validation: Comparisons (6) <= 3n/2 (7.50) is SATISFIED.
*/