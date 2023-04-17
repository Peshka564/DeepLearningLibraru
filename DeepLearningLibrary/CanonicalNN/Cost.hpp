#ifndef COST_HPP
#define COST_HPP

#include "Utils.hpp"

namespace cost {
	// Mean Squared Error - C = (sum over examples(|y(x) - a|) / 2n
	double MSE(const std::vector<double>& results, const std::vector<double>& expected);
}

#endif // !COST_HPP