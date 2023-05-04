#include <stdexcept>
#include "Neuron.hpp"
#include "../CanonicalNN/Utils.hpp"

Neuron::Neuron(size_t nodesIn) : bias(utils::normalDistr()), activatedOutput(0) {
	if (!nodesIn) throw std::invalid_argument("Empty weights");
	for (size_t i = 0; i < nodesIn; i++) weights.push_back(Value(utils::normalDistr()));
}

Value Neuron::activate(std::vector<Value>& x) {
	if (x.size() != weights.size()) throw std::invalid_argument("Wrong input dimension");
	
	weightedOutputs.push_back(std::move(weights[0] * x[0]));

	for (size_t i = 1; i < x.size(); i++) {
		inputs.push_back(std::move(weights[i] * x[i]));
		weightedOutputs.push_back(std::move(weightedOutputs[i - 1] + inputs[i - 1]));
	}
	activatedOutput = sigmoid(weightedOutputs[weightedOutputs.size() - 1]);
	return activatedOutput;
}