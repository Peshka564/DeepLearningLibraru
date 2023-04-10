#include <initializer_list>
#include <cstring>
#include <random>
#include <algorithm>
#include <iterator>
#include "Models.hpp"
#include "Layers.hpp"
#include "Utils.hpp"
#include "Cost.hpp"

Sequential::Sequential(std::initializer_list<Dense> list) : layers(list) {
	if (!layers.size()) throw std::exception();
};

std::vector<double> Sequential::feedForward(std::vector<double> trainingInput) {
	for (size_t i = 0; i < layers.size(); i++) {
		trainingInput = layers[i].calculateOutput(trainingInput);
	}
	return trainingInput;
}

double Sequential::calculateCost(const std::vector<std::vector<double>>& trainingData, const std::vector<std::vector<bool>>& labels) {
	double res = 0;
	for (size_t i = 0; i < trainingData.size(); i++) {
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

std::vector<std::vector<std::vector<double>>> Sequential::miniBatchSplit(const std::vector<std::vector<double>>& trainingData, unsigned miniBatchSize) {
	// init rng
	std::random_device rd;
	std::mt19937 g(rd());
	g.seed(5);

	// shuffle data
	std::vector<std::vector<double>> shuffledData = trainingData;
	std::shuffle(shuffledData.begin(), shuffledData.end(), g);

	// split into batches
	std::vector<std::vector<std::vector<double>>> batches;
	std::vector<std::vector<double>> temp;
	size_t k = 0;
	while (k < shuffledData.size()) {
		for (size_t i = k; i < k + miniBatchSize && i < shuffledData.size(); i++) {
			temp.push_back(shuffledData[i]);
		}
		batches.push_back(temp);
		k += miniBatchSize;
	}
	return batches;
}

void Sequential::backprop(const std::vector<double>& trainingInput, const std::vector<bool>& labels) {
	// feedForward is the reason why training input is double and not ushort
	std::vector<double> predictions = feedForward(trainingInput);
	// a - y(x) = d(MSE)/da - this will change for different cost functions
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

void Sequential::gradientDescent(const std::vector<std::vector<double>>& trainingData, const std::vector<std::vector<bool>>& labels, double learningRate, unsigned batchSize) {
	// split into batches
	std::vector<std::vector<std::vector<double>>> batches = miniBatchSplit(trainingData, batchSize);
	for (auto batch : batches) {
		// calculate gradients for a single example
		for (size_t i = 0; i < batch.size(); i++) {
			// backprop and find gradients
			backprop(batch[i], labels[i]);
			for (Dense& d : layers) {
				// adjust weights and biases
				d.updateParameters(batch.size(), learningRate);
			}
		}
	}
}

void Sequential::train(const std::vector<std::vector<double>>& trainingData, const std::vector<double>& answers, unsigned epochs, double learningRate, unsigned batchSize) {
	// generate labels - maybe specified by user
	std::vector<std::vector<bool>> labels(answers.size(), std::vector<bool>(10));
	for (size_t i = 0; i < answers.size(); i++) {
		labels[i] = oneHotEncode(answers[i]);
	}

	std::cout << "Passed labeling" << std::endl;

	// >check for empty training data
	layers[0].initializeParams(trainingData[0].size());
	for (size_t i = 1; i < layers.size(); i++) {
		layers[i].initializeParams(layers[i - 1].getNodesOut());
	}
	std::cout << "Passed init" << std::endl;

	for (unsigned epoch = 1; epoch <= epochs; epoch++) {
		std::cout << "-----------------------------------------------" << std::endl;
		std::cout << "Epoch: " << epoch << std::endl;
		// train the network
		gradientDescent(trainingData, labels, learningRate, batchSize);
		// evaluate cost
		std::cout << "Cost: " << calculateCost(trainingData, labels) << std::endl;
		// evaluate accuracy
		int accuracy = 0;
		for (size_t i = 0; i < trainingData.size(); i++) {
			std::vector<double> predictions = feedForward(trainingData[i]);
			double maxVal = predictions[0];
			int maxIndex = 0;
			for (size_t j = 0; j < predictions.size(); j++) {
				if (predictions[j] > maxVal) {
					maxVal = predictions[j];
					maxIndex = j;
				}
			}
			if (labels[i][maxIndex] == 1) accuracy++;
		}
		std::cout << "Accuracy: " << accuracy * 100.0 / trainingData.size() << std::endl;
		std::cout << "-----------------------------------------------" << std::endl;
		// add comparison with numerical gradient
	}
}