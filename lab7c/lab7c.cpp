#include<immintrin.h>
#include <xmmintrin.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cblas.h>

static const int N = 2;
static const int M = 1000000;

using namespace std;


void matr_print(float* invMatrixA) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			//cout << << " ";
			cout << invMatrixA[i * N + j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}


void setNulltMatrix(float* matrix) {
	int size = N * N;
	for (int i = 0; i < size; i++) 	matrix[i] = 0;
}


void CreateMatI(float* matrixI) {
	int size = N * N;
	for (int i = 0; i < size; i++) matrixI[i] = 0;
	for (size_t i = 0; i < size; i += N + 1) matrixI[i] = 1;
}


float MaxRowCount(float* A, const int N) {
	float* res = new float[N];
	for (int i = 0; i < N; i++) {
		res[i] = cblas_sasum(N, &A[i], N);
	}
	return res[cblas_isamax(N, res, 1)];
}

float MaxColumnCount(float* A, const int N) {
	float* res = new float[N];
	for (int i = 0; i < N; i++) {
		res[i] = cblas_sasum(N, &A[i * N], 1);
	}
	return res[cblas_isamax(N, res, 1)];
}


void CreateMatB(float* I, float* A, float* B) {
	float AL = MaxRowCount(A, N);
	float AU = MaxColumnCount(A, N);
	float U_L = 1 / (AU * AL);
	cblas_sgemm(CblasRowMajor, CblasTrans, CblasNoTrans,
		N, N, N, U_L, I, N, A, N, 0.0, B, N);
}


void CreateMatR(float* I, float* A, float* B, float* R) {
	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
		N, N, N, 1.0, B, N, A, N, 0.0, R, N);
	cblas_saxpy(N * N, -1.0, I, 1, R, 1);
	cblas_saxpy(N * N, -2.0, R, 1, R, 1);
}


void CopyMatrix(float* IN, float* OUT) {
	int size = N * N;
	for (int i = 0; i < size; i++) {
		OUT[i] = IN[i];
	}
}


void geometric_progression(float* B,
	float* R,
	float* invA) {

	float* Rn = new float[N * N];
	CopyMatrix(R, Rn);
	size_t size = N * N;
	cblas_saxpy(size, 1.0, Rn, 1, invA, 1);

	float* ret = new float[N * N];
	setNulltMatrix(ret);

	for (size_t i = 0; i < M; i++) {
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
			N, N, N, 1.0, Rn, N, R, N, 0, ret, N);
		cblas_saxpy(size, 1.0, ret, 1, invA, 1);
		setNulltMatrix(Rn);
		cblas_saxpy(size, 1.0, ret, 1, Rn, 1);
	}

	CopyMatrix(invA, ret);
	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
		N, N, N, 1.0, ret, N, B, N, 0, invA, N);

	delete[]ret;
	delete[]Rn;
}


void inverse_mat(float* matrixA, float* invMatrixA) {
	float* matrixB = new float[N * N];
	float* matrixR = new float[N * N];
	CreateMatI(invMatrixA);
	CreateMatB(invMatrixA, matrixA, matrixB);
	CreateMatR(invMatrixA, matrixA, matrixB, matrixR);
	geometric_progression(matrixB, matrixR, invMatrixA);

	delete[]matrixB;
	delete[]matrixR;
}


void setMatrixRND(float* matrix) {
	int size = N * N;
	for (int i = 0; i < size; i++) 	matrix[i] = rand() * 0.00000001;
}


void CreateMat(float* matrix) {
	int size = N * N;
	for (int i = 0; i < size; i++) 	matrix[i] = i + 1;
}


int main(int argc, char** argv) {
	srand(time(0));
	clock_t start = clock();

	float* matrixA = new float[N * N];
	//setMatrixRND(matrixA);
	CreateMat(matrixA);

	matr_print(matrixA);

	float* invMatrixA = new float[N * N];
	inverse_mat(matrixA, invMatrixA);
	matr_print(invMatrixA);

	std::cout << (float)(clock() - start) / CLOCKS_PER_SEC << endl;

	delete[]matrixA;
	delete[]invMatrixA;
	return 0;
}
