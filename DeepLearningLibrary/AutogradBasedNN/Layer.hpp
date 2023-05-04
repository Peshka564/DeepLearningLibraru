#ifndef LAYER
#define LAYER
#include <vector>
#include "Neuron.hpp"

class Layer {
	std::vector<Neuron> nodes;
public:
	Layer(size_t, size_t);
	std::vector<Value> feedForward(std::vector<Value>&);
};

#endif // LAYER_WRAPPER