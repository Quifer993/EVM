//#include <iostream>
//#include <ctime>
//#include <cstdlib>
//#include <float.h>
//#include<immintrin.h>
//#include<xmmintrin.h>
//
//const int M = 10;
//const int N = 2048;
//using namespace std;
//
//void showMatrix(float* matrix, size_t size) {
//	size_t i, j;
//	for (i = 0; i < size; ++i) {
//		for (j = 0; j < size; ++j) {
//			cout << matrix[i * size + j] << " ";
//		}
//		cout << endl;
//	}
//	cout << "\n\n\n";
//}
//
//void SubtractMatrix(float* M1, float* M2, float* result, int N) {
//	for (size_t i = 0; i < N; i++) {
//		size_t shift = i * N;
//		for (size_t j = 0; j < N; j += 16) {
//			_mm256_storeu_ps(result + shift + j + 0, _mm256_sub_ps(_mm256_loadu_ps(M1 + shift + j + 0), _mm256_loadu_ps(M2 + shift + j + 0)));
//			_mm256_storeu_ps(result + shift + j + 8, _mm256_sub_ps(_mm256_loadu_ps(result + shift + j + 8), _mm256_loadu_ps(result + shift + j + 8)));
//		}
//	}
//}
//
//float* MultiplicateMatrix(float* M1, float* M2, int N) {
//	float* M3 = (float*)_mm_malloc(N * N * sizeof(float), 32);
//
//	for (size_t i = 0; i < N; ++i) {
//		float* shiftM3 = M3 + i * N;
//		for (size_t j = 0; j < N; j += 8) _mm256_storeu_ps(shiftM3 + j + 0, _mm256_setzero_ps());
//		for (size_t k = 0; k < N; ++k) {
//			const float* shiftM2 = M2 + k * N;
//			__m256 pos = _mm256_set1_ps(M1[i * N + k]);
//			for (size_t j = 0; j < N; j += 16) {
//				_mm256_storeu_ps(shiftM3 + j + 0, _mm256_fmadd_ps(pos, _mm256_loadu_ps(shiftM2 + j + 0), _mm256_loadu_ps(shiftM3 + j + 0)));
//				_mm256_storeu_ps(shiftM3 + j + 8, _mm256_fmadd_ps(pos, _mm256_loadu_ps(shiftM2 + j + 8), _mm256_loadu_ps(shiftM3 + j + 8)));
//			}
//		}
//	}
//	return M3;
//}
//
//void SumMatrix(float* M1, float* M2, float* result, int N) {
//	for (size_t i = 0; i < N; i++) {
//		size_t shift = i * N;
//		for (size_t j = 0; j < N; j += 16) {
//			_mm256_storeu_ps(result + shift + j + 0, _mm256_add_ps(_mm256_loadu_ps(result + shift + j + 0), _mm256_loadu_ps(result + shift + j + 0)));
//			_mm256_storeu_ps(result + shift + j + 8, _mm256_add_ps(_mm256_loadu_ps(result + shift + j + 8), _mm256_loadu_ps(result + shift + j + 8)));
//		}
//	}
//}
//
//float* GenerateMatrix(int N) {
//	float* A = (float*)_mm_malloc(N * N * sizeof(float), 32);
//	for (size_t i = 0; i < N; i++) {
//		for (size_t j = 0; j < N; j++) {
//			A[i * N + j] = rand() * 0.25;
//		}
//	}
//	return A;
//}
//
//float MaxLineCount(float* matrix, int N) {
//	float maximum = FLT_MIN;
//	for (size_t i = 0; i < N; i++) {
//		float temp = 0;
//		int row = i * N;
//		for (size_t j = 0; j < N; j++) {
//			temp += matrix[row + j];
//		}
//
//		if (temp > maximum) {
//			maximum = temp;
//		}
//	}
//	return maximum;
//}
//
//void TransposeMatrix(float* transpMatrix, float* matrix, int N) {
//	for (int i = 0; i < N; i += 4){
//		for (int j = 0; j < N; j += 4){
//			__m128 firstLine = _mm_load_ps(&matrix[i * N + j]);
//			__m128 secondLine = _mm_load_ps(&matrix[(i + 1) * N + j]);
//			__m128 thirdLine = _mm_load_ps(&matrix[(i + 2) * N + j]);
//			__m128 fourthLine = _mm_load_ps(&matrix[(i + 3) * N + j]);
//
//			_MM_TRANSPOSE4_PS(firstLine, secondLine, thirdLine, fourthLine);
//
//			_mm_store_ps(&transpMatrix[j * N + i], firstLine);
//			_mm_store_ps(&transpMatrix[(j + 1) * N + i], secondLine);
//			_mm_store_ps(&transpMatrix[(j + 2) * N + i], thirdLine);
//			_mm_store_ps(&transpMatrix[(j + 3) * N + i], fourthLine);
//		}
//	}
//}
//
//float* GenerateMatrixB(float* A, int N) {
//	float* B = (float*)_mm_malloc(N * N * sizeof(float), 32);
//	float* transposedA = (float*)_mm_malloc(N * N * sizeof(float), 16);
//	TransposeMatrix(transposedA, A, N);
//	//showMatrix(transposedA, N);
//	float maxRowCount = MaxLineCount(A, N);
//	float maxColumnCount = MaxLineCount(transposedA, N);
//	float divider = 1 / (maxRowCount * maxColumnCount);
//	for (size_t i = 0; i < N; i++) {
//		for (size_t j = 0; j < N; j++) {
//			B[i * N + j] = transposedA[i * N + j] * divider;
//		}
//	}
//	_mm_free(transposedA);
//	return B;
//}
//
//float* GenerateMatrixI(int N) {
//	float* I = (float*)_mm_malloc(N * N * sizeof(float), 32);
//	for (size_t i = 0; i < N; ++i) {
//		float* c = I + i * N;
//		for (size_t j = 0; j < N; j += 8) _mm256_storeu_ps(c + j, _mm256_setzero_ps());
//	}
//	for (size_t i = 0; i < N; i++) I[i * N + i] = 1;
//	return I;
//}
//
//float* GenerateMatrixR(float* A, float* I, float* B, int N) {
//	float* R = (float*)_mm_malloc(N * N * sizeof(float), 32);
//	//float* multed = (float*)_mm_malloc(N * N * sizeof(float), 32);
//	R = MultiplicateMatrix(B, A, N);
//	SubtractMatrix(I, R, R, N);
//	//_mm_free(multed);
//	return R;
//}
//
//
//void CopyMatrix(float* IN, float* OUT) {
//	int size = N * N;
//	for (int i = 0; i < size; i++) {
//		OUT[i] = IN[i];
//	}
//}
//
//
//float* GetInversedMatrix(float* A, int N, int M) {
//	float* I_Result = GenerateMatrixI(N);
//
//	float* B = GenerateMatrixB(A, N);
//	float* R = GenerateMatrixR(A, I_Result, B, N);
//	float* Rn = (float*)_mm_malloc(N * N * sizeof(float), 32);
//	CopyMatrix(R, Rn);
//	SumMatrix(I_Result, Rn, I_Result, N);
//	for (size_t i = 0; i < M; i++) {
//		Rn = MultiplicateMatrix(Rn, R, N);
//		SumMatrix(I_Result, Rn, I_Result, N);
//	}
//
//	I_Result = MultiplicateMatrix(I_Result, B, N);
//	_mm_free(B);
//	_mm_free(R);
//	_mm_free(Rn);
//	return I_Result;
//}
//
//int main() {
//	srand(time(0));
//	clock_t start = clock();
//
//	float* A = GenerateMatrix(N);
//	//showMatrix(A, N);
//	float* InversedA = GetInversedMatrix(A, N, M);
//	//showMatrix(InversedA, N);
//
//	std::cout << (float)(clock() - start) / CLOCKS_PER_SEC << endl;
//
//	_mm_free(A);
//	_mm_free(InversedA);
//	return 0;
//}
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <float.h>
#include<immintrin.h>
#include<xmmintrin.h>

