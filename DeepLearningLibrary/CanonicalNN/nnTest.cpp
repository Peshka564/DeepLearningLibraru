//#include <iostream>
//#include <fstream>
//#include <vector>
//#include "Models.hpp"
//#include "Layers.hpp"
//
//void readFile(const char* name, std::vector<std::vector<double>>& x, std::vector<double>& y, size_t numSamples) {
//	std::ifstream file(name);
//	if (!file) throw std::exception();
//
//	size_t i = 0;
//	while (i < numSamples) {
//		for (size_t j = 0; j < 784; j++) {
//			file >> x[i][j];
//		}
//		file >> y[i];
//		i++;
//	}
//
//	file.close();
//}
//
//int main() {
//	const size_t numSamples = 10000;
//	const unsigned epochs = 100;
//	const double learningRate = 0.1;
//	const unsigned batchSize = 10000;
//
//	std::vector<std::vector<double>> training_x(numSamples, std::vector<double>(784));
//	std::vector<double> training_y(numSamples);
//	readFile("./CanonicalNN/mnist_training.txt", training_x, training_y, numSamples);
//
//	/*std::vector<std::vector<double>> testing_x(numSamples, std::vector<double>(784));
//	std::vector<double> testing_y(numSamples);
//	readFile("mnist_testing.txt", testing_x, testing_y, numSamples);*/
//
//	Sequential model({
//		Dense(30),
//		Dense(10)
//	});
//
//	model.train(training_x, training_y, epochs, learningRate, batchSize);
//}