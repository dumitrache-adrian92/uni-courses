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
	double *A_t_times_B = calloc(N * N, sizeof(double));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k <= i; k++) {
				A_t_times_B[i * N + j] += A[k * N + i] * B[k * N + j];
			}
		}
	}

	double *B_times_A = calloc(N * N, sizeof(double));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k <= j; k++) {
				B_times_A[i * N + j] += B[i * N + k] * A[k * N + j];
			}
		}
	}

	double *left_m = calloc(N * N, sizeof(double));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			left_m[i * N + j] = A_t_times_B[i * N + j] + B_times_A[i * N + j];
		}
	}

	double *result = calloc(N * N, sizeof(double));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				result[i * N + j] += left_m[i * N + k] * B[j * N + k];
			}
		}
	}

	free(A_t_times_B);
	free(B_times_A);
	free(left_m);

	return result;
}
