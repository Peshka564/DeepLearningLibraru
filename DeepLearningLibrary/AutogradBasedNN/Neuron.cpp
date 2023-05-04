#include <stdexcept>
#include "Neuron.hpp"
#include "../CanonicalNN/Utils.hpp"

Neuron::Neuron(size_t nodesIn) : bias(utils::normalDistr()), activatedOutput(0), weightedOutput(0) {
	for (size_t i = 0; i < nodesIn; i++) weights.push_back(Value(utils::normalDistr()));
}

Value Neuron::activate(std::vector<Value>& x) {
	if (x.size() != weights.size()) throw std::invalid_argument("Wrong input dimension");

	for (size_t i = 0; i < x.size(); i++) {
		inputs.push_back(weights[i] * x[i]);
		weightedOutput = weightedOutput + inputs[i];
	}
	activatedOutput = sigmoid(weightedOutput);
	return activatedOutput;
}