#include <stdio.h>
#include <stdlib.h>

// Function to calculate minimum moves
int get_min_moves(int n) {
    return (n * (n + 1)) / 6;
}

// Procedure to display and print the moves required to invert the triangle
void generate_moves(int n) {
    int k = n / 3;
    int total_moves = get_min_moves(n);
    
    printf("\n--- Coin Triangle Inversion for n = %d ---\n", n);
    printf("Total Coins: %d\n", n * (n + 1) / 2);
    printf("Minimum Moves Required: %d\n\n", total_moves);

    if (total_moves == 0) {
        printf("No moves required.\n");
        return;
    }

    printf("Step-by-step Coin Relocations (From (row, col) -> To (row, col)):\n");
    
    int move_count = 1;

    // 1. Relocate top corner coins to the new bottom apex
    for (int r = 0; r < k; r++) {
        for (int c = 0; c <= r; c++) {
            // Destination rows correspond to the new inverted point at the bottom
            int target_r = n + r;
            int target_c = c + (n - 1 - r);
            printf("Move %d: Move coin from (%d, %d) to (%d, %d)\n", 
                   move_count++, r, c, target_r, target_c);
        }
    }

    // 2. Relocate bottom-left corner coins to top-left positions
    for (int r = n - k; r < n; r++) {
        for (int c = 0; c < k - (n - 1 - r); c++) {
            int target_r = r - n;
            int target_c = c;
            printf("Move %d: Move coin from (%d, %d) to (%d, %d)\n", 
                   move_count++, r, c, target_r, target_c);
        }
    }

    // 3. Relocate bottom-right corner coins to top-right positions
    for (int r = n - k; r < n; r++) {
        for (int c = r - (k - 1 - (n - 1 - r)); c <= r; c++) {
            int target_r = r - n;
            int target_c = c + k;
            printf("Move %d: Move coin from (%d, %d) to (%d, %d)\n", 
                   move_count++, r, c, target_r, target_c);
        }
    }
}

int main() {
    int n;
    printf("Enter the number of rows (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    generate_moves(n);

    return 0;
}
/*------SAMPLE OUTPUT-----
Enter the number of rows (n): 4

--- Coin Triangle Inversion for n = 4 ---
Total Coins: 10
Minimum Moves Required: 3

Step-by-step Coin Relocations (From (row, col) -> To (row, col)):
Move 1: Move coin from (0, 0) to (4, 3)
Move 2: Move coin from (3, 0) to (-1, 0)
Move 3: Move coin from (3, 3) to (-1, 4)
*/