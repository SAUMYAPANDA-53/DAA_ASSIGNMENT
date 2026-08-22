#include <stdio.h>

// Function to perform Binary Search and count comparisons
int binarySearch(int arr[], int n, int x, int *comparisons) {
    int low = 0, high = n - 1;
    *comparisons = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        (*comparisons)++;

        if (arr[mid] == x) {
            return mid;
        }
        
        (*comparisons)++;
        if (arr[mid] < x) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1; // Element not found
}

// Function to perform Ternary Search and count comparisons
int ternarySearch(int arr[], int n, int x, int *comparisons) {
    int low = 0, high = n - 1;
    *comparisons = 0;

    while (low <= high) {
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;

        (*comparisons)++;
        if (arr[mid1] == x) {
            return mid1;
        }

        (*comparisons)++;
        if (arr[mid2] == x) {
            return mid2;
        }

        (*comparisons)++;
        if (x < arr[mid1]) {
            high = mid1 - 1;
        } 
        else {
            (*comparisons)++;
            if (x > arr[mid2]) {
                low = mid2 + 1;
            } 
            else {
                low = mid1 + 1;
                high = mid2 - 1;
            }
        }
    }
    return -1; // Element not found
}

int main() {
    // Pre-defined sorted array and target element
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 23; // Element to search

    printf("---  BINARY VS TERNARY SEARCH ---\n");
    printf("Array size (n): %d\n", n);
    
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("Element to search (x): %d\n\n", x);

    int bin_comp = 0, ter_comp = 0;

    // Execute Binary Search
    int bin_result = binarySearch(arr, n, x, &bin_comp);
    
    // Execute Ternary Search
    int ter_result = ternarySearch(arr, n, x, &ter_comp);

    // Display Results
    printf("--- SEARCH RESULTS ---");
    if (bin_result != -1)
        printf("\nBinary Search: Element found at index %d", bin_result);
    else
        printf("\nBinary Search: Element not found");
    printf("\nBinary Search Comparisons: %d", bin_comp);

    if (ter_result != -1)
        printf("\n\nTernary Search: Element found at index %d", ter_result);
    else
        printf("\n\nTernary Search: Element not found");
    printf("\nTernary Search Comparisons: %d\n", ter_comp);

    // Validation & Justification
    printf("\n--- VALIDATION & JUSTIFICATION ---");
    printf("\nBinary Search made %d comparisons while Ternary Search made %d comparisons.", bin_comp, ter_comp);
    printf("\nConclusion: Binary search is better because ternary search ");
    printf("\nperforms more key comparisons per level (checking two midpoints instead of one), ");
    printf("\nresulting in a higher total number of key comparisons[cite: 1].\n");

    return 0;
}/* SAMPLE OUTPUT

Array size (n): 10
Sorted array: 2 5 8 12 16 23 38 56 72 91 
Element to search (x): 23

Binary Search: Element found at index 5
Binary Search Comparisons: 5

Ternary Search: Element found at index 5
Ternary Search Comparisons: 6

--- VALIDATION & JUSTIFICATION ---
Binary Search made 5 comparisons while Ternary Search made 6 comparisons.
Conclusion: Binary search is better because ternary search 
performs more key comparisons per level (checking two midpoints instead of one), 
resulting in a higher total number of key comparisons*/