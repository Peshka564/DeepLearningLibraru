#include <iostream>
#include <random>
#include <vector>
#include "Layers.hpp"
#include "Activation.hpp"
#include "Utils.hpp"

// maybe init here
Dense::Dense(size_t nodes) : nodesOut(nodes), nodesIn(0),
weights({}), biases({}), output({}), gradientWeights({}), gradientBiases({})
{};

// Initialize weights and biases(currently to zero)
void Dense::initializeParams(size_t nodes) {
	std::cout << nodes << ", " << nodesOut << std::endl;
	nodesIn = nodes;
	
	// generate random numbers from normal distribution
	std::random_device rd;
	std::mt19937 e2(rd());
	e2.seed(8923892);
	std::normal_distribution<> dist(0, 1);

	weights = std::vector<std::vector<double>>(nodesOut, std::vector<double>(nodes));
	for (size_t i = 0; i < weights.size(); i++) {
		for (size_t j = 0; j < weights[0].size(); j++) {
			weights[i][j] = dist(e2);
		}
	}
	biases = std::vector<double>(nodesOut);
	for (size_t i = 0; i < biases.size(); i++) {
		biases[i] = dist(e2);
	}
	output = std::vector<double>(nodesOut);

	// must be zeros
	gradientWeights = std::vector<std::vector<double>>(nodesOut, std::vector<double>(nodes, 0));
	gradientBiases = std::vector<double>(nodesOut, 0);
	gradientOutput = std::vector<double>(nodesOut);
}

size_t Dense::getNodesOut() const {
	return nodesOut;
}

// Weighted output
std::vector<double> Dense::calculateOutput(std::vector<double>& input) {
	for (size_t i = 0; i < nodesOut; i++) {
		output[i] = activation::sigmoid(utils::dotProduct(weights[i], input) + biases[i]);
	}
	return output;
}

std::vector<double> Dense::computePreviousError() {
	// Zk,l+1 = sum(j) Wkj*Ajl + Bkl
	// d(Zk,l+1) / d(Zj,l) = wkj*sigm'(Zj,l)
	// and d(C)/d(Zj,l) = sum(k) d(Zk,l+1) / d(Zj,l)*DELTAk,l+1
	// transpose because we sum Wkj over k
	return utils::matmul(utils::transpose(weights), gradientOutput);
}

void Dense::computeGradients(const std::vector<double>& prevOutput) {
	// z = a(l-1) * w + b
	// biases
	// dC / db = dC / dz * dz / db
	// dz / db = 1 => dC / db = dC / dz
	// weights
	// dC / dw = dC / dz * dz / dw
	// dz / dw = a(l-1) => dC / dw = dC / dz * a(l - 1)
	gradientBiases = gradientOutput;
	for (size_t i = 0; i < weights.size(); i++) {
		for (size_t j = 0; j < weights[0].size(); j++) {
			gradientWeights[i][j] = prevOutput[j] * gradientOutput[i];
		}
	}
}

void Dense::updateParameters(size_t numSamples, double learningRate) {
	// w = w - eta * gradient
	// average over all of them
	for (size_t i = 0; i < weights.size(); i++) {
		for (size_t j = 0; j < weights[0].size(); j++) {
			weights[i][j] -= learningRate * gradientWeights[i][j] / numSamples;
		}
	}
	for (size_t i = 0; i < biases.size(); i++) {
		biases[i] -= learningRate * gradientBiases[i] / numSamples;
	}
	// zero grad
	gradientWeights = std::vector<std::vector<double>>(nodesOut, std::vector<double>(nodesIn, 0));
	gradientBiases = std::vector<double>(nodesOut, 0);
}

std::vector<double> Dense::getActivatedOutput() {
	std::vector<double> activatedOutput(output.size());
	for (size_t i = 0; i < output.size(); i++) {
		activatedOutput[i] = activation::sigmoid(output[i]);
	}
	return activatedOutput;
}

void Dense::setError(const std::vector<double>& error) {
	// dC/dz = dC/da * da/dz = dC/da * sigmoid'(z)
	std::vector<double> activatedOutput(output.size());
	for (size_t i = 0; i < output.size(); i++) {
		activatedOutput[i] = activation::sigmoidPrime(output[i]);
	}
	gradientOutput = utils::multiply(activatedOutput, error);
}