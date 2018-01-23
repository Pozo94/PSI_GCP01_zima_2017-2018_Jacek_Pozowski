#include <stdio.h>
#include "perceptron.h"

const int iteration =40, numberOfImputs = 2;
const double learnRate = 0.5;
void wait()
{
		while (true)
	{
		

	}
}
int main() {
	
	double case1[] = { 0, 0 };
	double case2[] = { 0, 1 };
	double case3[] = { 1, 0 };
	double case4[] = { 1, 1 };

	Perceptron *AndGate = Perceptron_create(numberOfImputs, learnRate);

	printf("Wartosc AND na wejsciu :\n");
	printf("[ 0 , 0 ]  -> %d\n", getReasult(AndGate, case1));
	printf("[ 0 , 1 ]  -> %d\n", getReasult(AndGate, case2));
	printf("[ 1 , 0 ]  -> %d\n", getReasult(AndGate, case3));
	printf("[ 1 , 1 ]  -> %d\n", getReasult(AndGate, case4));

	printf("\n Nauka... \n\n");

	for (int i = 0; i < iteration; i++) {
		printf("Epoka : %i \n", i + 1);
		learn(AndGate, case1, 0);
		printf("[ 0 , 0 ]  -> %d\n", getReasult(AndGate, case1));
		learn(AndGate, case2, 0);
		printf("[ 0 , 1 ]  -> %d\n", getReasult(AndGate, case2));
		learn(AndGate, case3, 0);
		printf("[ 1 , 0 ]  -> %d\n", getReasult(AndGate, case3));
		learn(AndGate, case4, 1);
		printf("[ 1 , 1 ]  -> %d\n", getReasult(AndGate, case4));
		printf("\n");
	}
	
	
	wait();
	return 0;
}
