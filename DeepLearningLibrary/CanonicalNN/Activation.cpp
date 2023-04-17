#include <cmath>
#include "Activation.hpp"

double activation::sigmoid(double input) {
	return 1 / (1 + std::exp(-input));
}

double activation::sigmoidPrime(double input) {
	double y = std::exp(-input);
	return y / ((1 + y) * (1 + y));
}