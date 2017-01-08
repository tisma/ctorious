#include <iostream>
#include <cstdlib>
#include <ctime>
#include <curand.h>
#include <cublas_v2.h>

using namespace std;

void GPU_fill_rand(float* A, int nr_rows_A, int nr_cols_A) {
	curandGenerator_t prng;
	curandCreateGenerator(&prng, CURAND_RNG_PSEUDO_DEFAULT);

	curandSetPseudoRandomGeneratorSeed(prng, (unsigned long long)clock());

	curandGenerateUniform(prng, A, nr_rows_A * nr_cols_A);
}

void gpu_blas_matix_mul(const float* A, const float* B, float* C, const int m, const int k, const int n) {
	int lda = m, ldb = k, ldc = m;
	const float alf = 1.0f;
	const float bet = 0.0f;
	const float* alpha = &alf;
	const float* beta = &bet;

	cublasHandle_t handle;
	cublasCreate(&handle);

	cublasSgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc);

	cublasDestroy(handle);
}

void print_matrix(const float* A, const int nr_rows_A, const int nr_cols_A) {
	for (int i = 0; i < nr_rows_A; i++) {
		for (int j = 0; j < nr_cols_A; j++) {
			cout << A[j * nr_rows_A + i] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

int main() {
	int nr_rows_A = 3, nr_cols_A = 3, nr_rows_B = 3, nr_cols_B = 3, nr_rows_C = 3, nr_cols_C = 3;

	float *h_A = (float*)malloc(nr_rows_A * nr_cols_A * sizeof(float));
	float *h_B = (float*)malloc(nr_rows_B * nr_cols_B * sizeof(float));
	float *h_C = (float*)malloc(nr_rows_C * nr_cols_C * sizeof(float));

	float *d_A, *d_B, *d_C;
	cudaMalloc(&d_A, nr_rows_A * nr_cols_A * sizeof(float));
	cudaMalloc(&d_B, nr_rows_B * nr_cols_B * sizeof(float));
	cudaMalloc(&d_C, nr_rows_C * nr_cols_C * sizeof(float));

	cudaMemcpy(d_A, h_A, nr_cols_A * nr_cols_A * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(d_B, h_B, nr_cols_B * nr_cols_B * sizeof(float), cudaMemcpyHostToDevice);

	GPU_fill_rand(d_A, nr_rows_A, nr_cols_A);
	GPU_fill_rand(d_B, nr_rows_B, nr_cols_B);

	cudaMemcpy(h_A, d_A, nr_rows_A * nr_cols_A * sizeof(float), cudaMemcpyDeviceToHost);
	cudaMemcpy(h_B, d_B, nr_rows_B * nr_cols_B * sizeof(float), cudaMemcpyDeviceToHost);

	cout << "A = " << endl;
	print_matrix(h_A, nr_rows_A, nr_cols_A);
	cout << "B = " << endl;
	print_matrix(h_B, nr_rows_B, nr_cols_B);

	gpu_blas_matix_mul(d_A, d_B, d_C, nr_rows_A, nr_cols_A, nr_cols_B);

	cudaMemcpy(h_C, d_C, nr_rows_C * nr_cols_C * sizeof(float), cudaMemcpyDeviceToHost);
	cout << "C = " << endl;
	print_matrix(h_C, nr_rows_C, nr_cols_C);

	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);

	free(h_A);
	free(h_B);
	free(h_C);

	return 0;
}
