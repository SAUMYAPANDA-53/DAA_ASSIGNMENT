#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRINGS 100
#define MAX_LENGTH 100

// Calculates the maximum overlap where a suffix of 'a' matches a prefix of 'b'
int find_overlap(const char *a, const char *b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    int max_overlap = 0;
    int limit = (len_a < len_b) ? len_a : len_b;

    for (int i = 1; i <= limit; i++) {
        if (strncmp(a + len_a - i, b, i) == 0) {
            max_overlap = i;
        }
    }
    return max_overlap;
}

// Merges two strings based on their calculated overlap length
void merge_strings(const char *a, const char *b, int overlap, char *dest) {
    strcpy(dest, a);
    strcat(dest, b + overlap);
}

int main() {
    int n;
    
    // User input for the number of strings
    printf("Enter the number of strings: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_STRINGS) {
        printf("Invalid number of strings.\n");
        return 1;
    }

    char strings[MAX_STRINGS][MAX_LENGTH];
    printf("Enter %d strings:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%99s", strings[i]);
    }

    int current_count = n;

    // Greedily merge pairs with maximum overlap until one string remains[cite: 1]
    while (current_count > 1) {
        int max_overlap = -1;
        int best_i = 0;
        int best_j = 1;

        // Find the pair of distinct strings with the highest overlap
        for (int i = 0; i < current_count; i++) {
            for (int j = 0; j < current_count; j++) {
                if (i == j) continue;

                int overlap = find_overlap(strings[i], strings[j]);
                if (overlap > max_overlap) {
                    max_overlap = overlap;
                    best_i = i;
                    best_j = j;
                }
            }
        }

        // Perform the merge operation
        char merged_result[MAX_LENGTH * 2];
        merge_strings(strings[best_i], strings[best_j], max_overlap, merged_result);

        // Update the array: replace strings[best_i] with the merged string
        strcpy(strings[best_i], merged_result);

        // Shift remaining strings to remove strings[best_j]
        for (int k = best_j; k < current_count - 1; k++) {
            strcpy(strings[k], strings[k + 1]);
        }

        current_count--;
    }

    // Display the final superstring containing all inputs[cite: 1]
    printf("Resulting Superstring: %s\n", strings[0]);

    return 0;
/*Enter the number of strings: 2
Enter 2 strings:
DEFF
FREF
Resulting Superstring: DEFFREF
*/