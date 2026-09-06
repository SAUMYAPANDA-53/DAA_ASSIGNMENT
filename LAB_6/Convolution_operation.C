/*1.
ALGORITHM FFT(a, N, invert)
    Input: Vector 'a' of complex numbers of size N (N must be a power of 2),
           Boolean flag 'invert' (FALSE for Forward FFT, TRUE for Inverse FFT)
    Output: Transformed vector of size N

    IF N == 1 THEN
        RETURN a
    END IF

    // Step 1: Divide into Even and Odd indexed sub-arrays
    Initialize aEven[N / 2]
    Initialize aOdd[N / 2]

    FOR i = 0 TO (N / 2) - 1 DO
        aEven[i] = a[2 * i]
        aOdd[i]  = a[2 * i + 1]
    END FOR

    // Step 2: Conquer (Recursive FFT calls)
    yEven = FFT(aEven, N / 2, invert)
    yOdd  = FFT(aOdd, N / 2, invert)

    // Step 3: Combine using Primitive Roots of Unity
    Initialize y[N]
    angle = (2 * PI / N) * (invert ? -1 : 1)
    
    w  = 1 + 0i                       // Complex number 1
    wN = cos(angle) + i * sin(angle)   // Twiddle factor base

    FOR k = 0 TO (N / 2) - 1 DO
        y[k]           = yEven[k] + w * yOdd[k]
        y[k + (N / 2)] = yEven[k] - w * yOdd[k]

        IF invert THEN
            y[k]           = y[k] / 2
            y[k + (N / 2)] = y[k + (N / 2)] / 2
        END IF

        w = w * wN
    END FOR

    RETURN y
END ALGORITHM

2.
ALGORITHM VectorConvolutionFFT(A, B, m, n)
    Input: Array A of size m, Array B of size n (n >= m)[cite: 1]
    Output: Resulting convolved array C of size m + n - 1

    // Step 1: Find next power of 2 >= (m + n - 1)
    targetSize = m + n - 1
    N = 1
    WHILE N < targetSize DO
        N = N * 2
    END WHILE

    // Step 2: Zero-pad input vectors up to size N
    Initialize paddedA[N] with 0
    Initialize paddedB[N] with 0

    FOR i = 0 TO m - 1 DO
        paddedA[i] = A[i]
    END FOR

    FOR j = 0 TO n - 1 DO
        paddedB[j] = B[j]
    END FOR

    // Step 3: Compute Point-Value representation via FFT
    FA = FFT(paddedA, N, FALSE)
    FB = FFT(paddedB, N, FALSE)

    // Step 4: Pointwise multiplication in frequency domain O(N)
    Initialize FC[N]
    FOR k = 0 TO N - 1 DO
        FC[k] = FA[k] * FB[k]
    END FOR

    // Step 5: Convert back using Inverse FFT (IFFT)
    complexC = FFT(FC, N, TRUE)

    // Step 6: Extract real part into output array C
    Initialize C[targetSize]
    FOR i = 0 TO targetSize - 1 DO
        C[i] = REAL_PART(complexC[i])
    END FOR

    RETURN C
END ALGORITHM
*/

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
