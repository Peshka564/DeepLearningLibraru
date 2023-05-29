#ifndef MODELS_HPP
#define MODELS_HPP

#include <iostream>
#include <initializer_list>
#include "Layers.hpp"

class Sequential {
private:
	std::vector<Dense> layers;

	// ff for a single training input
	std::vector<double> feedForward(std::vector<double>);
	void backprop(const std::vector<double>&, const std::vector<double>&);
	void gradientDescent(const std::vector<std::vector<double>>&, const std::vector<std::vector<double>>&, double, unsigned);
	double calculateCost(const std::vector<std::vector<double>>&, const std::vector<std::vector<double>>&);
	unsigned calculateAccuracy(const std::vector<std::vector<double>>&, const std::vector<std::vector<double>>&);
	std::vector<std::vector<std::vector<double>>> miniBatchSplit(const std::vector<std::vector<double>>&, unsigned);
	void computeNumericalGradients(const std::vector<std::vector<double>>&);
public:
	Sequential(std::initializer_list<Dense> list);
	void train(const std::vector<std::vector<double>>&, const std::vector<std::vector<double>>&, unsigned, double, unsigned, const std::vector<double>&);
	unsigned predict(const std::vector<double>&);
	// compile, fit, predict, save
};

#endif // !MODELS_HPP