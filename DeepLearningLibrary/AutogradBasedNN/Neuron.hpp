#ifndef NEURON
#define NEURON

#include <vector>
#include "scalarEngine/engine.hpp"

class Neuron {
public:
	// All of these are necessary to keep l-values in memory
	// so that backprop is successful
	std::vector<Value> weights;
	std::vector<Value> inputs;
	std::vector<Value> weightedOutputs;
	Value activatedOutput;
	Value bias;
public:
	Neuron(size_t);
	Value activate(std::vector<Value>&);
};

#endif // NEURON