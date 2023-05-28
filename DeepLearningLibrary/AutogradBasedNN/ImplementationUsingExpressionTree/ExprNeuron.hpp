#ifndef NEURON_EXPR
#define NEURON_EXPR
#include "Expression.hpp"

class ExprNeuron {
private:
	// TO DO: use smart pointers and vectors
	Expression* output;
	Expression** weights;
	size_t nodesIn;
	Expression* bias;
public:
	ExprNeuron(size_t nodesIn);
	Expression* activate(Expression** input);
	~ExprNeuron();
};

#endif