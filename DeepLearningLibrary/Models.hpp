#ifndef MODELS_HPP
#define MODELS_HPP

#include <iostream>
#include <initializer_list>
#include "Layers.hpp"

class Sequential {
private:
	//unsigned miniBatchSize;
	std::vector<Dense> layers;

	// single training input
	std::vector<double> feedForward(std::vector<double>);
	std::vector<bool> oneHotEncode(unsigned short);
	void backprop(const std::vector<double>&, const std::vector<bool>&);
	void gradientDescent(const std::vector<std::vector<double>>&, const std::vector<std::vector<bool>>&, double);
	double calculateCost(const std::vector<std::vector<double>>&, const std::vector<std::vector<bool>>&);
public:
	Sequential(std::initializer_list<Dense> list);
	// ushort for 0-255 for pixels and 0-9 for labels
	void train(const std::vector<std::vector<double>>&, const std::vector<unsigned short>&, unsigned, double);
	// again, no need
	//~Sequential();
	// compile, fit, predict, export
};

#endif // !MODELS_HPP