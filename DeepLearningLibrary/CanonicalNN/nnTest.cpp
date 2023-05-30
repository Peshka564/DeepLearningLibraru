#include <iostream>
#include <vector>
#include "Models.hpp"
#include "Layers.hpp"
#include "mnistReader.hpp"

//int main() {
//
//	Sequential model({
//		Dense(30),
//		Dense(10)
//	});
//
//	// maybe try a simpler network
//
//	model.train(training_x, labels, epochs, learningRate, batchSize, training_y);
//}

void testTrainingData(const std::vector<std::vector<double>>& training_x, const std::vector<double>& training_y, const std::vector<std::vector<double>>& labels) {
	for (size_t i = 0; i < 784; i++) std::cout << training_x[0][i] << " ";
	std::cout << std::endl;

	for (size_t i = 0; i < 20; i++) {
		drawDigit(training_x[i]);
		std::cout << training_y[i] << " ";
		for (size_t j = 0; j < 10; j++) {
			std::cout << labels[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

int main() {
	std::vector<std::vector<double>> training_x;
	std::vector<double> training_y;
	MNISTReadTrainingImages(training_x);
	MNISTReadTrainingLabels(training_y);

	// one hot encode
	std::vector<std::vector<double>> labels;
	for (size_t i = 0; i < training_y.size(); i++) {
		std::vector<double> temp(10, 0);
		temp[training_y[i]] = 1;
		labels.push_back(temp);
	}

	//testTrainingData(training_x, training_y, labels);
	Sequential model({ Dense(30), Dense(10) });
	
	const double learningRate = 3.0;
	const unsigned epochs = 100;
	model.train(training_x, labels, epochs, learningRate, training_x.size(), training_y);
}