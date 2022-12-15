//#include <xmmintrin.h>
//#include <cstdio>
//#include <cstdlib>
//#include <iostream>
//#include <ctime>
//
////все сделать на putty pscp
////-03 уровень комп. график время
//// 
////
//
//static const int N = 2048;
//static const int M = 10;
//
//#define  num(row,col)  ((row)*N + (col) )
//
//using namespace std;
//
//
//void matr_print(float* invMatrixA) {
//	for (int i = 0; i < N; ++i) {
//		for (int j = 0; j < N; ++j) {
//			//cout << << " ";
//			cout << invMatrixA[i * N + j] << "\t";
//		}
//		cout << endl;
//	}
//	cout << endl;
//}
//
//
//void mul_matr(float* M1, float* M2, float* matRes) {
//	float* M3 = new float[N * N];
//	int size = N * N;
//
//	for (size_t i = 0; i < size; i++){
//		M3[i] = 0;
//	}
//
//	for (size_t i = 0; i < N; i++){
//		for (size_t k = 0; k < N; k++){
//			for (size_t j = 0; j < N; j++){
//				M3[i * N + j] += M1[i * N + k] * M2[k * N + j];
//			}
//		}
//	}
//
//	for (int i = 0; i < size; ++i) {
//		matRes[i] = M3[i];
//	}
//
//	delete[]M3;
//}
//
//
//void sub_matr(float* mat1, float* mat2, float* matRes) {
//	int size = N * N;
//	for (int i = 0; i < size; ++i) {
//		matRes[i] = mat1[i] - mat2[i];
//	}
//}
//
//
//void sum_matr(float* mat1, float* mat2, float* matRes) {
//	int size = N * N;
//	for (int i = 0; i < size; ++i) {
//		matRes[i] = mat1[i] + mat2[i];
//	}
//}
//
//
//void GenerateMatrixI(float* matrixI) {
//	for (int i = 0; i < N * N; i++) {
//		if ((i - i / N * N) == i / N) {
//			matrixI[i] = 1;
//		}
//		else {
//			matrixI[i] = 0;
//		}
//	}
//}
//
//
//void GenerateMatrixAT(float* matrixA, float* matrixAT) {
//	int size = N * N;
//	for (int i = 0; i < size; i++) {
//		int column = i - i / N * N;
//		int string = i / N;
//		matrixAT[i] = matrixA[column * N + string];
//	}
//}
//
//
//float maxl(float* matrixA) {
//	float maxSum = 0;
//
//	for (int column = 0; column < N; column++) {
//		float sumString = 0;
//		int shiftColumn = column * N;
//		for (int string = 0; string < N; string++) {
//			sumString += matrixA[shiftColumn + string];
//		}
//		if (sumString > maxSum) {
//			maxSum = sumString;
//		}
//	}
//
//	return maxSum;
//}
//
//
//void GenerateMatrixB(float* matrixA, float* matrixB) {
//	float* matrixAT = new float[N * N];
//	GenerateMatrixAT(matrixA, matrixAT);
//
//	float AL = maxl(matrixA);
//	float AU = maxl(matrixAT);
//	float U_L= 1/ (AU * AL);
//	
//	int size = N * N;
//	for (int i = 0; i < size; i++) {
//		matrixB[i] = matrixAT[i] * U_L;
//	}
//	delete[]matrixAT;
//}
//
//
//void GenerateMatrixR(float* matrixI, float* matrixA, float* matrixB, float* matrixR) {
//	mul_matr(matrixB, matrixA, matrixR);
//	sub_matr(matrixI, matrixR, matrixR);
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
//void geometric_progression(float* matrixB, float* matrixR, float* invMatrixA) {
//	float* matrixRpower = new float[N * N];
//	CopyMatrix(matrixR, matrixRpower);
//
//	sum_matr(invMatrixA, matrixR, invMatrixA);
//	for (int i = 0; i < M; i++) {
//		mul_matr(matrixRpower, matrixR, matrixRpower);
//		sum_matr(invMatrixA, matrixRpower, invMatrixA);
//	}
//	mul_matr(invMatrixA, matrixB, invMatrixA);
//	delete[]matrixRpower;
//}
//
//
//
//void inverse_mat(float* matrixA, float* invMatrixA) {
//	float* matrixB = new float[N * N];
//	float* matrixR = new float[N * N];
//	GenerateMatrixI(invMatrixA);
//	GenerateMatrixB(matrixA , matrixB);
//	GenerateMatrixR(invMatrixA, matrixA, matrixB, matrixR);
//	geometric_progression(matrixB, matrixR, invMatrixA);
//
//	delete[]matrixB;
//	delete[]matrixR;
//}
//
//
//void setMatrixRND(float* matrix) {
//	int size = N * N;
//	for (int i = 0; i < size; i++) {
//		matrix[i] = rand() * 0.0001;
//	}
//}
//
//
//void GenerateMatrix(float* matrix) {
//	int size = N * N;
//	for (int i = 0; i < size; i++) {
//		matrix[i] = i + 1;
//	}
//}
//
//
//void setNulltMatrix(float* matrix) {
//	int size = N * N;
//	for (int i = 0; i < size; i++) {
//		matrix[i] = 0;
//	}
//}
//
//
//int main(int argc, char** argv) {
//	srand(time(0));
//	clock_t start = clock();
//
//	float* matrixA = new float[N * N];
//	//setMatrixRND(matrixA);
//	GenerateMatrix(matrixA);
//
//	//matr_print(matrixA);
//
//	float* invMatrixA = new float[N * N];
//	inverse_mat(matrixA, invMatrixA);
//	//matr_print(invMatrixA);
//
//	std::cout << (float)(clock() - start) / CLOCKS_PER_SEC << endl;
//
//	delete[]matrixA;
//	delete[]invMatrixA;
//	return 0;
//}
#include <xmmintrin.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>

