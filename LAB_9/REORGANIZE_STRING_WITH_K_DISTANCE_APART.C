/*Read string S and integer K
n = length of S
Initialize count array of size 26 to 0
Initialize next array of size 26 to 0

For i = 0 to n - 1:
    count[S[i] - 'a'] = count[S[i] - 'a'] + 1
End For

Initialize result string res of length n + 1, with res[n] = '\0'

For i = 0 to n - 1:
    best = -1
    max = -1
    
    For c = 0 to 25:
        If count[c] > max and next[c] <= i then
            max = count[c]
            best = c
        End If
    End For
    
    If best == -1 then
        Print "Impossible to rearrange."
        Free res
        Exit
    End If
    
    res[i] = best + 'a'
    count[best] = count[best] - 1
    next[best] = i + K
End For

Print "Rearranged string: ", res
Free res
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char s[1000];
    int k, n;
    int count[26] = {0};
    int next[26] = {0};
    char *res;
    int i, c;
    int best, max;

    printf("Enter string S: ");
    if (scanf("%999s", s) != 1) return 1;

    printf("Enter integer K: ");
    if (scanf("%d", &k) != 1) return 1;

    n = strlen(s);
    for (i = 0; i < n; i++) {
        count[s[i] - 'a']++;
    }

    res = (char*)malloc(n + 1);
    if (res == NULL) return 1;
    res[n] = '\0';

    for (i = 0; i < n; i++) {
        best = -1;
        max = 0; // Fixed: start max at 0 so we only pick characters with count > 0
        
        for (c = 0; c < 26; c++) {
            if (count[c] > max && next[c] <= i) {
                max = count[c];
                best = c;
            }
        }
        
        if (best == -1) {
            printf("Impossible to rearrange.\n");
            free(res);
            return 0;
        }
        
        res[i] = best + 'a';
        count[best]--;
        next[best] = i + k;
    }

    printf("Rearranged string: %s\n", res);
    free(res);
    return 0;
}
/*--------SAMPLE OUTPUT---------
Enter string S: abcbdcsa
Enter integer K: 3
Rearranged string: abcabcds

Enter string S: abcbdcsa
Enter integer K: 5
Rearranged string: abcdsabc
*/