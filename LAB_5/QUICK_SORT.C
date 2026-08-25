#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to swap two integers
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function for Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Quick Sort function
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int N = 100; // Number of elements
    const char *input_file = "unsorted_data.txt";
    const char *output_file = "sorted_data.txt";

    // Step 1: Generate N random numbers and save to file
    srand(time(0));
    FILE *fp = fopen(input_file, "w");
    if (fp == NULL) {
        printf("Error creating input file!\n");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        fprintf(fp, "%d\n", rand() % 1000 + 1); // Random numbers between 1 and 1000
    }
    fclose(fp);

    // Step 2: Read elements from the file into an array
    int *arr = (int *)malloc(N * sizeof(int));
    fp = fopen(input_file, "r");
    if (fp == NULL) {
        printf("Error opening input file!\n");
        free(arr);
        return 1;
    }

    for (int i = 0; i < N; i++) {
        fscanf(fp, "%d", &arr[i]);
    }
    fclose(fp);

    // Step 3: Perform Quick Sort
    quickSort(arr, 0, N - 1);

    // Step 4: Save sorted elements to output file
    fp = fopen(output_file, "w");
    if (fp == NULL) {
        printf("Error creating output file!\n");
        free(arr);
        return 1;
    }

    for (int i = 0; i < N; i++) {
        fprintf(fp, "%d\n", arr[i]);
    }
    fclose(fp);

    printf("Successfully generated %d random numbers in '%s' and saved sorted data to '%s'.\n", N, input_file, output_file);

    free(arr);
    return 0;
}