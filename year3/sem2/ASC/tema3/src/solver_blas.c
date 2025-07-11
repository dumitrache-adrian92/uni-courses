/*
 * Tema 2 ASC
 * 2024 Spring
 */
#include "utils.h"
#include <cblas.h>
#include <string.h>

/**
 * Function for (A' * B + B * A) * B'
 * where:
 *		A and B are N x N matrices
 * 		A is an upper triangular matrix
 */
double* my_solver(int N, double *A, double *B) {
	double *B_times_A = malloc(N * N * sizeof(double));
	memcpy(B_times_A, B, N * N * sizeof(double));

	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasNoTrans, CblasNonUnit, N, N, 1.0, A, N, B_times_A, N);

	double *A_t_times_B = malloc(N * N * sizeof(double));
	memcpy(A_t_times_B, B, N * N * sizeof(double));

	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasTrans, CblasNonUnit, N, N, 1.0, A, N, A_t_times_B, N);

	double *left_m = malloc(N * N * sizeof(double));
	memcpy(left_m, A_t_times_B, N * N * sizeof(double));

	cblas_daxpy(N * N, 1.0, B_times_A, 1, left_m, 1);

	double *result = malloc(N * N * sizeof(double));

	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, N, N, N, 1.0, left_m, N, B, N, 0.0, result, N);

	free(B_times_A);
	free(A_t_times_B);
	free(left_m);

	return result;
}
