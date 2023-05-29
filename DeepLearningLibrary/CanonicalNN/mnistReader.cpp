#include "mnistReader.hpp"

// this is needed because mnist data is backwards...idk
int reverseInt(int i)
{
	unsigned char c1, c2, c3, c4;

	c1 = i & 255;
	c2 = (i >> 8) & 255;
	c3 = (i >> 16) & 255;
	c4 = (i >> 24) & 255;

	return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}

void MNISTReadTrainingImages(std::vector<std::vector<double>>& training_x) {
	std::ifstream fin("./CanonicalNN/train-images.bin", std::ios::binary);
	int magicNumber, numberOfImages, rows, cols;
	fin.read((char*)&magicNumber, sizeof(magicNumber));
	fin.read((char*)&numberOfImages, sizeof(numberOfImages));
	fin.read((char*)&rows, sizeof(rows));
	fin.read((char*)&cols, sizeof(cols));

	magicNumber = reverseInt(magicNumber);
	numberOfImages = reverseInt(numberOfImages);
	rows = reverseInt(rows);
	cols = reverseInt(cols);

	std::cout << "Training_x magicNumber: " << magicNumber << std::endl;
	std::cout << "Training_x number of images: " << numberOfImages << std::endl;
	std::cout << "Training_x dim rows: " << rows << std::endl;
	std::cout << "Training_y dim cols: " << cols << std::endl;

	for (int i = 0; i < numberOfImages; i++) {
		training_x.push_back(std::vector<double>(rows * cols));
		for (int j = 0; j < rows * cols; j++) {
			fin.read((char*)&training_x[i][j], sizeof(training_x[i][j]));
		}
	}

	fin.close();
}

void MNISTReadTrainingLabels(std::vector<double>& training_y) {
	std::ifstream fin("./CanonicalNN/train-labels.bin", std::ios::binary);
	int magicNumber, numberOfItems;
	fin.read((char*)&magicNumber, sizeof(magicNumber));
	fin.read((char*)&numberOfItems, sizeof(numberOfItems));

	magicNumber = reverseInt(magicNumber);
	numberOfItems = reverseInt(numberOfItems);

	std::cout << "Training_y magicNumber: " << magicNumber << std::endl;
	std::cout << "Training_y number of labels: " << numberOfItems << std::endl;

	for (int i = 0; i < numberOfItems; i++) {
		double temp;
		fin.read((char*)&temp, sizeof(temp));
		training_y.push_back(temp);
	}

	fin.close();
}

void readFile(const char* name, std::vector<std::vector<double>>& x, std::vector<double>& y, size_t numSamples) {
	std::ifstream file(name);
	if (!file) throw std::exception();

	size_t i = 0;
	while (i < numSamples) {
		for (size_t j = 0; j < 784; j++) {
			file >> x[i][j];
		}
		file >> y[i];
		i++;
	}

	file.close();
}

void MNISTReadText() {
	const size_t numSamples = 10000;
	const unsigned epochs = 100;
	const double learningRate = 3.0;
	const unsigned batchSize = 10000;

	std::vector<std::vector<double>> training_x(50000, std::vector<double>(784));
	std::vector<double> training_y(50000);
	readFile("./CanonicalNN/mnist_training.txt", training_x, training_y, 50000);

	std::vector<std::vector<double>> labels(numSamples, std::vector<double>(10));
	for (size_t i = 0; i < numSamples; i++) {
		labels[i][(int)training_y[i]] = 1;
	}
	std::vector<std::vector<double>> testing_x(10000, std::vector<double>(784));
	std::vector<double> testing_y(10000);

	readFile("./CanonicalNN/mnist_testing.txt", testing_x, testing_y, 10000);
}

// reading the text file is 90 seconds slower
// not needed anywhere, just for my information
void benchmarkPerformance() {
	std::vector<std::vector<double>> training_x;
	std::vector<double> training_y;
	auto t1 = std::chrono::high_resolution_clock::now();
	MNISTReadTrainingImages(training_x);
	MNISTReadTrainingLabels(training_y);
	auto t2 = std::chrono::high_resolution_clock::now();
	auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
	std::cout << "Binary file time for 60k images in ms: " << ms_int.count() << std::endl;

	std::vector<std::vector<double>> training_x1(50000, std::vector<double>(784));
	std::vector<double> training_y1(50000);
	auto p1 = std::chrono::high_resolution_clock::now();
	readFile("./CanonicalNN/mnist_training.txt", training_x1, training_y1, 50000);
	auto p2 = std::chrono::high_resolution_clock::now();
	auto mp_int = std::chrono::duration_cast<std::chrono::milliseconds>(p2 - p1);
	std::cout << "Text file time for 50k images in ms: " << mp_int.count() << std::endl;
}