const int M = 1000000;
const int N = 16;
using namespace std;

void showMatrix(float* matrix, size_t size) {
	size_t i, j;
	for (i = 0; i < size; ++i) {
		for (j = 0; j < size; ++j) {
			cout << matrix[i * size + j] << " ";
		}
		cout << endl;
	}
	cout << "\n\n\n";
}

void SubtractMatrix(float* M1, float* M2, float* result, int N) {
	for (size_t i = 0; i < N; i++) {
		size_t shift = i * N;
		for (size_t j = 0; j < N; j += 8) {
			_mm_storeu_ps(result + shift + j + 0, _mm_sub_ps(_mm_loadu_ps(M1 + shift + j + 0), _mm_loadu_ps(M2 + shift + j + 0)));
			_mm_storeu_ps(result + shift + j + 4, _mm_sub_ps(_mm_loadu_ps(M1 + shift + j + 4), _mm_loadu_ps(M2 + shift + j + 4)));
		}
	}
}

float* MultiplicateMatrix(float* M1, float* M2, int N) {
	float* M3 = (float*)_mm_malloc(N * N * sizeof(float), 32);

	for (size_t i = 0; i < N; ++i) {
		float* shiftM3 = M3 + i * N;
		for (size_t j = 0; j < N; j += 4) _mm_storeu_ps(shiftM3 + j + 0, _mm_setzero_ps());
		for (size_t k = 0; k < N; ++k) {
			const float* shiftM2 = M2 + k * N;
			__m128 pos = _mm_set1_ps(M1[i * N + k]);
			for (size_t j = 0; j < N; j += 8) {
				_mm_storeu_ps(shiftM3 + j + 0, _mm_add_ps(_mm_mul_ps(pos, _mm_loadu_ps(shiftM2 + j + 0)), _mm_loadu_ps(shiftM3 + j + 0)));
				//_mm_storeu_ps(shiftM3 + j + 0, _mm_fmadd_ps(pos, _mm_loadu_ps(shiftM2 + j + 0), _mm_loadu_ps(shiftM3 + j + 0)));
				_mm_storeu_ps(shiftM3 + j + 4, _mm_add_ps(_mm_mul_ps(pos, _mm_loadu_ps(shiftM2 + j + 4)), _mm_loadu_ps(shiftM3 + j + 4)));
				//_mm_storeu_ps(shiftM3 + j + 4, _mm_fmadd_ps(pos, _mm_loadu_ps(shiftM2 + j + 4), _mm_loadu_ps(shiftM3 + j + 4)));
			}
		}
	}
	return M3;
}

