#include <initializer_list>
#include <cstring>
#include "Models.hpp"
#include "Layers.hpp"
#include "Utils.hpp"
#include "Cost.hpp"

Sequential::Sequential(std::initializer_list<Dense> list) : layers(list) {};

std::vector<double> Sequential::feedForward(std::vector<double> trainingInput) {
	for (size_t i = 0; i < layers.size(); i++) {
		trainingInput = layers[i].calculateOutput(trainingInput);
	}
	return trainingInput;
}

double Sequential::calculateCost(const std::vector<std::vector<double>>& trainingData, const std::vector<std::vector<bool>>& labels) {
	double res = 0;
	for (size_t i = 0; i < trainingData.size(); i++) {
		//!!
		std::vector<double> goodLabels(labels[i].begin(), labels[i].end());
		res += cost::MSE(feedForward(trainingData[i]), goodLabels);
	}
	return res / trainingData.size();
}

// 10 outputs representing each digit guess - {0, 1}
std::vector<bool> Sequential::oneHotEncode(double label) {
	std::vector<bool> ohe(10, 0);
	for (double i = 0; i < 10; i++) {
		if (i == label) ohe[i] = 1;
	}
	return ohe;
}

void Sequential::backprop(const std::vector<double>& trainingInput, const std::vector<bool>& labels) {
	// feedForward is the reason why training input is double and not ushort
	std::vector<double> predictions = feedForward(trainingInput);
	// a - y(x) = d(MSE)/da
	layers[layers.size() - 1].setError(utils::subtract(predictions, trainingInput));
	//layers[layers.size() - 1].computeGradients(predictions);
	for (int i = layers.size() - 1; i >= 0; i--) {
		if (i) {
			layers[i].computeGradients(layers[(size_t)i - 1].getActivatedOutput());
			std::vector<double> error = layers[i].computePreviousError();
			layers[(size_t)i - 1].setError(error);
		}
		else {
			layers[i].computeGradients(trainingInput);
			// custom compute gradient - just use training input
			// im gonna add input layer and stop at the layer before it
		}
	}
}

void Sequential::gradientDescent(const std::vector<std::vector<double>>& trainingData, const std::vector<std::vector<bool>>& labels, double learningRate) {
	// split into batches
	// calculate gradients for a single example
	for (size_t i = 0; i < trainingData.size(); i++) {
		// backprop and find gradients
		backprop(trainingData[i], labels[i]);
		for (Dense& d : layers) {
			// instead of trainingData.size() use miniBatchData.size()
			// adjust weights and biases
			d.updateParameters(trainingData.size(), learningRate);
		}
	}
}

void Sequential::train(const std::vector<std::vector<double>>& trainingData, const std::vector<double>& answers, unsigned epochs, double learningRate) {
	std::vector<std::vector<bool>> labels;
	for (size_t i = 0; i < answers.size(); i++) {
		labels[i] = oneHotEncode(answers[i]);
	}

	// check for empty training data
	layers[0].initializeParams(trainingData[0].size());

	for (size_t i = 1; i < layers.size(); i++) {
		layers[i].initializeParams(layers[i - 1].getNodesOut());
	}

	for (unsigned epoch = 1; epoch <= epochs; epoch++) {
		std::cout << "Epoch: " << epoch << std::endl;
		gradientDescent(trainingData, labels, learningRate);
		std::cout << "Cost: " << calculateCost(trainingData, labels) << std::endl;
	}
}