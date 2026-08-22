/*ALGOS

Algorithm PARTY_MAX_PRESENCE(arrival, departure, n):
    For i = 1 to n:
        events.add((arrival[i], +1))
        events.add((departure[i], -1))
    Sort events chronologically by time  // O(n log n)[cite: 1]
    max_people = 0, current_people = 0, best_time = 0
    For each event in events:
        current_people = current_people + event.type
        If current_people > max_people:
            max_people = current_people
            best_time = event.time
    Return best_time, max_people
*/

#include <stdio.h>
#include <stdlib.h>

// Comparison function required by qsort for sorting integers
int compare(const void *a, const void *b) {
    int int_a = *((const int *)a);
    int int_b = *((const int *)b);
    if (int_a < int_b) return -1;
    if (int_a > int_b) return 1;
    return 0;
}

int main() {
    int n;

    // 1. Get the number of persons
    printf("Enter the number of persons attending the party (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input for n.\n");
        return 1;
    }

    // Allocate memory for arrival and departure times
    int *arrival = (int *)malloc(n * sizeof(int));
    int *departure = (int *)malloc(n * sizeof(int));

    if (arrival == NULL || departure == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // 2. Get entry and exit times for each person
    printf("Enter the entry time (a_i) and exit time (b_i) for each person:\n");
    for (int i = 0; i < n; i++) {
        printf("Person %d (Entry Exit): ", i + 1);
        scanf("%d %d", &arrival[i], &departure[i]);
    }

    // 3. Sort arrival and departure arrays independently in O(n log n) time
    qsort(arrival, n, sizeof(int), compare);
    qsort(departure, n, sizeof(int), compare);

    // 4. Two-pointer sweep-line algorithm
    int i = 0, j = 0;
    int current_people = 0;
    int max_people = 0;
    int peak_time = -1;

    while (i < n) {
        if (arrival[i] < departure[j]) {
            current_people++;
            if (current_people > max_people) {
                max_people = current_people;
                peak_time = arrival[i];
            }
            i++;
        } else {
            current_people--;
            j++;
        }
    }

    // 5. Output results
    printf("\n--- Analysis Result ---\n");
    printf("Maximum number of people simultaneously present: %d\n", max_people);
    printf("Time when the peak crowd occurred: %d\n", peak_time);

    // Clean up allocated memory
    free(arrival);
    free(departure);

    return 0;
}

/* ---- SAMPLE OUTPUT ----
Enter the number of persons attending the party (n): 5
Enter the entry time (a_i) and exit time (b_i) for each person:
Person 1 (Entry Exit): 3 6
Person 2 (Entry Exit): 2 5
Person 3 (Entry Exit): 1 4
Person 4 (Entry Exit): 7 10
Person 5 (Entry Exit): 4 7

--- Analysis Result ---
Maximum number of people simultaneously present: 3
Time when the peak crowd occurred: 3
*/