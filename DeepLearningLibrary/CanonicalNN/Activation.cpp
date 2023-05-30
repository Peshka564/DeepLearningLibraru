#include <cmath>
#include "Activation.hpp"

double activation::sigmoid(double input) {
	return 1.0 / (1.0 + std::exp(-input));
}

double activation::sigmoidPrime(double input) {
	return activation::sigmoid(input) * (1 - activation::sigmoid(input));
}