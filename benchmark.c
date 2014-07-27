/* CS61C Sp14 Project 3
 *
 * ANY MODIFICATIONS TO THIS FILE WILL BE OVERWRITTEN DURING GRADING
 */

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utils.h"
#include "digit_rec.h"
#include "oracle.h"

static inline float random_float() {
    static union {
        unsigned int d;
        float f;
    } df;
    df.d = (rand() & 0x007fffff) | 0x3f800000;
    return df.f;
}

/* Benchmarks a NxM image with a TxT template, where dimensions are
 * specified as (width)x(height).
 */
int benchmark_matrix(int N, int M, int T) {

    if (N < T || M < T)
        printf("Warning: T (%d) should be no larger than N (%d) or M (%d)\n", T, N, M);

    size_t image_matrix_size = sizeof(float) * N * M;
    size_t template_matrix_size = sizeof(float) * T * T;
    float *A = (float*) malloc(image_matrix_size);
    float *B = (float*) malloc(template_matrix_size);

    float average_distance = 5 * random_float();
    for (int i = 0; i < N * M; i++)
        A[i] = random_float() * 0.1 + average_distance * i / N / M;
    for (int i = 0; i < T * T; i++)
        B[i] = random_float() * 0.1;

    float distance_ref = oracle_calc_min_dist(A, N, M, B, T);
    float* retVal;
    retVal = launch_gpu_computation(A, N, M, B, T);

    float distance = retVal[1];

    free(retVal);

    printf("N=%d M=%d T=%d \t", N, M, T);
    if (!float_equals(distance, distance_ref) && T != 4096) {
        printf("Result does not match oracle (got = %.3f, expected = %.3f)!\n", distance, distance_ref);
        return 0;
    } else if (T == 4096) {
        float diff = distance < distance_ref ? distance_ref-distance : distance - distance_ref;
        if (!(diff / distance_ref < 0.10)) {
            // allow 10% error on 4096 because GPU FP error becomes significant
            // gaming this in an attempt to gain better performance will get you
            // a zero
            printf("Result does not match oracle (got = %.3f, expected = %.3f)!\n", distance, distance_ref);
            return 0;
        }
    }

    double Gflop_s, seconds = -1.0;
    float* returnArr;

    returnArr = launch_gpu_computation(A, N, M, B, T);
    seconds = returnArr[0];
    free(returnArr);


    /** 8 total orientations, 3 operations (subtract, square, reduce-sum) */
    Gflop_s = 8.0 * 3 * T * T * (N - T + 1) * (M - T + 1) * 1e-9 / seconds;

    printf("%.4f Gflop/s\n", Gflop_s);

    free(A);
    free(B);

    return 1;
}

int main(int argc, char** argv) {
    srand(time(NULL));

    for (int i = 512; i < 4096*2; i*=2) {
        benchmark_matrix(i+100, i, i);
    }

    return 0;
}
