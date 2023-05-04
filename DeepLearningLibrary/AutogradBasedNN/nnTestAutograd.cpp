#include <iostream>
#include <vector>
#include "./scalarEngine/engine.hpp"
#include "Layer.hpp"
#include "MLP.hpp"
#include "Neuron.hpp"

int main() {

	MultiLayerPerceptron model(3, { 4, 4, 1 });
	std::vector<std::vector<Value>> xs = { {2, 3, -1}, {3, -1, 0.5}, {0.5, 1, 1}, {1, 1, -1} };
	std::vector<Value> predictions;
	std::vector<Value> ys = { 1, -1, -1, 1 };
	for (size_t i = 0; i < xs.size(); i++) {
		for (auto& val : model.feedForward(xs[i])) {
			std::cout << val << std::endl;
			predictions.push_back(val);
		}
	}
	Value temp0 = ys[0] - predictions[0];
	Value temp1 = ys[1] - predictions[1];
	Value temp2 = ys[2] - predictions[2];
	Value temp3 = ys[3] - predictions[3];

	Value proxy0 = temp0 * temp0;
	Value proxy1 = temp1 * temp1;
	Value proxy2 = temp2 * temp2;
	Value proxy3 = temp3 * temp3;

	Value final1 = proxy0 + proxy1;
	Value final2 = proxy2 + proxy3;

	Value loss = final1 + final2;
	loss.backprop();
	std::cout << "---------------" << std::endl;
	std::cout << loss << std::endl;

	//Successful
	//Neuron sample(3);
	//std::vector<Value> x = { 1, 2, 0.5 };
	//Value output = sample.activate(x);
	//std::cout << "--------------" << std::endl;
	//std::cout << output << std::endl;
	//////std::cout << sample.activatedOutput << std::endl;

	//std::cout << sample.weightedOutputs[0] << std::endl;
	//std::cout << sample.weightedOutputs[1] << std::endl;
	//std::cout << sample.weightedOutputs[2] << std::endl;
	//std::cout << std::endl;
	//std::cout << sample.inputs[0] << std::endl;
	//std::cout << sample.inputs[1] << std::endl;
	//// trying to get backprop to work
	//output.backprop();

	// Successful
	//MultiLayerPerceptron model(3, { 1 });
	//std::vector<Value> x = { 1, -2, 0.5 };
	//model.feedForward(x)[0].backprop();

	// Successful
	/*Layer l(3, 1);
	std::vector<Value> x = { 1, -2, 0.5 };
	l.feedForward(x)[0].backprop();*/
}