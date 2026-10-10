/*----------PSEUDOCODE-----------
Algorithm MinimumDeviation(nums, n):
    Initialize Max-Heap h with capacity n * 2
    min_val = INFINITY
    min_dev = INFINITY

    For i = 0 to n - 1:
        v = (nums[i] % 2 != 0) ? nums[i] * 2 : nums[i]
        Push v to h
        min_val = min(min_val, v)

    While h is not empty:
        max_val = Pop(h)
        min_dev = min(min_dev, max_val - min_val)

        If max_val is odd:
            Break
        
        nv = max_val / 2
        Push nv to h
        min_val = min(min_val, nv)

    Return min_dev
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct { 
    int *a; 
    int s,cap; 
} Heap;

Heap* init(int cap) {
    Heap *h = (Heap*)malloc(sizeof(Heap));
    h->cap = cap; 
    h->s = 0; 
    h->a = (int*)malloc(cap * sizeof(int));
    return h;
}

void swap(int *x, int *y) { 
    int t = *x; 
    *x = *y; 
    *y = t; 
}

void up(Heap *h, int i) {
    while (i > 0 && h->a[i] > h->a[(i - 1) / 2]) {
        swap(&h->a[i], &h->a[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void down(Heap *h, int i) {
    int l, r, largest;
    while ((l = 2 * i + 1) < h->s) {
        largest = i;
        r = l + 1;
        if (h->a[l] > h->a[largest]) largest = l;
        if (r < h->s && h->a[r] > h->a[largest]) largest = r;
        if (largest == i) break;
        swap(&h->a[i], &h->a[largest]);
        i = largest;
    }
}

void push(Heap *h, int val) {
    if (h->s == h->cap) {
        h->cap *= 2;
        h->a = (int*)realloc(h->a, h->cap * sizeof(int));
    }
    h->a[h->s] = val;
    up(h, h->s++);
}

int pop(Heap *h) {
    int root = h->a[0];
    h->a[0] = h->a[--h->s];
    down(h, 0);
    return root;
}

int minimumDeviation(int* nums, int n) {
    Heap *h = init(n * 2);
    int min_val = INT_MAX, min_dev = INT_MAX;
    
    for (int i = 0; i < n; i++) {
        int v = (nums[i] % 2 != 0) ? nums[i] * 2 : nums[i];
        push(h, v);
        if (v < min_val) min_val = v;
    }
    
    while (h->s > 0) {
        int max_val = pop(h);
        if (max_val - min_val < min_dev) {
            min_dev = max_val - min_val;
        }
        if (max_val % 2 != 0) break;
        
        int nv = max_val / 2;
        push(h, nv);
        if (nv < min_val) min_val = nv;
    }
    
    int res = min_dev;
    free(h->a); 
    free(h);
    return res;
}

int main() {
    int n;
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input size.\n");
        return 1;
    }
    
    int *nums = (int*)malloc(n * sizeof(int));
    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }
    
    int result = minimumDeviation(nums, n);
    printf("Minimum Deviation: %d\n", result);
    
    free(nums);
    return 0;
}/*-------SAMPLE OUTPUT--------
Enter number of elements: 4
Enter 4 integers: 4 3 5 2 9
Minimum Deviation: 3
*/