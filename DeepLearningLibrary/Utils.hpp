// tensors/ np arrays
// wrappers

#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
//#include "Vector.hpp"

namespace utils {
	// dot product
	double dotProduct(const std::vector<double>&, const std::vector<double>&);
	// vector length
	double normal(const std::vector<double>&);
	// hadamard product
	std::vector<double> multiply(const std::vector<double>&, const std::vector<double>&);
	// add vectors
	std::vector<double> add(const std::vector<double>&, const std::vector<double>&);
	// subtract vectors
	std::vector<double> subtract(const std::vector<double>&, const std::vector<double>&);
	// matrix multiplication
	std::vector<std::vector<double>> matmul(const std::vector<std::vector<double>>&, const std::vector<std::vector<double>>&);
	std::vector<double> matmul(const std::vector<std::vector<double>>&, const std::vector<double>&);
	double matmul(const std::vector<double>&, const std::vector<double>&);
	// transpose
	std::vector<std::vector<double>> transpose(const std::vector<std::vector<double>>&);
}

#endif // !UTILS_HPP