    /*  PSEUDOCODE: 
    
    Algorithm SortByColour(A, n):
        // Input: An array A of n pairs (number, colour), sorted by number
        // Output: Array A sorted by colour (red -> blue -> yellow), maintaining stability
        
        Initialize RedQueue as an empty queue
        Initialize BlueQueue as an empty queue
        Initialize YellowQueue as an empty queue
        
        // Step 1: Distribute elements into respective colour queues
        for i = 0 to n - 1:
            if A[i].colour == "red":
                Enqueue(RedQueue, A[i])
            else if A[i].colour == "blue":
                Enqueue(BlueQueue, A[i])
            else if A[i].colour == "yellow":
                Enqueue(YellowQueue, A[i])
                
        // Step 2: Reconstruct the array by copying elements back in order
        idx = 0
        
        while RedQueue is not empty:
            A[idx] = Dequeue(RedQueue)
            idx = idx + 1
            
        while BlueQueue is not empty:
            A[idx] = Dequeue(BlueQueue)
            idx = idx + 1
            
        while YellowQueue is not empty:
            A[idx] = Dequeue(YellowQueue)
            idx = idx + 1
            
        return A
        */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent an item pair (number, colour)
typedef struct {
    int number;
    char colour[10];
} Item;

// Comparison function for qsort to sort items by number (for stability/sorting within colour)
int compareItems(const void* a, const void* b) {
    Item* item1 = (Item*)a;
    Item* item2 = (Item*)b;
    return item1->number - item2->number;
}

int main() {
    int n;

    printf("Enter the number of items (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input for n.\n");
        return 1;
    }

    Item* arr = (Item*)malloc(n * sizeof(Item));

    printf("Enter %d pairs (number and colour: red/blue/yellow):\n", n);
    for (int i = 0; i < n; i++) {
        printf("Item %d - Number: ", i + 1);
        scanf("%d", &arr[i].number);
        printf("Item %d - Colour (red/blue/yellow): ", i + 1);
        scanf("%s", arr[i].colour);
    }

    // Step 1: Separate items into temporary dynamic arrays for each colour
    Item* red = (Item*)malloc(n * sizeof(Item));
    Item* blue = (Item*)malloc(n * sizeof(Item));
    Item* yellow = (Item*)malloc(n * sizeof(Item));
    
    int r_count = 0, b_count = 0, y_count = 0;

    for (int i = 0; i < n; i++) {
        if (strcmp(arr[i].colour, "red") == 0) {
            red[r_count++] = arr[i];
        } else if (strcmp(arr[i].colour, "blue") == 0) {
            blue[b_count++] = arr[i];
        } else if (strcmp(arr[i].colour, "yellow") == 0) {
            yellow[y_count++] = arr[i];
        }
    }

    // Step 2: Sort the numbers within each individual colour group
    qsort(red, r_count, sizeof(Item), compareItems);
    qsort(blue, b_count, sizeof(Item), compareItems);
    qsort(yellow, y_count, sizeof(Item), compareItems);

    // Step 3: Combine them back in the order: Red -> Blue -> Yellow
    int idx = 0;
    for (int i = 0; i < r_count; i++) arr[idx++] = red[i];
    for (int i = 0; i < b_count; i++) arr[idx++] = blue[i];
    for (int i = 0; i < y_count; i++) arr[idx++] = yellow[i];

    printf("\nOutput (Sorted by Colour: Red -> Blue -> Yellow, with numbers sorted per colour):\n");
    for (int i = 0; i < n; i++) {
        printf("(%d, %s) ", arr[i].number, arr[i].colour);
    }
    printf("\n");

    // Clean up dynamic memory
    free(arr);
    free(red);
    free(blue);
    free(yellow);

    return 0;
}/*  ---- SAMPLE INPUT ---- 
Enter the number of items (n): 6
Enter 6 pairs (number and colour: red/blue/yellow):
Item 1 - Number: 12
Item 1 - Colour (red/blue/yellow): blue
Item 2 - Number: 5
Item 2 - Colour (red/blue/yellow): red
Item 3 - Number: 20
Item 3 - Colour (red/blue/yellow): yellow
Item 4 - Number: 2
Item 4 - Colour (red/blue/yellow): blue
Item 5 - Number: 15
Item 5 - Colour (red/blue/yellow): red
Item 6 - Number: 8
Item 6 - Colour (red/blue/yellow): yellow

  ----SAMPLE OUTPUT ----
  Output (Sorted by Colour: Red -> Blue -> Yellow, with numbers sorted per colour):
(5, red) (15, red) (2, blue) (12, blue) (8, yellow) (20, yellow)


*/