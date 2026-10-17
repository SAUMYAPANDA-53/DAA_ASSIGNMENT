/*---------PSEUDOCODE-----------
Algorithm: Dynamic Connected Components in a Grid (Number of Islands II)

Initialize:
  total_cells = R * C
  For each cell i from 0 to total_cells - 1:
    parent[i] = -1  // -1 indicates water
    rank[i] = 0
  island_count = 0

Function Find(i):
  If parent[i] == i:
    return i
  parent[i] = Find(parent[i])
  return parent[i]

Function Union(i, j):
  root_i = Find(i)
  root_j = Find(j)
  If root_i != root_j:
    If rank[root_i] < rank[root_j]:
      Swap(root_i, root_j)
    parent[root_j] = root_i
    If rank[root_i] == rank[root_j]:
      rank[root_i] = rank[root_i] + 1
    return True
  return False

For each land addition at position (r, c):
  idx = r * C + c
  If parent[idx] != -1:
    Output island_count
    continue
  
  parent[idx] = idx
  island_count = island_count + 1
  
  For each 4-directionally adjacent neighbor (nr, nc) of (r, c):
    If 0 <= nr < R and 0 <= nc < C:
      n_idx = nr * C + nc
      If parent[n_idx] != -1:
        If Union(idx, n_idx):
          island_count = island_count - 1
          
  Output island_count
*/
#include <stdio.h>

int p[100005], r[100005];

int find(int i) {
    return p[i] == i ? i : (p[i] = find(p[i]));
}

int unite(int i, int j) {
    int ri = find(i), rj = find(j);
    if (ri == rj) return 0;
    if (r[ri] < r[rj]) { int t = ri; ri = rj; rj = t; }
    p[rj] = ri;
    if (r[ri] == r[rj]) r[ri]++;
    return 1;
}

int main() {
    int R, C, k, islands = 0;
    if (scanf("%d %d %d", &R, &C, &k) != 3) return 0;
    for (int i = 0; i < R * C; i++) p[i] = -1;
    
    int dr[] = {-1, 1, 0, 0}, dc[] = {0, 0, -1, 1};
    while (k--) {
        int r_idx, c_idx;
        scanf("%d %d", &r_idx, &c_idx);
        int idx = r_idx * C + c_idx;
        if (p[idx] != -1) {
            printf("Islands: %d\n", islands);
            continue;
        }
        p[idx] = idx;
        islands++;
        for (int i = 0; i < 4; i++) {
            int nr = r_idx + dr[i], nc = c_idx + dc[i];
            if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
                int n_idx = nr * C + nc;
                if (p[n_idx] != -1 && unite(idx, n_idx)) islands--;
            }
        }
        printf("Islands: %d\n", islands);
    }
    return 0;
} 