#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define GRAPH_WIDTH 40  // Maximum width of the ASCII bar graph

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

// Function to print a scaled ASCII bar graph
void print_ascii_bar(double value, double max_val) {
    int bar_length = 0;

    // Use logarithmic scaling to handle large differences in magnitudes
    if (value > 0 && max_val > 0) {
        double log_val = log10(value > 1.0 ? value : 1.0);
        double log_max = log10(max_val);
        
        if (log_max > 0) {
            bar_length = (int)((log_val / log_max) * GRAPH_WIDTH);
        }
    }

    // Print the bar
    printf("[");
    for (int i = 0; i < GRAPH_WIDTH; i++) {
        if (i < bar_length) {
            printf("#");
        } else {
            printf(" ");
        }
    }
    printf("]");
}

int main() {
    // Note: n is set to 100 for evaluation safety (f10: 3^n overflows double at n=100000)
    double n = 100.0; 

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

    // Calculate values
    for (int i = 0; i < num_funcs; i++) {
        funcs[i].value = funcs[i].func(n);
    }

    // Sort functions in increasing order
    qsort(funcs, num_funcs, sizeof(Function), compare);

    // Get the maximum value for ASCII bar scaling
    double max_value = funcs[num_funcs - 1].value;

    printf("Functions in increasing order of growth for n = %.0f:\n", n);
    printf("-----------------------------------------------------------------------------------\n");
    printf("%-3s | %-12s | %-12s | %s\n", "Pos", "Function", "Value", "Relative Scale (Log)");
    printf("-----------------------------------------------------------------------------------\n");

    for (int i = 0; i < num_funcs; i++) {
        printf("%2d. | %-12s | %-12.4e | ", i + 1, funcs[i].name, funcs[i].value);
        print_ascii_bar(funcs[i].value, max_value);
        printf("\n");
    }
    printf("-----------------------------------------------------------------------------------\n");

    return 0;
}

/* Sample output :
Functions in increasing order of growth for n = 100:
-----------------------------------------------------------------------------------
Pos | Function     | Value        | Relative Scale (Log)
-----------------------------------------------------------------------------------
 1. | 1 / n        | 1.0000e-002  | [                                        ]
 2. | log2(n)      | 6.6439e+000  | [                                        ]
 3. | n^0.51       | 1.0471e+001  | [                                        ]
 4. | 12 sqrt(n)   | 1.2000e+002  | [#                                       ]
 5. | 50n^0.5      | 5.0000e+002  | [##                                      ]
 6. | n log2(n)    | 6.6439e+002  | [##                                      ]
 7. | n^2 - 324    | 9.6760e+003  | [###                                     ]
 8. | 100n^2 + 6n  | 1.0006e+006  | [#####                                   ]
 9. | 2n^3         | 2.0000e+006  | [#####                                   ]
10. | 2^32 * n     | 4.2950e+011  | [#########                               ]
11. | n^(log2(n))  | 1.9396e+013  | [###########                             ]
12. | 3^n          | 5.1538e+047  | [########################################]
-----------------------------------------------------------------------------------
*/
12. 3^n             (Value: 1.#INF00e+000)*/