void SumMatrix(float* M1, float* M2, float* result, int N) {
	for (size_t i = 0; i < N; i++) {
		size_t shift = i * N;
		for (size_t j = 0; j < N; j += 8) {
			_mm_storeu_ps(result + shift + j + 0, _mm_add_ps(_mm_loadu_ps(M1 + shift + j + 0), _mm_loadu_ps(M2 + shift + j + 0)));
			_mm_storeu_ps(result + shift + j + 4, _mm_add_ps(_mm_loadu_ps(M1 + shift + j + 4), _mm_loadu_ps(M2 + shift + j + 4)));
		}
	}
}

float* GenerateMatrix(int N) {
	float* A = (float*)_mm_malloc(N * N * sizeof(float), 32);
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < N; j++) {
			A[i * N + j] = rand() * 0.0001;
		}
	}
	return A;
}

float MaxLineCount(float* matrix, int N) {
	float maximum = FLT_MIN;
	for (size_t i = 0; i < N; i++) {
		float temp = 0;
		int row = i * N;
		for (size_t j = 0; j < N; j++) {
			temp += matrix[row + j];
		}

		if (temp > maximum) {
			maximum = temp;
		}
	}
	return maximum;
}

void TransposeMatrix(float* transpMatrix, float* matrix, int N) {
	for (int i = 0; i < N; i += 4) {
		for (int j = 0; j < N; j += 4) {
			__m128 firstLine = _mm_load_ps(&matrix[i * N + j]);
			__m128 secondLine = _mm_load_ps(&matrix[(i + 1) * N + j]);
			__m128 thirdLine = _mm_load_ps(&matrix[(i + 2) * N + j]);
			__m128 fourthLine = _mm_load_ps(&matrix[(i + 3) * N + j]);

			_MM_TRANSPOSE4_PS(firstLine, secondLine, thirdLine, fourthLine);

			_mm_store_ps(&transpMatrix[j * N + i], firstLine);
			_mm_store_ps(&transpMatrix[(j + 1) * N + i], secondLine);
			_mm_store_ps(&transpMatrix[(j + 2) * N + i], thirdLine);
			_mm_store_ps(&transpMatrix[(j + 3) * N + i], fourthLine);
		}
	}
}

