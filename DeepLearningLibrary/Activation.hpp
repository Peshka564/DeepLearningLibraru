#ifndef ACTIVATION_HPP
#define ACTIVATION_HPP

#include <cmath>

namespace activation {
	// sgm(x) = 1 / (1 + e^(-x))
	double sigmoid(double input);
	double sigmoidPrime(double input);
}

#endif // !ACTIVATION_HPP