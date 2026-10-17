/*--------PSEUDOCODE---------
Initialize DSU (p, sz, sm) and max-heap `h` for components of size <= K.

For each vertex i (0 to V-1):
    Read sm[i], set p[i] = i, sz[i] = 1
    If K >= 1, push (sm[i], i) to heap

For each edge (u, v, w):
    a = find(u), b = find(v)
    If a != b:
        Merge b into a (union by size: sz[a] += sz[b], sm[a] += sm[b])
        If sz[a] <= K, push (sm[a], a) to heap
    
    // Clean up outdated or invalid heap roots
    While heap is not empty and top node is no longer valid:
        pop heap
        
    Print (heap is not empty ? top.s : 0)
*/
#include <stdio.h>

#define N 100005

typedef long long ll;
typedef struct { 
    ll s; 
    int r; 
} H;

H h[2 * N]; 
int hn;
int p[N], sz[N]; 
ll sm[N]; 
int K;

int find(int x) {
    while (p[x] != x) {
        p[x] = p[p[x]];
        x = p[x];
    }
    return x;
}

void push(H x) {
    int i = hn++;
    while (i && h[(i - 1) / 2].s < x.s) {
        h[i] = h[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    h[i] = x;
}

void pop() {
    H x = h[--hn];
    int i = 0, c;
    while ((c = 2 * i + 1) < hn) {
        if (c + 1 < hn && h[c + 1].s > h[c].s) c++;
        if (h[c].s <= x.s) break;
        h[i] = h[c];
        i = c;
    }
    h[i] = x;
}

int main() {
    int V, E, u, v, w;
    
    printf("Enter number of vertices (V), edges (E), and K: ");
    scanf("%d %d %d", &V, &E, &K);
    
    printf("Enter the %d vertex values:\n", V);
    for (int i = 0; i < V; i++) {
        scanf("%lld", &sm[i]);
        p[i] = i;
        sz[i] = 1;
        if (K >= 1) push((H){sm[i], i});
    }
    
    printf("Enter the %d edges (u v w):\n", E);
    while (E--) {
        scanf("%d %d %d", &u, &v, &w);
        int a = find(u), b = find(v);
        if (a != b) {
            if (sz[a] < sz[b]) { int t = a; a = b; b = t; }
            p[b] = a;
            sz[a] += sz[b];
            sm[a] += sm[b];
            if (sz[a] <= K) push((H){sm[a], a});
        }
        while (hn && !(find(h[0].r) == h[0].r && sz[h[0].r] <= K && sm[h[0].r] == h[0].s)) pop();
        printf("Result: %lld\n", hn ? h[0].s : 0);
    }
    
    return 0;
}