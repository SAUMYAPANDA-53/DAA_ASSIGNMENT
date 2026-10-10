/*-----------PSEUDOCODE---------
Algorithm MinMeetingRooms(start_times, end_times, n)
    Sort start_times in ascending order
    Sort end_times in ascending order
    
    rooms = 0
    max_rooms = 0
    i = 0
    j = 0
    
    while i < n do
        if start_times[i] < end_times[j] then
            rooms = rooms + 1
            i = i + 1
        else
            rooms = rooms - 1
            j = j + 1
        end if
        
        if rooms > max_rooms then
            max_rooms = rooms
        end if
    end while
    
    return max_rooms
*/

#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n;
    printf("Enter number of meetings: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    int s[n], e[n];
    printf("Enter start and end times for each meeting:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &s[i], &e[i]);
    }

    qsort(s, n, sizeof(int), compare);
    qsort(e, n, sizeof(int), compare);

    int rooms = 0, max_rooms = 0, i = 0, j = 0;
    while (i < n) {
        if (s[i] < e[j]) {
            rooms++;
            i++;
        } else {
            rooms--;
            j++;
        }
        if (rooms > max_rooms) {
            max_rooms = rooms;
        }
    }

    printf("Minimum rooms required: %d\n", max_rooms);
    return 0;
}
/*----------SAMPLE OUTPUT----------
Enter number of meetings: 3
Enter start and end times for each meeting:
1 2
1 3
2 4
Minimum rooms required: 2
*/