
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

/* ---------- Basic two-way merge of two sorted int arrays ---------- */

void merge_two(const int *a, int na, const int *b, int nb, int *out) {
    int i = 0, j = 0, k = 0;
    while (i < na && j < nb)
        out[k++] = (a[i] <= b[j]) ? a[i++] : b[j++];
    while (i < na) out[k++] = a[i++];
    while (j < nb) out[k++] = b[j++];
}

/* ---------- Helpers ---------- */

int cmp_int(const void *a, const void *b) {
    return (*(const int *)a) - (*(const int *)b);
}

int *generate_sorted_array(int n) {
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arr[i] = rand() % 1000000;
    qsort(arr, n, sizeof(int), cmp_int);
    return arr;
}

int is_sorted(const int *arr, int n) {
    for (int i = 1; i < n; i++)
        if (arr[i - 1] > arr[i]) return 0;
    return 1;
}

/* ---------- Method 1: sequential merging ---------- */

int *method1_sequential(int **arrays, int k, int n) {
    int cur_len = n;
    int *result = (int *)malloc((size_t)n * sizeof(int));
    memcpy(result, arrays[0], (size_t)n * sizeof(int));

    for (int i = 1; i < k; i++) {
        int new_len = cur_len + n;
        int *merged = (int *)malloc((size_t)new_len * sizeof(int));
        merge_two(result, cur_len, arrays[i], n, merged);
        free(result);
        result = merged;
        cur_len = new_len;
    }
    return result; /* caller frees */
}

/* ---------- Method 2: pairwise / tournament merging ---------- */

typedef struct {
    int *data;
    int len;
} Arr;

int *method2_pairwise(int **arrays, int k, int n) {
    Arr *cur = (Arr *)malloc((size_t)k * sizeof(Arr));
    for (int i = 0; i < k; i++) {
        cur[i].data = (int *)malloc((size_t)n * sizeof(int));
        memcpy(cur[i].data, arrays[i], (size_t)n * sizeof(int));
        cur[i].len = n;
    }

    int count = k;
    while (count > 1) {
        int new_count = (count + 1) / 2;
        Arr *next = (Arr *)malloc((size_t)new_count * sizeof(Arr));
        int idx = 0;
        for (int i = 0; i < count; i += 2) {
            if (i + 1 < count) {
                int len = cur[i].len + cur[i + 1].len;
                int *merged = (int *)malloc((size_t)len * sizeof(int));
                merge_two(cur[i].data, cur[i].len, cur[i + 1].data, cur[i + 1].len, merged);
                free(cur[i].data);
                free(cur[i + 1].data);
                next[idx].data = merged;
                next[idx].len = len;
            } else {
                /* odd one out: carry forward unmerged to next round */
                next[idx] = cur[i];
            }
            idx++;
        }
        free(cur);
        cur = next;
        count = new_count;
    }

    int *result = cur[0].data;
    free(cur);
    return result; /* caller frees */
}

/* ---------- Timing experiment ---------- */

int main(void) {
    srand(42);

    int n = 500;                                  /* elements per array (fixed) */
    int k_values[] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
    int num_k = sizeof(k_values) / sizeof(k_values[0]);

    FILE *fp = fopen("results_q3.csv", "w");
    if (!fp) { perror("fopen"); return 1; }
    fprintf(fp, "k,n,method1_time_sec,method2_time_sec\n");

    printf("%6s %8s %18s %18s\n", "k", "n", "Method1(s)", "Method2(s)");

    for (int t = 0; t < num_k; t++) {
        int k = k_values[t];

        int **arrays = (int **)malloc((size_t)k * sizeof(int *));
        for (int i = 0; i < k; i++) arrays[i] = generate_sorted_array(n);

        clock_t start = clock();
        int *r1 = method1_sequential(arrays, k, n);
        clock_t end = clock();
        double t1 = (double)(end - start) / CLOCKS_PER_SEC;
        if (!is_sorted(r1, k * n))
            fprintf(stderr, "ERROR: method1 result not sorted for k=%d\n", k);

        start = clock();
        int *r2 = method2_pairwise(arrays, k, n);
        end = clock();
        double t2 = (double)(end - start) / CLOCKS_PER_SEC;
        if (!is_sorted(r2, k * n))
            fprintf(stderr, "ERROR: method2 result not sorted for k=%d\n", k);

        /* cross-check: both methods must produce the identical multiset */
        int mismatch = 0;
        for (int i = 0; i < k * n; i++)
            if (r1[i] != r2[i]) { mismatch = 1; break; }
        if (mismatch)
            fprintf(stderr, "ERROR: method1 and method2 outputs differ for k=%d\n", k);

        printf("%6d %8d %18.6f %18.6f\n", k, n, t1, t2);
        fprintf(fp, "%d,%d,%.6f,%.6f\n", k, n, t1, t2);

        free(r1);
        free(r2);
        for (int i = 0; i < k; i++) free(arrays[i]);
        free(arrays);
    }

    fclose(fp);
    printf("\nResults written to results_q3.csv\n");
    printf("Method 1 (sequential merging) worst case: O(n k^2)\n");
    printf("Method 2 (pairwise merging)   worst case: O(n k log k)\n");
    return 0;
}
/* Sample output :
     k        n         Method1(s)         Method2(s)
     2      500           0.000000           0.000000
     4      500           0.000000           0.000000
     8      500           0.000000           0.001000
    16      500           0.000000           0.002000
    32      500           0.003000           0.002000
    64      500           0.007000           0.003000
   128      500           0.039000           0.012000
   256      500           0.126000           0.019000
   512      500           0.752000           0.061000
  1024      500           1.766000           0.063000

Results written to results_q3.csv
Method 1 (sequential merging) worst case: O(n k^2)
Method 2 (pairwise merging)   worst case: O(n k log k)
*/