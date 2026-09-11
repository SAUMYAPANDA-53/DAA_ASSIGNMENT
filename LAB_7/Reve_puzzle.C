#include <stdio.h>
#include <math.h>

// Global counter for tracking total moves
long long move_count = 0;

// Standard 3-peg Tower of Hanoi for remaining (n - k) disks
void hanoi_3pegs(int n, char src, char dst, char aux) {
    if (n == 0) return;
    hanoi_3pegs(n - 1, src, aux, dst);
    printf("Move disk %d from %c to %c\n", n, src, dst);
    move_count++;
    hanoi_3pegs(n - 1, aux, dst, src);
}

// Compute optimal k split for Frame-Stewart algorithm
int get_optimal_k(int n) {
    if (n <= 1) return 0;
    return n - (int)round(sqrt(2 * n + 1) - 0.5);
}

// 4-peg Frame-Stewart algorithm for Reve's Puzzle
void reves_puzzle(int n, char src, char dst, char aux1, char aux2) {
    if (n == 0) return;
    if (n == 1) {
        printf("Move disk %d from %c to %c\n", n, src, dst);
        move_count++;
        return;
    }

    int k = get_optimal_k(n);

    // Step 1: Move top k disks to aux1 using all 4 pegs
    reves_puzzle(k, src, aux1, aux2, dst);

    // Step 2: Move remaining (n - k) disks to dst using 3 pegs
    hanoi_3pegs(n - k, src, dst, aux2);

    // Step 3: Move k disks from aux1 to dst using all 4 pegs
    reves_puzzle(k, aux1, dst, src, aux2);
}

int main() {
    int n;

    // Prompt user for input
    printf("Enter the number of disks (n): ");
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("Please enter a valid positive integer.\n");
        return 1;
    }

    char src = 'A', dst = 'B', aux1 = 'C', aux2 = 'D';

    printf("\n--- Solution Sequence for n = %d disks ---\n\n", n);
    reves_puzzle(n, src, dst, aux1, aux2);

    printf("\nTotal moves executed: %lld\n", move_count);
    return 0;
}
/*----------SAMPLE OUTPUT--------
Enter the number of disks (n): 5

--- Solution Sequence for n = 5 disks ---

Move disk 1 from A to B
Move disk 2 from A to C
Move disk 1 from B to C
Move disk 1 from A to B
Move disk 2 from A to D
Move disk 1 from B to D
Move disk 3 from A to B
Move disk 1 from D to A
Move disk 2 from D to B
Move disk 1 from A to B
Move disk 1 from C to D
Move disk 2 from C to B
Move disk 1 from D to B

Total moves executed: 13*/
