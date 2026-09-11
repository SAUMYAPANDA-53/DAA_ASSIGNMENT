/*------ALGORITHM---------
Algorithm HitMovingTarget(n):
    Input: Number of hiding spots n (n > 1)
    Output: Sequence of shots that guarantees hitting the target

    if n == 2 then
        Shoot spot 2
        Shoot spot 2
        return

    // Phase 1: Catch target if it started at an EVEN position
    for spot = 2 to n - 1 do
        Shoot(spot)

    // Phase 2: Catch target if it started at an ODD position
    for spot = 2 to n - 1 do
        Shoot(spot)
*/
/*-------CODE-------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int simulate_shot(int shot_spot, int *target_spot, int n) {
    if (shot_spot == *target_spot) return 1; // Target hit!

    // Target moves to an adjacent spot
    if (*target_spot == 1) *target_spot = 2;
    else if (*target_spot == n) *target_spot = n - 1;
    else *target_spot += (rand() % 2 == 0) ? 1 : -1;

    return 0;
}

int main() {
    int n, shots[100], num_shots = 0;
    printf("Enter number of spots n (n > 1): ");
    if (scanf("%d", &n) != 1 || n <= 1) return 1;

    // Generate guaranteed shooting sequence
    if (n == 2) {
        shots[num_shots++] = 2;
        shots[num_shots++] = 2;
    } else {
        for (int phase = 0; phase < 2; phase++) {
            for (int spot = 2; spot <= n - 1; spot++) {
                shots[num_shots++] = spot;
            }
        }
    }

    printf("\nGuaranteed Shooting Sequence (%d shots): ", num_shots);
    for (int i = 0; i < num_shots; i++) printf("%d ", shots[i]);
    printf("\n\n--- Simulation ---\n");

    srand(time(NULL));
    int initial_target = (rand() % n) + 1;
    int target = initial_target;
    printf("Target starts at spot: %d\n", initial_target);

    for (int step = 0; step < num_shots; step++) {
        printf("Shot %2d at spot %d | Target was at %d -> ", step + 1, shots[step], target);
        if (simulate_shot(shots[step], &target, n)) {
            printf("HIT!\n");
            break;
        }
        printf("MISSED (Target moved to %d)\n", target);
    }
    return 0;
}
/*----------SAMPLE OUTPUT---------
Enter number of spots n (n > 1): 4

Guaranteed Shooting Sequence (4 shots): 2 3 2 3 

--- Simulation ---
Target starts at spot: 2
Shot  1 at spot 2 | Target was at 2 -> HIT!
*/