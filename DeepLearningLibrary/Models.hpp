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
	// maybe specified by user
	std::vector<bool> oneHotEncode(int);
	void backprop(const std::vector<double>&, const std::vector<bool>&);
	void gradientDescent(const std::vector<std::vector<double>>&, const std::vector<std::vector<bool>>&, double, unsigned);
	double calculateCost(const std::vector<std::vector<double>>&, const std::vector<std::vector<bool>>&);
	std::vector<std::vector<std::vector<double>>> miniBatchSplit(const std::vector<std::vector<double>>&, unsigned);
public:
	Sequential(std::initializer_list<Dense> list);
	// ushort for 0-255 for pixels and 0-9 for labels
	void train(const std::vector<std::vector<double>>&, const std::vector<int>&, unsigned, double, unsigned);
	// compile, fit, predict, export
};

#endif // !MODELS_HPP