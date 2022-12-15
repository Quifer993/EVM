#include <iostream>
#include <intrin.h>
#include <cmath>
#include <set>
#include <ctime>

void DirectFill(int* arr, int size){
	for (int i = 0; i < size - 1; ++i){
		arr[i] = i + 1;
	}
	arr[size - 1] = 0;
}


void ReversedFill(int* arr, int size){
	for (int i = size - 1; i > 0; --i){
		arr[i] = i - 1;
	}
	arr[0] = size - 1;
}


void RandomFill(int* arr, const int N){
	DirectFill(arr, N);
	for (int i = N - 1; i >= 1;--i){ //ְכדמנטעל װטרונא – ֹועסא
		int j = (rand() * rand()) % (i + 1);

		int tmp = arr[i];
		arr[i] = arr[j];
		arr[j] = tmp;
	}
	//for (int i = 0; i < N; i++) {
	//	std::cout << arr[i] + 1<< " ";
	//}
	std::cout << std::endl;
}

double CountTime(int* arr, int size){
	int k = 0;
	for (int i = 0; i < size; ++i)
	{
		k = arr[k];
	}
	if (k == 375) std::cout << "WOOOW!" << std::endl;

	uint64_t time = UINT64_MAX;
	for (int j = 0; j < 10; ++j)
	{
		k = 0;
		uint64_t start = __rdtsc();
		for (int i = 0; i < size; ++i){
			k = arr[k];

		}

		uint64_t end = __rdtsc();
		if (k == (578916))
			std::cout << "WOOOW!" << std::endl;
		if (end - start < time){
			time = end - start;
		}
	}
	return (double)(time) / size;
}


void bypass() {
	//256 - 1Kb
	//33554432 - 32Mb
	for (int N = 256; N < 5347488; N *= 1.2){
		std::cout /* << "Size: " */<< N * 4 << std::endl;
		int* arr = new int[N];
		double time;

		DirectFill(arr, N);
		time = CountTime(arr, N);
		std::cout << /*"Direct bypass: " << */ time /*<< " tacts"*/ <<  std::endl;

		ReversedFill(arr, N);
		time = CountTime(arr, N);
		std::cout << /* "Reverse bypass: " <<*/ time /* << " tacts" */ << std::endl;

		RandomFill(arr, N);
		time = CountTime(arr, N);
		std::cout <</* "Random bypass: " <<*/ time /* << " tacts" */ << std::endl;

		delete[] arr;
	}
	return;
}


int main(){
	srand(clock());
	bypass();
	return 0;
}
