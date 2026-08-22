/* ALGORITHM
// Question 5: Interval Merging
Algorithm MERGE_INTERVALS(I, n):
    Sort intervals I by start coordinate in ascending order  // O(n log n)[cite: 1]
    merged = [I[1]]
    For i = 2 to n:
        current = last element in merged
        If current.end >= I[i].start:
            current.end = max(current.end, I[i].end)
        Else:
            merged.add(I[i])
    Return merged
*/


#include <stdio.h>
#include <stdlib.h>

// Structure to represent an interval (x_i, y_i)
typedef struct {
    int start;
    int end;
} Interval;

// Comparison function required by qsort to sort intervals by start time
int compareIntervals(const void *a, const void *b) {
    Interval *intervalA = (Interval *)a;
    Interval *intervalB = (Interval *)b;
    if (intervalA->start < intervalB->start) return -1;
    if (intervalA->start > intervalB->start) return 1;
    return 0;
}

// Function to merge overlapping intervals
int mergeIntervals(Interval intervals[], int n, Interval merged[]) {
    if (n <= 0) return 0;

    // Step 1: Sort intervals in O(n log n) time based on start times
    qsort(intervals, n, sizeof(Interval), compareIntervals);

    // Step 2: Linear sweep to merge overlapping intervals
    int merged_count = 0;
    merged[0] = intervals[0];

    for (int i = 1; i < n; i++) {
        // Check for overlap: current start <= last merged end
        if (intervals[i].start <= merged[merged_count].end) {
            // Merge by taking the maximum end time
            if (intervals[i].end > merged[merged_count].end) {
                merged[merged_count].end = intervals[i].end;
            }
        } else {
            // No overlap, move to the next slot in the merged array
            merged_count++;
            merged[merged_count] = intervals[i];
        }
    }

    return merged_count + 1; // Return the total number of merged intervals
}

int main() {
    int n;

    // 1. Get the number of intervals
    printf("Enter the number of intervals (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input for n.\n");
        return 1;
    }

    // Allocate memory for input intervals and output merged intervals
    Interval *intervals = (Interval *)malloc(n * sizeof(Interval));
    Interval *merged = (Interval *)malloc(n * sizeof(Interval));

    if (intervals == NULL || merged == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // 2. Get interval pairs from user
    printf("Enter the intervals as pairs (start end), e.g., '1 3':\n");
    for (int i = 0; i < n; i++) {
        printf("Interval %d: ", i + 1);
        scanf("%d %d", &intervals[i].start, &intervals[i].end);
    }

    // 3. Process intervals
    int merged_size = mergeIntervals(intervals, n, merged);

    // 4. Output the result
    printf("\n--- Merged Intervals Output ---\n{ ");
    for (int i = 0; i < merged_size; i++) {
        printf("(%d,%d)", merged[i].start, merged[i].end);
        if (i < merged_size - 1) printf(", ");
    }
    printf(" }\n");

    // Clean up allocated memory
    free(intervals);
    free(merged);

    return 0;
}
/*----SAMPLE OUTPUT
Enter the number of intervals (n): 5
Enter the intervals as pairs (start end), e.g., '1 3':
Interval 1: 1 3
Interval 2: 2 6
Interval 3: 7 10
Interval 4: 5 11
Interval 5: 6 9

--- Merged Intervals Output ---
{ (1,11) }
 */