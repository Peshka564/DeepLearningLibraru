#ifndef MODELS_HPP
#define MODELS_HPP

#include <iostream>
#include <initializer_list>
#include "Layers.hpp"

class Sequential {
private:
	//unsigned miniBatchSize;
	std::vector<Dense> layers;

	// ff for a single training input
	std::vector<double> feedForward(std::vector<double>);
	// maybe specified by user
	std::vector<bool> oneHotEncode(double);
	void backprop(const std::vector<double>&, const std::vector<bool>&);
	void gradientDescent(const std::vector<std::vector<double>>&, const std::vector<std::vector<bool>>&, double);
	double calculateCost(const std::vector<std::vector<double>>&, const std::vector<std::vector<bool>>&);
	std::vector<std::vector<double>> miniBatchSplit(const std::vector<double>&, size_t);
public:
	Sequential(std::initializer_list<Dense> list);
	// ushort for 0-255 for pixels and 0-9 for labels
	void train(const std::vector<std::vector<double>>&, const std::vector<double>&, unsigned, double);
	// compile, fit, predict, export
};

#endif // !MODELS_HPP