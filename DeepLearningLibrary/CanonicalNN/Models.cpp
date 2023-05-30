#include <initializer_list>
#include <cstring>
#include <random>
#include <algorithm>
#include <iterator>
#include "Models.hpp"
#include "Layers.hpp"
#include "Utils.hpp"
#include "Cost.hpp"

Sequential::Sequential(std::initializer_list<Dense> list) : layers(list) {}

std::vector<double> Sequential::feedForward(std::vector<double> trainingInput) {
	for (size_t i = 0; i < layers.size(); i++) {
		trainingInput = layers[i].calculateOutput(trainingInput);
	}
	return trainingInput;
}

double Sequential::calculateCost(const std::vector<std::vector<double>>& trainingData, const std::vector<std::vector<double>>& labels) {
	double res = 0;
	for (size_t i = 0; i < trainingData.size(); i++) {
		res += cost::MSE(feedForward(trainingData[i]), labels[i]);
	}
	return res / trainingData.size();
}

unsigned Sequential::predict(const std::vector<double>& trainingInput) {
	std::vector<double> outputs = feedForward(trainingInput);
	double maxValue = outputs[0];
	size_t maxIndex = 0;
	/*for (size_t i = 0; i < outputs.size(); i++) {
		std::cout << outputs[i] << " ";
	}
	std::cout << std::endl;*/
	for (size_t i = 1; i < outputs.size(); i++) {
		if (maxValue < outputs[i]) {
			maxValue = outputs[i];
			maxIndex = i;
		}
	}
	return maxIndex;
}

unsigned Sequential::calculateAccuracy(const std::vector<std::vector<double>>& trainingData, const std::vector<std::vector<double>>& labels) {
	unsigned res = 0;
	for (size_t i = 0; i < trainingData.size(); i++) {
		if (labels[i][predict(trainingData[i])] == 1) res++;
	}
	return res;
}

std::vector<std::vector<std::vector<double>>> Sequential::miniBatchSplit(const std::vector<std::vector<double>>& trainingData, unsigned miniBatchSize) {
	// init rng
	std::random_device rd;
	std::mt19937 g(rd());
	g.seed(18291);

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

void Sequential::backprop(const std::vector<double>& trainingInput, const std::vector<double>& labels) {
	
	std::vector<double> predictions = feedForward(trainingInput);

	// a - y(x) = d(MSE)/da - this will change for different cost functions
	layers[layers.size() - 1].setError(utils::subtract(predictions, labels));
	layers[layers.size() - 1].computeGradients(layers[layers.size() - 2].getActivatedOutput());

	for (int i = layers.size() - 1; i >= 0; i--) {
		std::vector<double> error = layers[i].computePreviousError();
		layers[i - 1].setError(error);
		layers[i].computeGradients(layers[i - 1].getActivatedOutput());
	}
}

void Sequential::gradientDescent(const std::vector<std::vector<double>>& trainingData, const std::vector<std::vector<double>>& labels, double learningRate, unsigned batchSize) {
	// split into batches
	//std::vector<std::vector<std::vector<double>>> batches = miniBatchSplit(trainingData, batchSize);
	//for (auto batch : batches) {
	//	// calculate gradients for a single example
	//	for (size_t i = 0; i < batch.size(); i++) {
	//		// backprop and find gradients
	//		backprop(batch[i], labels[i]);
	//		for (Dense& d : layers) {
	//			// adjust weights and biases
	//			d.updateParameters(batch.size(), learningRate);
	//		}
	//	}
	//}
	for (size_t i = 0; i < trainingData.size(); i++) {
		// backprop and find gradients
		backprop(trainingData[i], labels[i]);
		for (Dense& d : layers) {
			// adjust weights and biases
			d.updateParameters(trainingData.size(), learningRate);
		}
	}
}

void Sequential::train(const std::vector<std::vector<double>>& trainingData, const std::vector<std::vector<double>>& labels, unsigned epochs, double learningRate, unsigned batchSize, const std::vector<double>& answers) {
	// labels are specified by user
	// maybe add sparse loss to fix that and onehot encode it automatically

	// checks
	if (trainingData.size() != labels.size()) throw std::invalid_argument("Invalid number of (data, labels)");
	if (!trainingData.size()) throw std::invalid_argument("No data is not allowed");

	// layer initialization
	layers[0].initializeParams(trainingData[0].size());
	for (size_t i = 1; i < layers.size(); i++) {
		layers[i].initializeParams(layers[i - 1].getNodesOut());
	}

	//for (size_t i = 0; i < 1; i++) {
	//	std::vector<std::vector<double>> lw = layers[i].getWeights();
	//	std::vector<double> lb = layers[i].getBiases();

	//	/*for (size_t r = 0; r < lw.size(); r++) {
	//		for (size_t c = 0; c < lw[0].size(); c++) {
	//			std::cout << lw[r][c] << " ";
	//		}
	//		std::cout << std::endl;
	//	}
	//	std::cout << std::endl;*/

	//	for (size_t j = 0; j < lb.size(); j++) {
	//		std::cout << lb[j] << " ";
	//	}
	//	std::cout << std::endl;
	//}
	
	// main training loop
	for (unsigned epoch = 1; epoch <= epochs; epoch++) {
		std::cout << "-----------------------------------------------" << std::endl;
		std::cout << "Epoch: " << epoch << std::endl;

		// train the network
		gradientDescent(trainingData, labels, learningRate, batchSize);

		// evaluate cost
		std::cout << "Cost: " << calculateCost(trainingData, labels) << std::endl;

		// evaluate accuracy
		std::cout << "Accuracy: " << calculateAccuracy(trainingData, labels) /* * 100.0 / trainingData.size()*/ << std::endl;

		/*for (size_t i = 0; i < 50; i++) {
			std::vector<double> pred = feedForward(trainingData[i]);
			for (size_t j = 0; j < pred.size(); j++) {
				std::cout << pred[j] << ' ';
			}
			std::cout << answers[i] << ' ' << labels[i][predict(trainingData[i])] << ' ' << labels[i][answers[i]] << std::endl;
		}*/
		std::cout << "-----------------------------------------------" << std::endl;

		// TO DO: add comparison with numerical gradient for testing purposes
	}
}