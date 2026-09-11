/*-----ALGORITHM--------
Algorithm BestTimeToBeAlive(index):
    Input: Array of N scientists with (name, birth_year, death_year)
    Output: Peak year and maximum number of scientists alive simultaneously

    Create an array Events of size 2 * N

    for i = 0 to N - 1 do:
        Events[2*i]     = Event(year = index[i].birth_year, type = +1)
        Events[2*i + 1] = Event(year = index[i].death_year + 1, type = -1)

    // Sort events primarily by year ASCENDING.
    // Ties broken by type ASCENDING (-1 before +1)
    Sort(Events)

    current_alive = 0
    max_alive = 0
    best_year = -1

    for event in Events do:
        current_alive = current_alive + event.type
        if current_alive > max_alive then:
            max_alive = current_alive
            best_year = event.year

    return best_year, max_alive
*/
/*------CODE---------*/
#include <stdio.h>
#include <stdlib.h>

// Represents a birth or death event
typedef struct {
    int year;
    int type; // +1 for birth, -1 for death
} Event;

// Compare events by year; if years are equal, death (-1) comes before birth (+1)
int compareEvents(const void *a, const void *b) {
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    if (e1->year != e2->year) {
        return e1->year - e2->year;
    }
    return e1->type - e2->type;
}

int main() {
    // Sample dataset: Birth and Death years of scientists
    int birth_years[] = {1643, 1646, 1635, 1629, 1656};
    int death_years[] = {1727, 1716, 1703, 1695, 1742};
    int n = sizeof(birth_years) / sizeof(birth_years[0]);

    // Create 2 events for each scientist
    Event events[2 * n];
    for (int i = 0; i < n; i++) {
        events[2 * i]     = (Event){birth_years[i], +1};
        events[2 * i + 1] = (Event){death_years[i] + 1, -1}; // +1 since alive through death year
    }

    // Sort events chronologically
    qsort(events, 2 * n, sizeof(Event), compareEvents);

    // Sweep line to find peak overlap
    int current_alive = 0;
    int max_alive = 0;
    int peak_year = 0;

    for (int i = 0; i < 2 * n; i++) {
        current_alive += events[i].type;
        if (current_alive > max_alive) {
            max_alive = current_alive;
            peak_year = events[i].year;
        }
    }

    // Output result
    printf("Peak Year: %d\n", peak_year);
    printf("Max Scientists Alive Simultaneously: %d\n", max_alive);

    return 0;
}
/*-----SAMPLE OUTPUT---------

Peak Year: 1656
Max Scientists Alive Simultaneously: 5

*/