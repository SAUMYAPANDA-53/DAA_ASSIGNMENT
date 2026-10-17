/*----------PSEUDOCODE---------
Function find(x):
    while p[x] != x:
        p[x] = p[p[x]]   // Path compression
        x = p[x]
    return x

Main:
    Read n, m
    For i from 0 to n-1:
        Read A[i]
        p[i] = i

    For j from 1 to m:
        Read u, v
        p[find(u)] = find(v)   // Union step

    For i from 0 to n-1:
        r = find(i)
        val[i] = (root: r, value: A[i])
        idx[i] = (root: r, index: i)

    Sort val array based on root (r), then by value (x)
    Sort idx array based on root (r), then by index (x)

    For i from 0 to n-1:
        res[idx[i].index] = val[i].value

    Print elements of res array
*/

#include <stdio.h>
#include <stdlib.h>

#define N 100005

typedef struct {
    int r;
    int x;
} T;

int p[N], A[N], res[N];
T val[N], idx[N];

int find(int x) {
    while (p[x] != x) {
        p[x] = p[p[x]];
        x = p[x];
    }
    return x;
}

int cmp(const void *a, const void *b) {
    const T *x = (const T *)a;
    const T *y = (const T *)b;
    if (x->r != y->r)
        return x->r - y->r;
    return x->x - y->x;
}

int main() {
    int n, m, u, v;

    printf("Enter number of elements (n) and number of edges (m): ");
    if (scanf("%d %d", &n, &m) != 2) return 1;

    printf("Enter the %d elements of array A:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
        p[i] = i;
    }

    printf("Enter the %d edges (u v) [0-indexed positions]:\n", m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        p[find(u)] = find(v);
    }

    for (int i = 0; i < n; i++) {
        int r = find(i);
        val[i].r = r;
        val[i].x = A[i];
        idx[i].r = r;
        idx[i].x = i;
    }

    qsort(val, n, sizeof(T), cmp);
    qsort(idx, n, sizeof(T), cmp);

    for (int i = 0; i < n; i++) {
        res[idx[i].x] = val[i].x;
    }

    printf("\nResulting array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", res[i]);
    }
    printf("\n");

    return 0;
}