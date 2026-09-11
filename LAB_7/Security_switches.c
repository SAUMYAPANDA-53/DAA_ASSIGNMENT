/*-------ALGORITHM---------
Algorithm TurnOff(n, switches):
    Input: Number of switches n, binary array switches of size n (1 = ON, 0 = OFF)
    Output: Sequence of moves to turn OFF switches from index 1 to n

    if n == 1 then
        Toggle switch 1
        switches[1] = 0
        return

    if n == 2 then
        Toggle switch 2   // Valid because switch 1 is ON
        switches[2] = 0
        Toggle switch 1
        switches[1] = 0
        return

    // Step 1: Turn OFF switches 1 to n-2
    TurnOff(n - 2, switches)

    // Step 2: Toggle switch n (now valid because switch n-1 is 1 and 1..n-2 are 0)
    Toggle switch n
    switches[n] = 0

    // Step 3: Turn ON switches 1 to n-2
    TurnOn(n - 2, switches)

    // Step 4: Turn OFF switches 1 to n-1
    TurnOff(n - 1, switches)


Algorithm TurnOn(n, switches):
    if n == 1 then
        Toggle switch 1
        switches[1] = 1
        return

    if n == 2 then
        Toggle switch 1
        switches[1] = 1
        Toggle switch 2
        switches[2] = 1
        return

    // Step 1: Turn ON switches 1 to n-1
    TurnOn(n - 1, switches)

    // Step 2: Turn OFF switches 1 to n-2
    TurnOff(n - 2, switches)

    // Step 3: Toggle switch n
    Toggle switch n
    switches[n] = 1

    // Step 4: Turn ON switches 1 to n-2
    TurnOn(n - 2, switches)
*/

/*------CODE-------*/

#include <stdio.h>
#include <math.h>

int state, moves = 0;

void print_state(int n) {
    for (int i = n - 1; i >= 0; i--) printf("%d", (state >> i) & 1);
    printf("\n");
}

// mode: 0 to turn OFF, 1 to turn ON
void process(int k, int mode, int n) {
    if (k <= 0) return;
    if (k == 1) {
        state ^= 1; // Toggle rightmost switch
        printf("Move %2d: Switch 1 -> ", ++moves);
        print_state(n);
        return;
    }
    
    process(k - (mode ? 1 : 2), mode, n);
    
    // Toggle switch k
    state ^= (1 << (k - 1));
    printf("Move %2d: Switch %d -> ", ++moves, k);
    print_state(n);
    
    process(k - 2, 1, n);
    process(k - (mode ? 2 : 1), 0, n);
}

int main() {
    int n = 4; // Change n as needed
    state = (1 << n) - 1; // Initialize all n switches to 1 (ON)
    
    printf("Initial State: ");
    print_state(n);
    printf("-------------------------\n");

    process(n, 0, n); // Turn OFF all switches

    printf("-------------------------\n");
    printf("Total Moves: %d | Theoretical: %d\n", moves, (int)floor(pow(2, n + 1) / 3.0));
    return 0;
}
/*-----SAMPLE OUTPUT--------
Initial State: 1111
-------------------------
Move  1: Switch 2 -> 1101
Move  2: Switch 1 -> 1100
Move  3: Switch 4 -> 0100
Move  4: Switch 1 -> 0101
Move  5: Switch 2 -> 0111
Move  6: Switch 1 -> 0110
Move  7: Switch 3 -> 0010
Move  8: Switch 1 -> 0011
Move  9: Switch 2 -> 0001
Move 10: Switch 1 -> 0000
-------------------------*/