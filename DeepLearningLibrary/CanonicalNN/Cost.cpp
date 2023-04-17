#include <vector>
#include "Cost.hpp"
#include "Utils.hpp"

double cost::MSE(const std::vector<double>& results, const std::vector<double>& expected) {
	double length = utils::normal(utils::subtract(expected, results));
	return length * length / 2;
}