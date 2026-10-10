#include <stdio.h>
#include <stdlib.h>

typedef struct { int d, f; } Station;

int cmp(const void* a, const void* b) { return ((Station*)a)->d - ((Station*)b)->d; }

void maxHeapify(int heap[], int size, int i) {
    int max = i, l = 2*i + 1, r = 2*i + 2;
    if (l < size && heap[l] > heap[max]) max = l;
    if (r < size && heap[r] > heap[max]) max = r;
    if (max != i) {
        int t = heap[i]; heap[i] = heap[max]; heap[max] = t;
        maxHeapify(heap, size, max);
    }
}

void push(int heap[], int *size, int val) {
    int i = (*size)++;
    heap[i] = val;
    while (i && heap[(i-1)/2] < heap[i]) {
        int t = heap[i]; heap[i] = heap[(i-1)/2]; heap[(i-1)/2] = t;
        i = (i-1)/2;
    }
}

int pop(int heap[], int *size) {
    int top = heap[0];
    heap[0] = heap[--(*size)];
    maxHeapify(heap, *size, 0);
    return top;
}

int minRefuelStops(int D, int fuel, Station st[], int n) {
    qsort(st, n, sizeof(Station), cmp);
    int heap[100], hSize = 0, stops = 0, idx = 0;

    while (fuel < D) {
        while (idx < n && st[idx].d <= fuel)
            push(heap, &hSize, st[idx++].f);
        if (hSize == 0) return -1;
        fuel += pop(heap, &hSize);
        stops++;
    }
    return stops;
}

int main() {
    Station st[] = {{10, 60}, {20, 30}, {30, 30}, {60, 40}};
    int stops = minRefuelStops(100, 10, st, 4);
    printf("Min Stops: %d\n", stops);
    return 0;
}