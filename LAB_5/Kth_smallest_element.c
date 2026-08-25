/* -------- ALGORITHM ------

Function QuickSelect(array, left, right, target_k):
    if left equals right:
        return array[left]

    pivot_index = RandomIndexBetween(left, right)
    pivot_index = Partition(array, left, right, pivot_index)

    if target_k equals pivot_index:
        return array[target_k]
    else if target_k < pivot_index:
        return QuickSelect(array, left, pivot_index - 1, target_k)
    else:
        return QuickSelect(array, pivot_index + 1, right, target_k)

Function Partition(array, left, right, pivot_index):
    pivot_value = array[pivot_index]
    Swap(array[pivot_index], array[right])
    
    store_index = left
    for i from left to right - 1:
        if array[i] < pivot_value:
            Swap(array[i], array[store_index])
            store_index = store_index + 1
            
    Swap(array[right], array[store_index])
    return store_index
*/

/*  ----------- CODE ------------ */

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

int quickselect(int arr[], int left, int right, int target_k) {
    if (left == right) {
        return arr[left];
    }

    int pivot_index = left + rand() % (right - left + 1);
    pivot_index = partition(arr, left, right, pivot_index);

    if (target_k == pivot_index) {
        return arr[target_k];
    } else if (target_k < pivot_index) {
        return quickselect(arr, left, pivot_index - 1, target_k);
    } else {
        return quickselect(arr, pivot_index + 1, right, target_k);
    }
}

int main() {
    int n, k;

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

    printf("Enter %d integers (space or comma separated): ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d%*[, ]", &arr[i]) != 1) {
            printf("Invalid array input!\n");
            free(arr);
            return 1;
        }
    }

    printf("Enter position K (1-indexed, 1 to %d): ", n);
    if (scanf("%d", &k) != 1 || k < 1 || k > n) {
        printf("Invalid value of K!\n");
        free(arr);
        return 1;
    }

    srand(time(NULL));
    
    // k - 1 converts 1-indexed K to 0-indexed array position
    int result = quickselect(arr, 0, n - 1, k - 1);

    printf("\nThe %d-th smallest element is: %d\n", k, result);

    free(arr);
    return 0;
}/*  --------SAMPLE OUTPUT---------
Enter the number of elements (N): 7
Enter 7 integers (space or comma separated): 2,1,4,5,12,7,9
Enter position K (1-indexed, 1 to 7): 3

The 3-th smallest element is: 4
*/