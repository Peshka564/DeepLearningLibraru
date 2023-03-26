#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Models.hpp"
#include "Layers.hpp"

void readFile(const char* name, std::vector<std::vector<double>>& x, std::vector<double>& y, size_t size) {
	std::ifstream file(name);
	if (!file) throw std::exception();

	size_t i = 0;
	while (i < size) {
		for (size_t j = 0; j < 784; j++) {
			file >> x[i][j];
		}
		file >> y[i];
		i++;
	}

	file.close();
}

int main() {
	//std::vector<std::vector<double>> training_x(50000, std::vector<double>(784));
	//std::vector<double> training_y(50000);
	//readFile("mnist_training.txt", training_x, training_y);
	std::vector<std::vector<double>> testing_x(10000, std::vector<double>(784));
	std::vector<double> testing_y(10000);
	readFile("mnist_testing.txt", testing_x, testing_y, 10000);
	std::cout << "Success" << std::endl;
	Sequential model({
		Dense(30),
		Dense(10)
	});
	model.train(testing_x, testing_y, 10, 0.001);
}