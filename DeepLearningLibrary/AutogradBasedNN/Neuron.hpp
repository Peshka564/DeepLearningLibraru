#ifndef NEURON
#define NEURON

#include <vector>
#include "scalarEngine/engine.hpp"

class Neuron {
private:
	std::vector<Value> weights;
	std::vector<Value> inputs;
	Value weightedOutput;
	Value activatedOutput;
	Value bias;
public:
	Neuron(size_t);
	Value activate(std::vector<Value>&);
};

#endif // NEURON