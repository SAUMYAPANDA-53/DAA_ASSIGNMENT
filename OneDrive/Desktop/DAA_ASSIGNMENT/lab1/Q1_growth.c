#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    char name[20];
    double (*func)(double);
    double value;
} Function;

double f1(double n) { return n * log2(n); }
double f2(double n) { return 12.0 * sqrt(n); }
double f3(double n) { return 1.0 / n; }
double f4(double n) { return pow(n, log2(n)); }
double f5(double n) { return 100.0 * n * n + 6.0 * n; }
double f6(double n) { return pow(n, 0.51); }
double f7(double n) { return n * n - 324.0; }
double f8(double n) { return 50.0 * pow(n, 0.5); }
double f9(double n) { return 2.0 * pow(n, 3); }
double f10(double n) { return pow(3.0, n); }
double f11(double n) { return pow(2.0, 32) * n; }
double f12(double n) { return log2(n); }


int compare(const void *a, const void *b) {
    Function *fA = (Function *)a;
    Function *fB = (Function *)b;
    if (fA->value < fB->value) return -1;
    if (fA->value > fB->value) return 1;
    return 0;
}

int main() {
    double n = 100000.0; 

    Function funcs[] = {
        {"n log2(n)", f1, 0},
        {"12 sqrt(n)", f2, 0},
        {"1 / n", f3, 0},
        {"n^(log2(n))", f4, 0},
        {"100n^2 + 6n", f5, 0},
        {"n^0.51", f6, 0},
        {"n^2 - 324", f7, 0},
        {"50n^0.5", f8, 0},
        {"2n^3", f9, 0},
        {"3^n", f10, 0},
        {"2^32 * n", f11, 0},
        {"log2(n)", f12, 0}
    };

    int num_funcs = sizeof(funcs) / sizeof(funcs[0]);

    
    for (int i = 0; i < num_funcs; i++) {
        funcs[i].value = funcs[i].func(n);
    }

    
    qsort(funcs, num_funcs, sizeof(Function), compare);

    printf("Functions in increasing order of growth for n = %.0f:\n", n);
    for (int i = 0; i < num_funcs; i++) {
        printf("%2d. %-15s (Value: %e)\n", i + 1, funcs[i].name, funcs[i].value);
    }

    return 0;
}

/*Sample output :
Functions in increasing order of growth for n = 100000:
 1. 1 / n           (Value: 1.000000e-005)
 2. log2(n)         (Value: 1.660964e+001)
 3. n^0.51          (Value: 3.548134e+002)
 4. 12 sqrt(n)      (Value: 3.794733e+003)
 5. 50n^0.5         (Value: 1.581139e+004)
 6. n log2(n)       (Value: 1.660964e+006)
 7. n^2 - 324       (Value: 1.000000e+010)
 8. 100n^2 + 6n     (Value: 1.000001e+012)
 9. 2^32 * n        (Value: 4.294967e+014)
10. 2n^3            (Value: 2.000000e+015)
11. n^(log2(n))     (Value: 1.117384e+083)
12. 3^n             (Value: 1.#INF00e+000)*/