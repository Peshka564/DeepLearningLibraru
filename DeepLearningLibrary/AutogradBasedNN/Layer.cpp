#include "Layer.hpp"

Layer::Layer(size_t nodesIn, size_t nodesOut) {
	for (size_t i = 0; i < nodesOut; i++) nodes.push_back(Neuron(nodesIn));
}

std::vector<Value> Layer::feedForward(std::vector<Value>& input) {
	std::vector<Value> output(nodes.size());
	for (size_t i = 0; i < nodes.size(); i++) output[i] = nodes[i].activate(input);
	return output;
}

std::vector<Value> Layer::parameters() {
	std::vector<Value> params;
	for (size_t i = 0; i < nodes.size(); i++) {
		std::vector<Value> temp = nodes[i].parameters();
		params.insert(params.end(), temp.begin(), temp.end());
	}
	return params;
}