float* GenerateMatrixB(float* A, int N) {
	float* B = (float*)_mm_malloc(N * N * sizeof(float), 32);
	float* transposedA = (float*)_mm_malloc(N * N * sizeof(float), 8);
	TransposeMatrix(transposedA, A, N);
	float maxRowCount = MaxLineCount(A, N);
	float maxColumnCount = MaxLineCount(transposedA, N);
	float divider = 1 / (maxRowCount * maxColumnCount);
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < N; j++) {
			B[i * N + j] = transposedA[i * N + j] * divider;
		}
	}
	_mm_free(transposedA);
	return B;
}

float* GenerateMatrixI(int N) {
	float* I = (float*)_mm_malloc(N * N * sizeof(float), 32);
	for (size_t i = 0; i < N; ++i) {
		float* c = I + i * N;
		for (size_t j = 0; j < N; j += 4) _mm_storeu_ps(c + j, _mm_setzero_ps());
	}
	for (size_t i = 0; i < N; i++) I[i * N + i] = 1;
	return I;
}

float* GenerateMatrixR(float* A, float* I, float* B, int N) {
	float* R = MultiplicateMatrix(B, A, N);
	SubtractMatrix(I, R, R, N);
	return R;
}


void CopyMatrix(float* IN, float* OUT) {
	int size = N * N;
	for (int i = 0; i < size; i++) {
		OUT[i] = IN[i];
	}
}


float* GetInversedMatrix(float* A, int N, int M) {
	float* I_Result = GenerateMatrixI(N);
	float* B = GenerateMatrixB(A, N);
	float* R = GenerateMatrixR(A, I_Result, B, N);
	float* Rn = (float*)_mm_malloc(N * N * sizeof(float), 32);
	CopyMatrix(R, Rn);

	SumMatrix(I_Result, Rn, I_Result, N);
	for (size_t i = 0; i < M; i++) {
		float *g = Rn;
		Rn = MultiplicateMatrix(Rn, R, N);
		SumMatrix(I_Result, Rn, I_Result, N);
		_mm_free(g);
	}
	float* g = I_Result;
	I_Result = MultiplicateMatrix(I_Result, B, N);
	_mm_free(g);
	_mm_free(B);
	_mm_free(R);
	_mm_free(Rn);
	return I_Result;
}

int main() {
	srand(time(0));
	clock_t start = clock();

	float* A = GenerateMatrix(N);
	showMatrix(A, N);
	float* InversedA = GetInversedMatrix(A, N, M);
	showMatrix(InversedA, N);

	std::cout << (float)(clock() - start) / CLOCKS_PER_SEC << endl;

	_mm_free(A);
	_mm_free(InversedA);
	return 0;
}
