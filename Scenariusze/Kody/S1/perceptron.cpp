#include <stdlib.h>
#include <time.h>

#include "perceptron.h"



	
	Perceptron * Perceptron_create(unsigned inputs, double trainingRate)
	{
		unsigned i;
		
		srand(time(NULL));
		Perceptron *newOne = (Perceptron*)malloc(sizeof(Perceptron));
		newOne->inputs_ = inputs;
		
		newOne->trainingRate_ = trainingRate;
		newOne->weights_ = (double*)malloc(newOne->inputs_ * sizeof(double));

		for (i = 0; i < newOne->inputs_; i++) {
			newOne->weights_[i] = randValue();
		}
		newOne->threshold_ = 0.2;

		return newOne;
	}

	void learn(Perceptron *perceptron, const double inputs[], int expectedResult) {
		int result = getReasult(perceptron, inputs);
		if (result == expectedResult) {
			return;
		}
		changeWeight(perceptron, result, expectedResult, inputs);
	}

	int getReasult(const Perceptron *perceptron, const double inputs[]) {
		if (getValue(perceptron, inputs) >= perceptron->threshold_)
			return 1;
		else
			return 0;
	}

	const double *getWeight(const Perceptron *perceptron) {
		return perceptron->weights_;
	}

	double getValue(const Perceptron *perceptron, const double inputs[]) {
		unsigned i;
		double ans = 0;

		for (i = 0; i < perceptron->inputs_; i++) {
			ans += perceptron->weights_[i] * inputs[i];
		}
		return ans;
	}

	void setWeight(Perceptron *perceptron, const double *weights) {
		unsigned i;
		for (i = 0; i < perceptron->inputs_; i++) {
			perceptron->weights_[i] = weights[i];
		}
	}

	void changeWeight(Perceptron *perceptron, int actualResult, int desiredResult, const double inputs[]) {
		unsigned i;

		for (i = 0; i < perceptron->inputs_; i++) {
			perceptron->weights_[i] += perceptron->trainingRate_ * (desiredResult - actualResult)*inputs[i] ;
		}
		
	}

	double randValue() {
		double randValue = 0;
		randValue = (double)rand()/(RAND_MAX);
		
		return randValue;
	}

	
	