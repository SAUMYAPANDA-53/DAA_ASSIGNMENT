#include <stdio.h>
#include <stdlib.h>

void minHeapify(int heap[], int size, int i) {
    int min = i, l = 2*i + 1, r = 2*i + 2;
    if (l < size && heap[l] < heap[min]) min = l;
    if (r < size && heap[r] < heap[min]) min = r;
    if (min != i) {
        int t = heap[i]; heap[i] = heap[min]; heap[min] = t;
        minHeapify(heap, size, min);
    }
}

void push(int heap[], int *size, int val) {
    int i = (*size)++;
    heap[i] = val;
    while (i && heap[(i-1)/2] > heap[i]) {
        int t = heap[i]; heap[i] = heap[(i-1)/2]; heap[(i-1)/2] = t;
        i = (i-1)/2;
    }
}

int pop(int heap[], int *size) {
    int top = heap[0];
    heap[0] = heap[--(*size)];
    minHeapify(heap, *size, 0);
    return top;
}

int connectSticks(int sticks[], int n) {
    int heap[100], hSize = 0, totalCost = 0;

    // Build initial min-heap
    for (int i = 0; i < n; i++) push(heap, &hSize, sticks[i]);

    // Greedily connect the two smallest sticks
    while (hSize > 1) {
        int first = pop(heap, &hSize);
        int second = pop(heap, &hSize);
        int cost = first + second;
        totalCost += cost;
        push(heap, &hSize, cost);
    }

    return totalCost;
}

int main() {
    int sticks[] = {2, 4, 3};
    int n = sizeof(sticks) / sizeof(sticks[0]);
    
    printf("Minimum Cost: %d\n", connectSticks(sticks, n));
    return 0;
}