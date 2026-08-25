#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int left, int right, int pivot_index) {
    int pivot_value = arr[pivot_index];
    swap(&arr[pivot_index], &arr[right]);
    
    int store_index = left;
    for (int i = left; i < right; i++) {
        if (arr[i] < pivot_value) {
            swap(&arr[i], &arr[store_index]);
            store_index++;
        }
    }
    
    swap(&arr[right], &arr[store_index]);
    return store_index;
}

int quickselect(int arr[], int left, int right, int k) {
    if (left == right) return arr[left];

    int pivot_index = left + rand() % (right - left + 1);
    pivot_index = partition(arr, left, right, pivot_index);

    if (k == pivot_index) return arr[k];
    else if (k < pivot_index) return quickselect(arr, left, pivot_index - 1, k);
    else return quickselect(arr, pivot_index + 1, right, k);
}

double find_median(int arr[], int n) {
    srand(time(NULL));
    if (n % 2 == 1) {
        return (double)quickselect(arr, 0, n - 1, n / 2);
    } else {
        int mid1 = quickselect(arr, 0, n - 1, n / 2 - 1);
        int mid2 = quickselect(arr, 0, n - 1, n / 2);
        return (double)(mid1 + mid2) / 2.0;
    }
}

int main() {
    int n;

    printf("Enter the number of elements (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid array size!\n");
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter %d integers (comma or space separated): ", n);
    for (int i = 0; i < n; i++) {
        // "%d%*[, ]" parses the integer and discards trailing commas or spaces
        if (scanf("%d%*[, ]", &arr[i]) != 1) {
            printf("Invalid input format!\n");
            free(arr);
            return 1;
        }
    }

    double median = find_median(arr, n);
    printf("\nCalculated Median: %.2f\n", median);

    free(arr);
    return 0;
}/* SAMPLE OUTPUT 
Enter the number of elements (N): 5
Enter 5 integers (comma or space separated): 2,12,4,5,1

Calculated Median: 4.00
*/