/*-----------PSEUDOCODE---------
Initialize:
  Read V, E. Read vertex weights into sm[], set DSU parents p[i] = i, and graph head[] = -1.
  Read E undirected edges and build adjacency list.
  Read deletion order permutation P[].

Process (Reverse Order):
  best = 0, ans[V] = 0
  For i = V down to 2:
    x = P[i], act[x] = 1 (activate vertex)
    For each neighbor v of x:
      If v is active:
        Merge DSU components of x and v, summing their weights.
    best = max(best, component_sum of x)
    ans[i-1] = best

Output:
  Print ans[1] through ans[V].
*/

#include <stdio.h>
#define N 100005
typedef long long ll;
int head[N], nx[2*N], to[2*N], ec, p[N], P[N], act[N];
ll sm[N], ans[N];

int find(int x) { 
    while(p[x] != x) { p[x] = p[p[x]]; x = p[x]; } 
    return x; 
}

void add(int u, int v) { 
    to[ec] = v; 
    nx[ec] = head[u]; 
    head[u] = ec++; 
}

int main() {
    int V, E, u, v; 
    
    printf("=== Interactive Component Weight Tracker ===\n");
    printf("GUIDE:\n");
    printf("- First, you enter total vertices (V) and total edges (E).\n");
    printf("  For example, type '4 3' where 4 = total vertices, 3 = total edges.\n\n");
    
    printf("Enter number of vertices (V) and edges (E) [e.g., 4 3]: ");
    fflush(stdout);
    if (scanf("%d %d", &V, &E) != 2 || V >= N) {
        printf("Error: Invalid input or V exceeds max limit (%d).\n", N);
        return 0;
    }
    
    printf("\n--- Step 2: Vertex Weights ----- \n");
    printf("You entered V = %d vertices. Now enter the weight for each vertex.\n", V);
    printf("Example: If V=4, you can enter: 10 20 30 40\n");
    printf("Enter the weights for each of the %d vertices:\n", V);
    for(int i = 1; i <= V; i++) {
        printf("  -> Enter weight for vertex %d: ", i);
        fflush(stdout);
        scanf("%lld", &sm[i]); 
        p[i] = i; 
        head[i] = -1; 
        act[i] = 0;
    }
    
    printf("\n--- Step 3: Graph Edges ---\n");
    printf("You entered E = %d edges. Now enter each connection (u v).\n", E);
    printf("Example: '1 2' means vertex 1 is connected to vertex 2.\n");
    for(int i = 0; i < E; i++) { 
        printf("  -> Enter edge %d (u v): ", i + 1);
        fflush(stdout);
        scanf("%d %d", &u, &v); 
        add(u, v); 
        add(v, u); 
    }
    
    printf("\n--- Step 4: Deletion Order Permutation ---\n");
    printf("Enter the order in which the %d vertices are processed/deleted:\n", V);
    for(int i = 1; i <= V; i++) { 
        printf("  -> Enter vertex at deletion step %d: ", i);
        fflush(stdout);
        scanf("%d", &P[i]); 
    }
    
    ll best = 0; 
    ans[V] = 0;
    
    for(int i = V; i >= 2; i--) {                        
        int x = P[i]; 
        act[x] = 1;
        
        for(int e = head[x]; e != -1; e = nx[e]) {
            if(act[to[e]]) {
                int a = find(x), b = find(to[e]);
                if(a != b) { 
                    p[b] = a; 
                    sm[a] += sm[b]; 
                }
            }
        }
        
        ll s = sm[find(x)]; 
        if(s > best) best = s;
        ans[i-1] = best;
    }
    
    printf("\n--- Results (Max Component Sum After Each Deletion Step) ---\n");
    for(int i = 1; i <= V; i++) { 
        printf("%lld\n", ans[i]); 
    }
    
    return 0;
}