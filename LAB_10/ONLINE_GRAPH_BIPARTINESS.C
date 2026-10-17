/*----------PSEUDOCODE------------
Algorithm: Online Bipartiteness Testing

Initialize:
  For each vertex i from 0 to V - 1:
    parent[i] = i
    rank[i] = 0
    parity[i] = 0

Function Find(u):
  If parent[u] == u:
    return (u, 0)
  (root, p) = Find(parent[u])
  parity[u] = parity[u] XOR p
  parent[u] = root
  return (root, parity[u])

Function AddEdge(u, v):
  (root_u, p_u) = Find(u)
  (root_v, p_v) = Find(v)

  If root_u == root_v:
    If p_u == p_v:
      Report "Violation: Adding edge introduces an odd-length cycle."
      Return False
    Else:
      Report "Edge added successfully. Bipartiteness maintained."
      Return True
  Else:
    If rank[root_u] < rank[root_v]:
      Swap(root_u, root_v)
      Swap(p_u, p_v)
    
    parent[root_v] = root_u
    parity[root_v] = p_u XOR p_v XOR 1
    
    If rank[root_u] == rank[root_v]:
      rank[root_u] = rank[root_u] + 1
      
    Report "Edge added successfully. Bipartiteness maintained."
    Return True
*/
#include <stdio.h>

int p[1005], r[1005], par[1005];

int find(int u, int *x) {
    if (p[u] == u) { *x = 0; return u; }
    int px; int root = find(p[u], &px);
    par[u] ^= px;
    return p[u] = root;
}

int add(int u, int v) {
    int pu, pv, ru = find(u, &pu), rv = find(v, &pv);
    if (ru == rv) return pu != pv;
    if (r[ru] < r[rv]) { int t = ru; ru = rv; rv = t; t = pu; pu = pv; pv = t; }
    p[rv] = ru;
    par[rv] = pu ^ pv ^ 1;
    if (r[ru] == r[rv]) r[ru]++;
    return 1;
}

int main() {
    int V, E, u, v;
    printf("Enter V and E: ");
    if (scanf("%d %d", &V, &E) != 2) return 0;
    for (int i = 0; i < V; i++) p[i] = i;
    
    printf("Enter %d edges (u v):\n", E);
    while (E--) {
        scanf("%d %d", &u, &v);
        if (add(u, v)) printf("Edge (%d, %d) added. Bipartite maintained.\n", u, v);
        else printf("Edge (%d, %d) violates bipartiteness. Skipped.\n", u, v);
    }
    return 0;
}
/*----------SAMPLE OUTPUT----------

*/