/*
 * Tema 2 ASC
 * 2024 Spring
 */
#include "utils.h"

/*
 * Function for (A' * B + B * A) * B'
 * where:
 *		A and B are N x N matrices
 * 		A is an upper triangular matrix
 */
double* my_solver(int N, double *A, double* B) {
    double *A_t = calloc(N * N, sizeof(double));
    double *B_t = calloc(N * N, sizeof(double));

    for (register int i = 0; i < N; i++) {
        register double *p_A_t = A + i * N;
        register double *p_B_t = B + i * N;

        for (register int j = 0; j < N; j++) {
            A_t[j * N + i] = *p_A_t;
            B_t[j * N + i] = *p_B_t;
            p_A_t++;
            p_B_t++;
        }
    }

    double *A_t_times_B = calloc(N * N, sizeof(double));

    for (register int i = 0; i < N; i++) {
        register double *p_A_t = &A_t[i * N];
        register double *p_A_t_times_B = &A_t_times_B[i * N];

		for (register int k = 0; k <= i; k++) {
			register double *p_B = &B[k * N];

			for (register int j = 0; j < N; j++) {
				p_A_t_times_B[j] += *p_A_t * p_B[j];
            }

            p_A_t++;
		}
	}

	double *B_times_A = calloc(N * N, sizeof(double));

	for (register int i = 0; i < N; i++) {
		register double *p_B = &B[i * N];
		register double *p_B_times_A = &B_times_A[i * N];

		for (register int k = 0; k < N; k++) {
			register double *p_A = &A[k * N];

			for (register int j = k; j < N; j++) {
				p_B_times_A[j] += *p_B * p_A[j];
			}

			p_B++;
		}
	}

	double *left_m = calloc(N * N, sizeof(double));

	for (register int i = 0; i < N; i++) {
		register double *p_A_t_times_B = &A_t_times_B[i * N];
		register double *p_B_times_A = &B_times_A[i * N];
		register double *p_left_m = &left_m[i * N];

		for (register int j = 0; j < N; j++) {
			*p_left_m = *p_A_t_times_B + *p_B_times_A;
			p_A_t_times_B++;
			p_B_times_A++;
			p_left_m++;
		}
	}

	double *result = calloc(N * N, sizeof(double));

	for (register int i = 0; i < N; i++) {
		register double *p_left_m = &left_m[i * N];
		register double *p_result = &result[i * N];

		for (register int k = 0; k < N; k++) {
			register double *p_B_t = &B_t[k * N];

			for (register int j = 0; j < N; j++) {
				p_result[j] += *p_left_m * p_B_t[j];
			}

			p_left_m++;
		}
	}

	free(A_t_times_B);
	free(B_times_A);
	free(left_m);
	free(A_t);
	free(B_t);

	return result;
}
