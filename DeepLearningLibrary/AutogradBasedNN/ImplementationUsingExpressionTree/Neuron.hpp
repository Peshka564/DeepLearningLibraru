#ifndef NEURON_EXPR
#define NEURON_EXPR
#include "Expression.hpp"
#include <vector>
#include <memory>

class Neuron {
private:
	std::vector<std::shared_ptr<Expression>> weights;
	std::unique_ptr<Expression> bias;
	std::unique_ptr<Expression> output;
	/*Expression* output;
	Expression** weights;
	Expression* bias;*/
public:
	Neuron(size_t nodesIn);
};

#endif