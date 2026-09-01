#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct {
    double real;
    double imag;
} Complex;

Complex c_add(Complex a, Complex b) {
    return (Complex){a.real + b.real, a.imag + b.imag};
}

Complex c_sub(Complex a, Complex b) {
    return (Complex){a.real - b.real, a.imag - b.imag};
}

Complex c_mul(Complex a, Complex b) {
    return (Complex){
        a.real * b.real - a.imag * b.imag,
        a.real * b.imag + a.imag * b.real
    };
}

void fft(Complex *buf, int n, int invert) {
    if (n <= 1) return;

    Complex *even = (Complex *)malloc((n / 2) * sizeof(Complex));
    Complex *odd = (Complex *)malloc((n / 2) * sizeof(Complex));
    for (int i = 0; i < n / 2; i++) {
        even[i] = buf[2 * i];
        odd[i] = buf[2 * i + 1];
    }

    fft(even, n / 2, invert);
    fft(odd, n / 2, invert);

    double angle = 2 * M_PI / n * (invert ? -1 : 1);
    Complex w = {1, 0};
    Complex wn = {cos(angle), sin(angle)};

    for (int i = 0; i < n / 2; i++) {
        Complex t = c_mul(w, odd[i]);
        buf[i] = c_add(even[i], t);
        buf[i + n / 2] = c_sub(even[i], t);
        if (invert) {
            buf[i].real /= 2;
            buf[i].imag /= 2;
            buf[i + n / 2].real /= 2;
            buf[i + n / 2].imag /= 2;
        }
        w = c_mul(w, wn);
    }

    free(even);
    free(odd);
}

void convolve(const double *A, int m, const double *B, int n, double *C) {
    int len = m + n - 1;
    int N = 1;
    while (N < len) N <<= 1;

    Complex *fa = (Complex *)calloc(N, sizeof(Complex));
    Complex *fb = (Complex *)calloc(N, sizeof(Complex));

    for (int i = 0; i < m; i++) fa[i].real = A[i];
    for (int i = 0; i < n; i++) fb[i].real = B[i];

    fft(fa, N, 0);
    fft(fb, N, 0);

    for (int i = 0; i < N; i++) {
        fa[i] = c_mul(fa[i], fb[i]);
    }

    fft(fa, N, 1);

    for (int i = 0; i < len; i++) {
        C[i] = round(fa[i].real); // Rounded for clean integer-like display if inputs are integers
    }

    free(fa);
    free(fb);
}

int main() {
    int m, n;

    printf("Enter the size of vector A (m): ");
    if (scanf("%d", &m) != 1 || m <= 0) {
        printf("Invalid size for A.\n");
        return 1;
    }

    double *A = (double *)malloc(m * sizeof(double));
    printf("Enter %d elements for vector A:\n", m);
    for (int i = 0; i < m; i++) {
        scanf("%lf", &A[i]);
    }

    printf("Enter the size of vector B (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size for B.\n");
        free(A);
        return 1;
    }

    double *B = (double *)malloc(n * sizeof(double));
    printf("Enter %d elements for vector B:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &B[i]);
    }

    int len = m + n - 1;
    double *C = (double *)malloc(len * sizeof(double));

    convolve(A, m, B, n, C);

    printf("\nConvolution Vector C (size %d):\n", len);
    for (int i = 0; i < len; i++) {
        printf("%.0f ", C[i]);
    }
    printf("\n");

    free(A);
    free(B);
    free(C);

    return 0;
}
/*---------SAMPLE OUTPUT ----------
Enter the size of vector A (m): 3
Enter 3 elements for vector A:
2 3 4
Enter the size of vector B (n): 2
Enter 2 elements for vector B:
5 6

Convolution Vector C (size 4):
10 27 38 24 
*/