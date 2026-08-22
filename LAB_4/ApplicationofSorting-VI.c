/*ALGOS 
// Question 6: Point in Maximum Intervals
Algorithm MAX_INTERVAL_POINT(S, n):
    For each interval i in S:
        events.add((l_i, +1))
        events.add((r_i, -1))
    Sort events by coordinate  // O(n log n)[cite: 1]
    max_overlap = 0, current_overlap = 0, best_point = 0
    For each event in events:
        current_overlap = current_overlap + event.val
        If current_overlap > max_overlap:
            max_overlap = current_overlap
            best_point = event.coord
    Return best_point, max_overlap
*/

#include <stdio.h>
#include <stdlib.h>

// Structure to represent an event on the line
typedef struct {
    int coord;
    int type; // +1 for interval start, -1 for interval end
} Event;

// Comparison function for qsort
int compareEvents(const void *a, const void *b) {
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;
    
    if (e1->coord != e2->coord) {
        return e1->coord - e2->coord;
    }
    // If coordinates are equal, process start (+1) before end (-1)
    // so that endpoints are correctly included at that coordinate.
    return e2->type - e1->type; 
}

// Function to find the optimal point with maximum interval overlap
void findOptimalPoint(int n, int intervals[][2]) {
    Event *events = (Event *)malloc(2 * n * sizeof(Event));
    if (!events) {
        perror("Memory allocation failed");
        return;
    }

    // Populate events for each interval
    for (int i = 0; i < n; i++) {
        events[2 * i].coord = intervals[i][0];
        events[2 * i].type = 1;      // Interval starts
        events[2 * i + 1].coord = intervals[i][1];
        events[2 * i + 1].type = -1; // Interval ends
    }

    // Sort events in O(n log n) time
    qsort(events, 2 * n, sizeof(Event), compareEvents);

    int current_overlap = 0;
    int max_overlap = 0;
    int best_point = events[0].coord;

    int i = 0;
    while (i < 2 * n) {
        int current_coord = events[i].coord;
        
        // 1. Process all start events (+1) at current_coord
        int j = i;
        while (j < 2 * n && events[j].coord == current_coord && events[j].type == 1) {
            current_overlap += events[j].type;
            j++;
        }

        // 2. Update maximum overlap and optimal point record
        if (current_overlap > max_overlap) {
            max_overlap = current_overlap;
            best_point = current_coord;
        }

        // 3. Process all end events (-1) at current_coord
        while (j < 2 * n && events[j].coord == current_coord && events[j].type == -1) {
            current_overlap += events[j].type; // Subtracts 1
            j++;
        }

        i = j;
    }

    printf("Validation Results:\n");
    printf("-------------------\n");
    printf("Maximum number of overlapping intervals: %d\n", max_overlap);
    printf("Optimal point p: %d\n", best_point);

    free(events);
}

int main() {
    // Example dataset provided in the prompt: S = {(10,40),(20,60),(50,90),(15,70)}
    int intervals[][2] = {
        {10, 40},
        {20, 60},
        {50, 90},
        {15, 70}
    };
    int n = sizeof(intervals) / sizeof(intervals[0]);

    printf("Input Intervals Set S:\n");
    for (int i = 0; i < n; i++) {
        printf("Interval %d: [%d, %d]\n", i + 1, intervals[i][0], intervals[i][1]);
    }
    printf("\n");

    findOptimalPoint(n, intervals);

    return 0;
}
/* ---- SAMPLE OUTPUT ----
Input Intervals Set S:
Interval 1: [10, 40]
Interval 2: [20, 60]
Interval 3: [50, 90]
Interval 4: [15, 70]

Validation Results:
-------------------
Maximum number of overlapping intervals: 3
Optimal point p: 20
*/