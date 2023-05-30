#include <vector>
#include <fstream>
#include <chrono>
#include <iostream>

// this is needed because mnist data is backwards...idk
int reverseInt(int i);

void MNISTReadTrainingImages(std::vector<std::vector<double>>& training_x);
void MNISTReadTrainingLabels(std::vector<double>& training_y);

void drawDigit(const std::vector<double>& pixelValues);

void readFile(const char* name, std::vector<std::vector<double>>& x, std::vector<double>& y, size_t numSamples);
void MNISTReadText();

// reading the text file is 90 seconds slower
// not needed anywhere, just for my information
void benchmarkPerformance();