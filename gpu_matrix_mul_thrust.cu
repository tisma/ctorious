#include <iostream>
#include <cstdlib>
#include <ctime>
#include <curand.h>
#include <cublas_v2.h>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>

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

void print_matrix(thrust::device_vector<float>& A) {
	for (int i = 0; i < A.size(); i++) {
		cout << A[i] << ' ';
	}
	cout << endl;
}

int main() {
	int nr_rows_A = 3, nr_cols_A = 3, nr_rows_B = 3, nr_cols_B = 3, nr_rows_C = 3, nr_cols_C = 3;

	thrust::device_vector<float> d_A(nr_rows_A * nr_cols_A);
	thrust::device_vector<float> d_B(nr_rows_B * nr_cols_B);
	thrust::device_vector<float> d_C(nr_rows_C * nr_cols_C);

	GPU_fill_rand(thrust::raw_pointer_cast(&d_A[0]), nr_rows_A, nr_cols_A);
	GPU_fill_rand(thrust::raw_pointer_cast(&d_B[0]), nr_rows_B, nr_cols_B);

	cout << "A = " << endl;
	print_matrix(d_A);
	cout << "B = " << endl;
	print_matrix(d_B);

	gpu_blas_matix_mul(thrust::raw_pointer_cast(&d_A[0]), 
					   thrust::raw_pointer_cast(&d_B[0]), 
					   thrust::raw_pointer_cast(&d_C[0]), 
					   nr_rows_A, nr_cols_A, nr_cols_B);

	cout << "C = " << endl;
	print_matrix(d_C);

	return 0;
}
