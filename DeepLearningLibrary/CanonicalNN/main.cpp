//#include <iostream>
//#include <fstream>
//#include <vector>
//#include "Models.hpp"
//#include "Layers.hpp"
//
//void readFile(const char* name, std::vector<std::vector<double>>& x, std::vector<int>& y, size_t numSamples) {
//	std::ifstream file(name);
//	if (!file) throw std::exception();
//
//	size_t i = 0;
//	while (i < numSamples && file.peek() != EOF) {
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
//	//std::vector<std::vector<double>> training_x(50000, std::vector<double>(784));
//	//std::vector<double> training_y(50000);
//	//readFile("mnist_training.txt", training_x, training_y);
//	std::vector<std::vector<double>> testing_x(numSamples, std::vector<double>(784));
//	std::vector<int> testing_y(numSamples);
//	readFile("mnist_testing.txt", testing_x, testing_y, numSamples);
//	std::cout << "Successful read" << std::endl;
//	Sequential model({
//		Dense(30),
//		Dense(10)
//	});
//	std::cout << "Passed constructor" << std::endl;
//	model.train(testing_x, testing_y, epochs, learningRate, batchSize);
//}