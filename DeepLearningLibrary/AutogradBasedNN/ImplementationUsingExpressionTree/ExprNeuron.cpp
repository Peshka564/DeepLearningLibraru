#include <stdexcept>
#include "ExprNeuron.hpp"
#include "Literal.hpp"
#include "Mult.hpp"
#include "Add.hpp"
#include "Sigmoid.hpp"

ExprNeuron::ExprNeuron(size_t nodesIn) : nodesIn(nodesIn), bias(new Literal()) {
	if (!nodesIn) throw std::invalid_argument("Empty weights");
	weights = new Expression*[nodesIn];
	for (size_t i = 0; i < nodesIn; i++) weights[i] = new Literal();
	output = nullptr;
}

ExprNeuron::~ExprNeuron() {
	delete output;
	delete[] weights;
}

Expression* ExprNeuron::activate(Expression** input) {
	// check for equal size and size != 0 - for now assuming size is correct

	// I don't like this
	output = new Mult(input[0], weights[0]);
	for (size_t i = 1; i < nodesIn; i++) {
		Expression* multRes = new Mult(input[i], weights[i]);
		output = new Add(output, multRes);
	}
	output = new Add(output, bias);
	output = new Sigmoid(output);

	return output;
}