static const int N = 2048;
static const int M = 10;

#define  num(row,col)  ((row)*N + (col) )

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


void GenerateMatrixI(float* matrixI) {
	for (int i = 0; i < N * N; i++) {
		if ((i - i / N * N) == i / N) {
			matrixI[i] = 1;
		}
		else {
			matrixI[i] = 0;
		}
	}
}


void GenerateMatrixAT(float* matrixA, float* matrixAT) {
	int size = N * N;
	for (int i = 0; i < size; i++) {
		int column = i - i / N * N;
		int string = i / N;
		matrixAT[i] = matrixA[column * N + string];
	}
}


float maxl(float* matrixA) {
	float maxSum = 0;

	for (int column = 0; column < N; column++) {
		float sumString = 0;
		int shiftColumn = column * N;
		for (int string = 0; string < N; string++) {
			sumString += matrixA[shiftColumn + string];
		}
		if (sumString > maxSum) {
			maxSum = sumString;
		}
	}

	return maxSum;
}


void GenerateMatrixB(float* matrixA, float* matrixB) {
	float* matrixAT = new float[N * N];
	GenerateMatrixAT(matrixA, matrixAT);

	float AL = maxl(matrixA);
	float AU = maxl(matrixAT);
	float U_L = 1 / (AU * AL);

	int size = N * N;
	for (int i = 0; i < size; i++) {
		matrixB[i] = matrixAT[i] * U_L;
	}
	delete[]matrixAT;
}


void GenerateMatrixR(float* matrixI, float* matrixA, float* matrixB, float* matrixR) {
	mul_matr(matrixB, matrixA, matrixR);
	sub_matr(matrixI, matrixR, matrixR);
}


void CopyMatrix(float* IN, float* OUT) {
	int size = N * N;
	for (int i = 0; i < size; i++) {
		OUT[i] = IN[i];
	}
}


void geometric_progression(float* matrixB, float* matrixR, float* invMatrixA) {
	float* matrixRpower = new float[N * N];
	CopyMatrix(matrixR, matrixRpower);

	sum_matr(invMatrixA, matrixR, invMatrixA);
	for (int i = 0; i < M; i++) {
		mul_matr(matrixRpower, matrixR, matrixRpower);
		sum_matr(invMatrixA, matrixRpower, invMatrixA);
	}
	mul_matr(invMatrixA, matrixB, invMatrixA);
	delete[]matrixRpower;
}



void inverse_mat(float* matrixA, float* invMatrixA) {
	float* matrixB = new float[N * N];
	float* matrixR = new float[N * N];
	GenerateMatrixI(invMatrixA);
	GenerateMatrixB(matrixA, matrixB);
	GenerateMatrixR(invMatrixA, matrixA, matrixB, matrixR);
	geometric_progression(matrixB, matrixR, invMatrixA);

	delete[]matrixB;
	delete[]matrixR;
}


void setMatrixRND(float* matrix) {
	int size = N * N;
	for (int i = 0; i < size; i++) {
		matrix[i] = (int)(rand() * 0.00000001);
	}
}


void GenerateMatrix(float* matrix) {
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
	setMatrixRND(matrixA);
	//GenerateMatrix(matrixA);

	//matr_print(matrixA);

	float* invMatrixA = new float[N * N];
	inverse_mat(matrixA, invMatrixA);
	//matr_print(invMatrixA);

	std::cout << (float)(clock() - start) / CLOCKS_PER_SEC << endl;

	delete[]matrixA;
	delete[]invMatrixA;
	return 0;
}
