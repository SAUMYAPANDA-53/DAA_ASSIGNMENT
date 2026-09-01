#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// (i) Finding the maximum element
int findMaximum(int arr[], int n) {
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

// (ii) Finding the first and second largest elements
void findFirstAndSecondLargest(int arr[], int n, int *first, int *second) {
    *first = *second = -2147483648; // INT_MIN equivalent
    for (int i = 0; i < n; i++) {
        if (arr[i] > *first) {
            *second = *first;
            *first = arr[i];
        } else if (arr[i] > *second && arr[i] != *first) {
            *second = arr[i];
        }
    }
}

// (iii) Finding the mean
double findMean(int arr[], int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return (double)sum / n;
}

// Helper comparison function for sorting/median
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// (iv) Finding the median
double findMedian(int arr[], int n) {
    int *temp = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) temp[i] = arr[i];
    qsort(temp, n, sizeof(int), compare);
    
    double median;
    if (n % 2 == 0) {
        median = (temp[n / 2 - 1] + temp[n / 2]) / 2.0;
    } else {
        median = temp[n / 2];
    }
    free(temp);
    return median;
}

// (v) Finding the standard deviation
double findStandardDeviation(int arr[], int n, double mean) {
    double sumSqDiff = 0;
    for (int i = 0; i < n; i++) {
        sumSqDiff += pow(arr[i] - mean, 2);
    }
    return sqrt(sumSqDiff / n);
}

// (vi) Finding the mode
int findMode(int arr[], int n) {
    int *temp = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) temp[i] = arr[i];
    qsort(temp, n, sizeof(int), compare);

    int maxStreak = 0, mode = temp[0], currentStreak = 1;
    for (int i = 1; i < n; i++) {
        if (temp[i] == temp[i - 1]) {
            currentStreak++;
        } else {
            currentStreak = 1;
        }
        if (currentStreak > maxStreak) {
            maxStreak = currentStreak;
            mode = temp[i];
        }
    }
    free(temp);
    return mode;
}

// (vii) Removing all duplicates (returns new size)
int removeDuplicates(int arr[], int n) {
    int *temp = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) temp[i] = arr[i];
    qsort(temp, n, sizeof(int), compare);

    int j = 0;
    if (n > 0) {
        arr[j++] = temp[0];
        for (int i = 1; i < n; i++) {
            if (temp[i] != temp[i - 1]) {
                arr[j++] = temp[i];
            }
        }
    }
    free(temp);
    return j;
}

// (viii) Reversing the elements of the array
void reverseArray(int arr[], int n) {
    for (int i = 0; i < n / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[n - 1 - i];
        arr[n - 1 - i] = temp;
    }
}

// (ix) Partitioning: elements less than pivot appear AFTER elements greater than or equal to pivot
void customPartition(int arr[], int n, int pivot) {
    int *temp = (int *)malloc(n * sizeof(int));
    int left = 0, right = n - 1;

    for (int i = 0; i < n; i++) {
        if (arr[i] < pivot) {
            temp[right--] = arr[i];
        } else {
            temp[left++] = arr[i];
        }
    }
    for (int i = 0; i < n; i++) {
        arr[i] = temp[i];
    }
    free(temp);
}

int main() {
    int n, pivot;

    printf("Enter the number of elements in the array: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid array size.\n");
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d integer elements (space or comma separated):\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        // Safely consume any separating commas or whitespace
        int ch;
        while ((ch = getchar()) == ',' || ch == ' ' || ch == '\t' || ch == '\r');
        if (ch != EOF) {
            ungetc(ch, stdin);
        }
    }

    printf("Enter the pivot value for partitioning: ");
    scanf("%d", &pivot);

    printf("\nOriginal Array:\n");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n\n");

    // (i) Maximum
    printf("(i) Maximum Element: %d\n", findMaximum(arr, n));

    // (ii) First and Second Largest
    int first, second;
    findFirstAndSecondLargest(arr, n, &first, &second);
    printf("(ii) First Largest: %d, Second Largest: %d\n", first, second);

    // (iii) Mean
    double mean = findMean(arr, n);
    printf("(iii) Mean: %.2f\n", mean);

    // (iv) Median
    printf("(iv) Median: %.2f\n", findMedian(arr, n));

    // (v) Standard Deviation
    printf("(v) Standard Deviation: %.2f\n", findStandardDeviation(arr, n, mean));

    // (vi) Mode
    printf("(vi) Mode: %d\n", findMode(arr, n));

    // (vii) Removing duplicates
    int *arrCopy = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arrCopy[i] = arr[i];
    int newSize = removeDuplicates(arrCopy, n);
    printf("(vii) Array after removing duplicates: ");
    for (int i = 0; i < newSize; i++) printf("%d ", arrCopy[i]);
    printf("\n");

    // (viii) Reversing
    for (int i = 0; i < n; i++) arrCopy[i] = arr[i];
    reverseArray(arrCopy, n);
    printf("(viii) Reversed Array: ");
    for (int i = 0; i < n; i++) printf("%d ", arrCopy[i]);
    printf("\n");

    // (ix) Custom Partition
    for (int i = 0; i < n; i++) arrCopy[i] = arr[i];
    customPartition(arrCopy, n, pivot);
    printf("(ix) Partitioned Array (Elements < %d appear AFTER >= %d):\n", pivot, pivot);
    for (int i = 0; i < n; i++) printf("%d ", arrCopy[i]);
    printf("\n");

    free(arr);
    free(arrCopy);

    return 0;
}
/*       ------- SAMPLE  OUTPUT -------
Enter the number of elements in the array: 5
Enter 5 integer elements (space or comma separated):
2, 1, 4, 1, 2
Enter the pivot value for partitioning: 3

Original Array:
2 1 4 1 2 

(i) Maximum Element: 4
(ii) First Largest: 4, Second Largest: 2
(iii) Mean: 2.00
(iv) Median: 2.00
(v) Standard Deviation: 1.10
(vi) Mode: 1
(vii) Array after removing duplicates: 1 2 4 
(viii) Reversed Array: 2 1 4 1 2 
(ix) Partitioned Array (Elements < 3 appear AFTER >= 3):
4 2 1 1 2 
*/