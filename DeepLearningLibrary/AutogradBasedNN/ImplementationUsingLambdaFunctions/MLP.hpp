#ifndef MLP
#define MLP

#include <vector>
#include "Layer.hpp"
#include "scalarEngine/engine.hpp"

class MultiLayerPerceptron {
	std::vector<Layer> layers;
	std::vector<std::vector<Value>> intermediate;
public:
	MultiLayerPerceptron(size_t, const std::vector<size_t>&);
	std::vector<Value> feedForward(std::vector<Value>);
	std::vector<Value> parameters();
};

#endif // !MLP