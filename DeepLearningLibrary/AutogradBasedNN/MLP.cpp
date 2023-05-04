#include <stdexcept>
#include "MLP.hpp"

MultiLayerPerceptron::MultiLayerPerceptron(size_t inputNodes, const std::vector<size_t>& outputNodes) {
	if (!outputNodes.size()) throw std::invalid_argument("Empty input to MLP");

	layers.push_back(std::move(Layer(inputNodes, outputNodes[0])));
	for (size_t i = 1; i < outputNodes.size(); i++) {
		layers.push_back(std::move(Layer(outputNodes[i - 1], outputNodes[i])));
	}
}

std::vector<Value> MultiLayerPerceptron::feedForward(std::vector<Value> input) {
	for (size_t i = 0; i < layers.size(); i++) {
		input = layers[i].feedForward(input);
	}
	return input;
}