#include <xmmintrin.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cblas.h>

static const int N = 2048;
static const int M = 10;

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


void mul_matr(float* M1, float* M2, float* matRes) {
	float* M3 = new float[N * N];
	int size = N * N;

	for (size_t i = 0; i < size; i++) {
		M3[i] = 0;
	}

	for (size_t i = 0; i < N; i++) {
		for (size_t k = 0; k < N; k++) {
			for (size_t j = 0; j < N; j++) {
				M3[i * N + j] += M1[i * N + k] * M2[k * N + j];
			}
		}
	}

	for (int i = 0; i < size; ++i) {
		matRes[i] = M3[i];
	}

	delete[]M3;
}


void sub_matr(float* mat1, float* mat2, float* matRes) {
	int size = N * N;
	for (int i = 0; i < size; ++i) {
		matRes[i] = mat1[i] - mat2[i];
	}
}


void sum_matr(float* mat1, float* mat2, float* matRes) {
	int size = N * N;
	for (int i = 0; i < size; ++i) {
		matRes[i] = mat1[i] + mat2[i];
	}
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


void CreateMatB(float* I,float* A, float* B) {
	float AL = MaxRowCount(A, N);
	float AU = MaxColumnCount(A, N);
	float U_L = 1 / (AU * AL);

	cblas_sgemm(CblasRowMajor, CblasTrans, CblasNoTrans, 
				N, N, N, U_L, I, N, A, N, 0.0, B, N);
}


void CreateMatR(float* I, float* A, float* B, float* R) {
	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
				N, N, N, 1.0, B, N, A, N, 0.0, R, N);
	cblas_saxpy(N, -1.0, R, 1, I, 1);
}


void CopyMatrix(float* IN, float* OUT) {
	int size = N * N;
	for (int i = 0; i < size; i++) {
		OUT[i] = IN[i];
	}
}


void geometric_progression(	float* B, 
							float* R, 
							float* invMatrixA) {

	float* Rn = new float[N * N];
	CopyMatrix(R, Rn);

	for (size_t i = 0; i < M; i++) {
		//SumMatrix(result, Rn, result, N);
		//Rn = MultiplicateMatrix(Rn, R, N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
					N, N, N, 1.0, I, N, R, N, 1.0, I, N);
	}
	//result = MultiplicateMatrix(result, B, N);
	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
				N, N, N, 1.0, I, N, B, N, 0.0, I, N);

	//sum_matr(invMatrixA, matrixR, invMatrixA);
	//for (int i = 0; i < M; i++) {
	//	mul_matr(matrixRpower, matrixR, matrixRpower);
	//	sum_matr(invMatrixA, matrixRpower, invMatrixA);
	//}
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
	for (int i = 0; i < size; i++) {
		matrix[i] = rand() * 0.0001;
	}
}


void CreateMat(float* matrix) {
	int size = N * N;
	for (int i = 0; i < size; i++) {
		matrix[i] = i + 1;
	}
}


void setNulltMatrix(float* matrix) {
	int size = N * N;
	for (int i = 0; i < size; i++) {
		matrix[i] = 0;
	}
}


int main(int argc, char** argv) {
	srand(time(0));
	clock_t start = clock();

	float* matrixA = new float[N * N];
	//setMatrixRND(matrixA);
	CreateMat(matrixA);

	//matr_print(matrixA);

	float* invMatrixA = new float[N * N];
	inverse_mat(matrixA, invMatrixA);
	//matr_print(invMatrixA);

	std::cout << (float)(clock() - start) / CLOCKS_PER_SEC << endl;

	delete[]matrixA;
	delete[]invMatrixA;
	return 0;
}
