//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <vector>
//#include <string>
//#include "Models.hpp"
//#include "Layers.hpp"
//
//
//void readFile(const char* name, std::vector<std::vector<double>>& x, std::vector<double>& y) {
//
//}
//
//int main() {
//	//// receive with pointers
//	std::ifstream file("mnist_testing.txt");
//	
//	std::vector<std::vector<double>> testing_x(10000, std::vector<double>(784));
//	std::vector<double> testing_y(10000);
//
//	size_t i = 0;
//	while (file.peek() != EOF) {
//		for (size_t j = 0; j < 784; j++) {
//			file >> testing_x[i][j];
//		}
//		file >> testing_y[i];
//		i++;
//	}
//
//	std::vector<std::vector<double>> training_x(10000, std::vector<double>(784));
//	std::vector<double> training_y(10000);
//
//	size_t i = 0;
//	while (file.peek() != EOF) {
//		for (size_t j = 0; j < 784; j++) {
//			file >> testing_x[i][j];
//		}
//		file >> testing_y[i];
//		i++;
//	}
//
//	//Sequential model({
//	//	Dense(30),
//	//	Dense(10)
//	//});
//	//int i = 0;
//	//std::string str;
//	//while (std::getline(file, str)) {
//	//	std::stringstream ss(str);
//	//	if (i % 2 == 0) {
//	//		for (size_t j = 0; j < 784; j++) {
//	//			ss >> testing_x[i / 2][j];
//	//			//std::cout << testing_x[i / 2][j] << " ";
//	//		}
//	//		//std::cout << std::endl;
//	//	}
//	//	else {
//	//		ss >> testing_y[i / 2 + 1];
//	//		//std::cout << testing_y[i / 2 + 1] << std::endl;
//	//	}
//	//	i++;
//	//}
//
//	for (const double& d : testing_y) {
//		std::cout << d << " ";
//	}
//	std::cout << std::endl;
//	std::cout << "Done" << std::endl;
//}