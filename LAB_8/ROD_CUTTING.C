/*------ALGORITHM---------
ALGORITHM ExtendedRodCutting(P, n)
    Input: Array P[1..n] of prices, rod length n
    Output: Maximum revenue, and reconstructed optimal piece lengths

    Initialize DP array R[0..n] with 0
    Initialize choice array choices[0..n] with 0

    FOR i = 1 TO n DO
        max_val = -infinity
        FOR j = 1 TO i DO
            IF P[j] + R[i - j] > max_val THEN
                max_val = P[j] + R[i - j]
                choices[i] = j
            END IF
        END FOR
        R[i] = max_val
    END FOR

    PRINT "Maximum Revenue:", R[n]
    PRINT "Piece lengths:"
    temp_n = n
    WHILE temp_n > 0 DO
        PRINT choices[temp_n]
        temp_n = temp_n - choices[temp_n]
    END WHILE
*/

#include <stdio.h>

void cutRod(int price[], int n) {
    int r[n + 1], choices[n + 1];
    r[0] = 0;

    for (int i = 1; i <= n; i++) {
        int max_val = -1;
        for (int j = 1; j <= i; j++) {
            if (price[j - 1] + r[i - j] > max_val) {
                max_val = price[j - 1] + r[i - j];
                choices[i] = j;
            }
        }
        r[i] = max_val;
    }

    // (i) Maximum Revenue
    printf("\nMax Revenue: %d\n", r[n]);

    // (ii) Reconstruction of Piece Lengths
    printf("Piece Lengths: ");
    while (n > 0) {
        printf("%d ", choices[n]);
        n -= choices[n];
    }
    printf("\n");
}

int main() {
    int n;

    printf("Enter the length of the rod: ");
    scanf("%d", &n);

    int price[n];
    printf("Enter the prices for lengths 1 to %d:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Price for length %d: ", i + 1);
        scanf("%d", &price[i]);
    }

    cutRod(price, n);

    return 0;
}

/*----------SAMPLE OUTPUT----------Enter the length of the rod: 4
Enter the prices for lengths 1 to 4:
Price for length 1: 21
Price for length 2: 23
Price for length 3: 56
Price for length 4: 23

Max Revenue: 84
Piece Lengths: 1 1 1 1 
*/