

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ---------- Standard 2-way Merge Sort ---------- */

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

/* ---------- Modified 3-way Merge Sort ---------- */

void merge3(int arr[], int l, int m1, int m2, int r) {
    int n1 = m1 - l + 1;
    int n2 = m2 - m1;
    int n3 = r - m2;

    int *A = (int *)malloc(n1 * sizeof(int));
    int *B = (int *)malloc(n2 * sizeof(int));
    int *C = (int *)malloc(n3 * sizeof(int));

    for (int i = 0; i < n1; i++) A[i] = arr[l + i];
    for (int i = 0; i < n2; i++) B[i] = arr[m1 + 1 + i];
    for (int i = 0; i < n3; i++) C[i] = arr[m2 + 1 + i];

    int i = 0, j = 0, k = 0, idx = l;

    while (i < n1 && j < n2 && k < n3) {
        int minVal;
        if (A[i] <= B[j] && A[i] <= C[k])      { minVal = A[i++]; }
        else if (B[j] <= A[i] && B[j] <= C[k]) { minVal = B[j++]; }
        else                                    { minVal = C[k++]; }
        arr[idx++] = minVal;
    }
    while (i < n1 && j < n2) arr[idx++] = (A[i] <= B[j]) ? A[i++] : B[j++];
    while (j < n2 && k < n3) arr[idx++] = (B[j] <= C[k]) ? B[j++] : C[k++];
    while (i < n1 && k < n3) arr[idx++] = (A[i] <= C[k]) ? A[i++] : C[k++];
    while (i < n1) arr[idx++] = A[i++];
    while (j < n2) arr[idx++] = B[j++];
    while (k < n3) arr[idx++] = C[k++];

    free(A); free(B); free(C);
}

void merge_sort_modified(int arr[], int l, int r) {
    int len = r - l + 1;
    if (len < 2) return;
    if (len == 2) {
        int m = l + (r - l) / 2;
        merge_sort_modified(arr, l, m);
        merge_sort_modified(arr, m + 1, r);
        merge(arr, l, m, r);
        return;
    }
    int third = len / 3;
    int m1 = l + third - 1;
    int m2 = m1 + third;

    merge_sort_modified(arr, l, m1);
    merge_sort_modified(arr, m1 + 1, m2);
    merge_sort_modified(arr, m2 + 1, r);
    merge3(arr, l, m1, m2, r);
}

/* ---------- Helpers ---------- */

int *generate_array(int n) {
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arr[i] = rand() % 1000000;
    return arr;
}

int *copy_array(int *src, int n) {
    int *dst = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) dst[i] = src[i];
    return dst;
}

int is_sorted(int *arr, int n) {
    for (int i = 1; i < n; i++)
        if (arr[i - 1] > arr[i]) return 0;
    return 1;
}

/* ---------- Main: timing experiment ---------- */

int main(void) {
    srand(42);

    int sizes[] = {1000, 2000, 4000, 8000, 16000, 32000,
                   64000, 128000, 256000, 512000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    FILE *fp = fopen("results_q2.csv", "w");
    if (!fp) { perror("fopen"); return 1; }
    fprintf(fp, "n,merge_sort_time_sec,modified_merge_sort_time_sec\n");

    printf("%10s %20s %25s\n", "n", "MergeSort(s)", "ModifiedMergeSort(s)");

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        int *base = generate_array(n);

        int *a1 = copy_array(base, n);
        clock_t start = clock();
        merge_sort(a1, 0, n - 1);
        clock_t end = clock();
        double t1 = (double)(end - start) / CLOCKS_PER_SEC;
        if (!is_sorted(a1, n)) fprintf(stderr, "ERROR: merge_sort failed for n=%d\n", n);

        int *a2 = copy_array(base, n);
        start = clock();
        merge_sort_modified(a2, 0, n - 1);
        end = clock();
        double t2 = (double)(end - start) / CLOCKS_PER_SEC;
        if (!is_sorted(a2, n)) fprintf(stderr, "ERROR: merge_sort_modified failed for n=%d\n", n);

        printf("%10d %20.6f %25.6f\n", n, t1, t2);
        fprintf(fp, "%d,%.6f,%.6f\n", n, t1, t2);

        free(base); free(a1); free(a2);
    }

    fclose(fp);
    
    return 0;
}

/* Sample output :
        n            Merge_Sort              Modified_MergeSort
      1000             0.001000                  0.000000
      2000             0.001000                  0.001000
      4000             0.002000                  0.002000
      8000             0.004000                  0.003000
     16000             0.010000                  0.012000
     32000             0.029000                  0.028000
     64000             0.049000                  0.026000
    128000             0.068000                  0.071000
    256000             0.130000                  0.151000
    512000             0.460000                  0.456000
*/