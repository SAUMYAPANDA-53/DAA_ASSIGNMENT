#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to reverse a subsequence from index i to j and return its cost (length)
long long reverse_subsequence(int p[], int i, int j) {
    int left = i, right = j;
    while (left < right) {
        int temp = p[left];
        p[left] = p[right];
        p[right] = temp;
        left++;
        right--;
    }
    return (long long)(j - i + 1);
}

// Sorting algorithm using reversals to place each element in its correct position
long long sort_permutation(int p[], int n) {
    long long total_cost = 0;
    for (int i = 0; i < n; i++) {
        int pos = -1;
        for (int j = i; j < n; j++) {
            if (p[j] == i + 1) {
                pos = j;
                break;
            }
        }
        if (pos != i) {
            total_cost += reverse_subsequence(p, i, pos);
        }
    }
    return total_cost;
}

// Function to generate a random permutation of size n
void generate_permutation(int p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i] = i + 1;
    }
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = p[i];
        p[i] = p[j];
        p[j] = temp;
    }
}

int main() {
    srand(time(NULL));
    printf("n,cost\n");
    
    int max_n = 2000;
    int step = 100;
    int *p = (int *)malloc(max_n * sizeof(int));
    
    for (int n = 100; n <= max_n; n += step) {
        generate_permutation(p, n);
        long long cost = sort_permutation(p, n);
        printf("%d,%lld\n", n, cost);
    }
    
    free(p);
    return 0;
}