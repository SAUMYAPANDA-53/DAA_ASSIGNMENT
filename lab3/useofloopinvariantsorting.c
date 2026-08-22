#include <stdio.h>

void selectionSort(int arr[], int n) {
    // Loop invariant: At the start of each iteration i, 
    // the subarray arr[0 ... i-1] contains the i smallest elements 
    // of the array in sorted order.
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        
        // Find the smallest element in the remaining unsorted array arr[i ... n-1]
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        
        // Exchange the found minimum element with the element at index i
        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

int main() {
    int n;
    printf("Enter the number of elements (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input.\n");
        return 0;
    }

    int arr[n];
    printf("Enter %d elements (separated by spaces or newlines):\n", n);
    for (int i = 0; i < n; i++) {
        while (scanf("%d", &arr[i]) != 1) {
            // Clear invalid input buffer if non-integer is entered
            while (getchar() != '\n');
            printf("Invalid input. Re-enter element %d: ", i + 1);
        }
    }

    selectionSort(arr, n);

    printf("Sorted array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
/* SAMPLE OUTPUT 
Enter the number of elements (n): 5
Enter 5 elements (separated by spaces or newlines):
1 3 2 6 2
Sorted array:
1 2 2 3 6 
*/