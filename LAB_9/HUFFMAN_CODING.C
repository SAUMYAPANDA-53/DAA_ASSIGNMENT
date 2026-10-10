#include <stdio.h>
#include <string.h>

typedef struct { int sym, freq, len; } Node;

int freq_arr[40];
int left_arr[40];
int right_arr[40];
int parent_arr[40];
Node a[20];
int n_sym;

void getLen(int u, int l) {
    if(left_arr[u] == -1 && right_arr[u] == -1) {
        for(int i = 0; i < n_sym; i++) {
            if(a[i].sym == u) a[i].len = l;
        }
        return;
    }
    if(left_arr[u] != -1) getLen(left_arr[u], l + 1);
    if(right_arr[u] != -1) getLen(right_arr[u], l + 1);
}

int main() {
    memset(left_arr, -1, sizeof(left_arr));
    memset(right_arr, -1, sizeof(right_arr));
    memset(parent_arr, 0, sizeof(parent_arr));
    memset(freq_arr, 0, sizeof(freq_arr));

    printf("Enter number of symbols: ");
    if (scanf("%d", &n_sym) != 1) return 0;
    
    for(int i = 0; i < n_sym; i++) {
        a[i].sym = i;
        printf("Frequency of symbol %d: ", i);
        scanf("%d", &a[i].freq);
        freq_arr[i] = a[i].freq;
    }

    int m = n_sym;
    for(int i = 0; i < n_sym - 1; i++) {
        int f1 = 1e9, f2 = 1e9, n1 = -1, n2 = -1;
        for(int j = 0; j < m; j++) {
            if(!parent_arr[j] && freq_arr[j] < f1) { 
                f2 = f1; n2 = n1; f1 = freq_arr[j]; n1 = j; 
            } else if(!parent_arr[j] && freq_arr[j] < f2) { 
                f2 = freq_arr[j]; n2 = j; 
            }
        }
        parent_arr[n1] = parent_arr[n2] = 1;
        freq_arr[m] = f1 + f2;
        left_arr[m] = n1; 
        right_arr[m] = n2;
        m++;
    }

    if(m > 0) getLen(m - 1, 0);

    for(int i = 0; i < n_sym - 1; i++) {
        for(int j = i + 1; j < n_sym; j++) {
            if(a[i].len > a[j].len || (a[i].len == a[j].len && a[i].sym > a[j].sym)) {
                Node t = a[i]; a[i] = a[j]; a[j] = t;
            }
        }
    }

    unsigned long long code = 0;
    int last_len = a[0].len;
    printf("\nCanonical Huffman Codebook:\n");
    for(int i = 0; i < n_sym; i++) {
        if(i > 0) code = (code + 1) << (a[i].len - last_len);
        last_len = a[i].len;
        printf("Symbol %d: Len = %d, Code = ", a[i].sym, a[i].len);
        for(int b = a[i].len - 1; b >= 0; b--)
            printf("%d", (int)((code >> b) & 1));
        printf("\n");
    }
    return 0;
}
/*------SAMPLE OUTPUT--------
Enter number of symbols: 3
Frequency of symbol 0: 2
Frequency of symbol 1: 3
Frequency of symbol 2: 5

Canonical Huffman Codebook:
Symbol 2: Len = 1, Code = 0
Symbol 0: Len = 2, Code = 10
Symbol 1: Len = 2, Code = 11
*/