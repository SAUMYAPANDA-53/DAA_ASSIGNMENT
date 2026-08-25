/* -------ALGORITHM--------
PROCEDURE Heapify(arr, n, i):
    largest = i
    left = 2 * i + 1
    right = 2 * i + 2

    IF left < n AND arr[left] > arr[largest] THEN
        largest = left
    IF right < n AND arr[right] > arr[largest] THEN
        largest = right

    IF largest != i THEN
        SWAP arr[i] WITH arr[largest]
        Heapify(arr, n, largest)

PROCEDURE HeapSort(arr, n):
    // Build max heap
    FOR i = (n / 2 - 1) DOWN TO 0 DO
        Heapify(arr, n, i)

    // Extract elements from heap one by one
    FOR i = n - 1 DOWN TO 1 DO
        SWAP arr[0] WITH arr[i]
        Heapify(arr, i, 0)
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

void generateFile(const char* filename, int n) {
    FILE* file = fopen(filename, "w");
    if (!file) return;
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\n", rand() % 100000);
    }
    fclose(file);
}

int main() {
    int n = 10000;
    const char* inputFile = "input.txt";
    const char* outputFile = "output.txt";

    srand((unsigned int)time(NULL));
    generateFile(inputFile, n);

    FILE* file = fopen(inputFile, "r");
    if (!file) return 1;

    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);

    clock_t start = clock();
    heapSort(arr, n);
    clock_t end = clock();

    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution time for N=%d: %f seconds\n", n, cpu_time_used);

    file = fopen(outputFile, "w");
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\n", arr[i]);
    }
    fclose(file);

    free(arr);
    return 0;
}