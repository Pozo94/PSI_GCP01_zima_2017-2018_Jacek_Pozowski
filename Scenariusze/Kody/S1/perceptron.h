

class Perceptron {
public:
	unsigned inputs_;
	double *weights_;
	double threshold_, trainingRate_;
};

Perceptron *Perceptron_create(unsigned inputs, double learnRate);
void learn(Perceptron *perceptron, const double inputs[], int expectedResult);
int getReasult(const Perceptron *perceptron, const double inputs[]);
const double *getWeight(const Perceptron *perceptron);
double getValue(const Perceptron *perceptron, const double inputs[]);
void setWeight(Perceptron *perceptron, const double *weights);
void changeWeight(Perceptron *perceptron, int actualResult, int desiredResult, const double inputs[]);
double randValue();
