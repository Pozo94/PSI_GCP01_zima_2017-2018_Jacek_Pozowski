#include "DeltaRule.h"

//konstruktor
DeltaRule::DeltaRule(double _learningRate) {
	delta = 0;
	numberOfWeights = PIXEL_AMOUNT;
	numberOfSets = LETTER_AMOUNT;
	learningRate = _learningRate;
	EMax = 0.1;
	error = 0;
	output = 0;
	weights = new double[numberOfWeights];

	for (int i = 0; i < PIXEL_AMOUNT; i++)
		this->weights[i] = getRandomDouble();//losowanie wag

	//wczytanie z pliku danych uczacych
	readTestData();
}

//losuje double'a z przedzialu <0;1>
double DeltaRule::getRandomDouble()
{
	double randValue = ((double)rand() / (double)RAND_MAX);
	return randValue;
}

//wczytanie danych ucz�cych z pliku
void DeltaRule::readTestData()
{
	fstream file;
	file.open("data_for_testing.txt");

	if (!file.good()) {
		cout << " I can't open the file" << endl;
		system("PAUSE");
		exit(0);
	}

	//wczytuj z pliku dopoki s� dane
	while (!file.eof())
		for (int i = 0; i < LETTER_AMOUNT; i++) { // i oznacza indeks litery
			for (int j = 0; j < PIXEL_AMOUNT; j++) // j oznacza ilosc bitow na dana litere
				file >> this->inputData[i][j]; //wczytywanie do tablicy z wej�ciami

			file >> this->expectedResults[i]; //wczytanie z pliku czy dana litera jest duza (1) lub mala (0)
		}

	file.close();
}

//funkcja aktywacji - funkcja sigmoidalna
double DeltaRule::activationFunction(double sum) {
	//Wspolczynnik beta = 1.0
	return (1 / (1 + exp(-1.0 * sum)));
}

//pochodna funkcji aktywcji
double DeltaRule::derivativeActivationFunction(double sum)
{
	return (1.0*exp(-1.0*sum)) / (pow(exp(-1.0*sum) + 1, 2));
}

//zwraca sume danego wejscia
double DeltaRule::getSum(int letter[], double * weights)
{
	double sum = 0.0;
	for (int i = 0; i < numberOfWeights; i++)
		sum += letter[i] * weights[i];
	return sum;
}

//funkcja uczaca
void DeltaRule::learn() {
	cout << endl << "DELTARULE LEARNING" << endl;

	bool acceptableError = false; //zmienna, stwierdzajaca czy blad jest mozliwy do zaakceptowania

	int epoch = 0; //numer epoki

				 

	do {
		epoch++; // zwiekszenie numeru epoki
		error = 0.0; //zerowanie glownego bledu w celu sprawdzenia bledow podczas jednej iteracji
		for (int i = 0; i < numberOfSets; i++) {

			//wynik otrzymany
			output = activationFunction(getSum(inputData[i], weights));

			//obliczanie roznicy pomiedzy wynikiem oczekiwanym a wynikiem otrzymanym
			delta = expectedResults[i] - output;

			//aktualizowanie wag
			for (int j = 0; j < numberOfWeights; j++)
				weights[j] += learningRate * delta*inputData[i][j] * derivativeActivationFunction(getSum(inputData[i], weights));

			//aktualizowanie bledu glownego
			error += delta * delta;
		}
		error /= 2;

		//porownywanie bledu z progiem
		if (error > EMax)
			acceptableError = false;
		else
			acceptableError = true;

	} while (!acceptableError);

	cout << "Epoki: " << epoch << endl;
	cout << "MSE: " << error << endl;
	
}



//funkcja testujaca
void DeltaRule::test()
{
	cout << "Test: " << endl;
	for (int i = 0; i < numberOfSets; i++) {
		cout << "Litera " << setTestLetters[i] << " - ";
		if (activationFunction(getSum(setTest[i], weights)) > 0.5) {
			cout << "Duza";
		}
		else {
			cout << "Mala";
		}
		cout << endl;
	}
}
