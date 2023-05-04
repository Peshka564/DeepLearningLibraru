#ifndef MLP
#define MLP

#include <vector>
#include "Layer.hpp"

class MultiLayerPerceptron {
	std::vector<Layer> layers;
public:
	MultiLayerPerceptron(size_t, const std::vector<size_t>&);
	std::vector<Value> feedForward(std::vector<Value>);
};

#endif // !MLP