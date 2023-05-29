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

int main() {
	std::vector<std::vector<double>> training_x;
	MNISTReadTrainingImages(training_x);
}