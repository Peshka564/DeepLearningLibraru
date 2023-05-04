#include <stdexcept>
#include "MLP.hpp"

MultiLayerPerceptron::MultiLayerPerceptron(size_t inputNodes, const std::vector<size_t>& outputNodes) : layers(outputNodes.size()), intermediate(outputNodes.size() + 1) {
	if (!outputNodes.size()) throw std::invalid_argument("Empty input to MLP");

	layers[0] = Layer(inputNodes, outputNodes[0]);
	for (size_t i = 1; i < outputNodes.size(); i++) {
		layers[i] = Layer(outputNodes[i - 1], outputNodes[i]);
	}
}

std::vector<Value> MultiLayerPerceptron::feedForward(std::vector<Value> input) {
	intermediate[0] = input;
	for (size_t i = 0; i < layers.size(); i++) {
		intermediate[i + 1] = layers[i].feedForward(intermediate[i]);
	}
	return intermediate[intermediate.size() - 1];
}