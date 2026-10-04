/*-------PSEUDOCODE-------
FUNCTION next_collatz(n):
    IF n % 2 == 0 THEN
        RETURN n / 2
    ELSE
        RETURN 3 * n + 1
FUNCTION print_trajectory(n):
    PRINT n
    WHILE n > 1:
        n = next_collatz(n)
        PRINT n
FUNCTION analyze_interval(a, b):
    FOR n FROM a TO b DO:
        PRINT "Trajectory for", n
        print_trajectory(n)
START:
    READ choice (1: single value, 2: interval [a, b])
    IF choice == 1 THEN
        READ n
        print_trajectory(n)
    ELSE IF choice == 2 THEN
        READ a, b
        analyze_interval(a, b)
END
*/
#include <stdio.h>

long long next_collatz(long long n) {
    return (n % 2 == 0) ? n / 2 : 3 * n + 1;
}

void print_trajectory(long long n) {
    printf("Trajectory: %lld", n);
    while (n > 1) {
        n = next_collatz(n);
        printf(" -> %lld", n);
    }
    printf("\n");
}

int main() {
    int choice;
    printf("1. Single n\n2. Interval [a, b]\nChoice: ");
    if (scanf("%d", &choice) != 1) return 1;

    if (choice == 1) {
        long long n;
        printf("Enter n: ");
        scanf("%lld", &n);
        print_trajectory(n);
    } else {
        long long a, b;
        printf("Enter a b: ");
        scanf("%lld %lld", &a, &b);
        for (long long i = a; i <= b; i++) {
            printf("\n--- n = %lld ---\n", i);
            print_trajectory(i);
        }
    }
    return 0;
}
/*-------SAMPLE OUTPUT--------
1. Single n
2. Interval [a, b]
Choice: 4
Enter a b: 1 6

--- n = 1 ---
Trajectory: 1
--- n = 2 ---
Trajectory: 2 -> 1
--- n = 3 ---
Trajectory: 3 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1
--- n = 4 ---
Trajectory: 4 -> 2 -> 1
--- n = 5 ---
Trajectory: 5 -> 16 -> 8 -> 4 -> 2 -> 1
--- n = 6 ---
Trajectory: 6 -> 3 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1
*/