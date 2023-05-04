#include "Layer.hpp"

Layer::Layer(size_t nodesIn, size_t nodesOut) {
	for (size_t i = 0; i < nodesOut; i++) nodes.push_back(std::move(Neuron(nodesIn)));
}

std::vector<Value> Layer::feedForward(std::vector<Value>& input) {
	std::vector<Value> output;
	for (size_t i = 0; i < nodes.size(); i++) output.push_back(nodes[i].activate(input));
	return output;
}