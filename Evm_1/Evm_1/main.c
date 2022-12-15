#include <stdio.h>
#include <stdlib.h>


double exponential_function(double power_num) {
	double sum = 1;
	double behind = 1;
	for (double i = 1; i < 3500000000; i++) {
		behind = behind * power_num / i;
		sum += behind;
	}

	return sum;
}


int main(int argc, char **argv){
	if (argc == 1) {
		printf("Enter the number\n");
		return 1;
	}

	double input = atof(argv[1]);
	printf("%.10f\n", exponential_function(input));

	return 0;
}