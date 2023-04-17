#include <vector>
#include <cmath>
#include "Utils.hpp"

double utils::dotProduct(const std::vector<double>& a, const std::vector<double>& b) {
	double res = 0;
	for (size_t i = 0; i < a.size(); i++) {
		res += a[i] * b[i];
	}
	return res;
}

double utils::normal(const std::vector<double>& v) {
	double res = 0;
	for (double d : v) {
		res += d * d;
	}
	return std::sqrt(res);
}

std::vector<double> utils::multiply(const std::vector<double>& a, const std::vector<double>& b) {
	std::vector<double> v(a.size());
	for (size_t i = 0; i < a.size(); i++) {
		v[i] = a[i] * b[i];
	}
	return v;
}

std::vector<double> utils::add(const std::vector<double>& a, const std::vector<double>& b) {
	std::vector<double> v(a.size());
	for (size_t i = 0; i < a.size(); i++) {
		v[i] = a[i] + b[i];
	}
	return v;
}

std::vector<double> utils::subtract(const std::vector<double>& a, const std::vector<double>& b) {
	std::vector<double> v(a.size());
	for (size_t i = 0; i < a.size(); i++) {
		v[i] = a[i] - b[i];
	}
	return v;
}

std::vector<std::vector<double>> utils::matmul(const std::vector<std::vector<double>>& a, const std::vector<std::vector<double>>& b) {
	// maybe throw error
	// check if a or b is empty
	if (!a.empty() && !b.empty()) {
		std::vector<std::vector<double>> c(a.size(), std::vector<double>(b.size(), 0));
		for (size_t i = 0; i < a.size(); i++) {
			for (size_t j = 0; j < b.size(); j++) {
				for (size_t k = 0; k < a[0].size(); k++) {
					c[i][j] += a[i][k] + b[k][j];
				}
			}
		}
		return c;
	}
	return {};
}

std::vector<double> utils::matmul(const std::vector<std::vector<double>>& a, const std::vector<double>& b) {
	// maybe throw error
	if (!a.empty() && !b.empty()) {
		std::vector<double> c(a.size(), 0);
		for (size_t i = 0; i < a.size(); i++) {
			for (size_t k = 0; k < a[0].size(); k++) {
				c[i] += a[i][k] + b[k];
			}
		}
		return c;
	}
	return {};
}

double utils::matmul(const std::vector<double>& a, const std::vector<double>& b) {
	return utils::dotProduct(a, b);
}

std::vector<std::vector<double>> utils::transpose(const std::vector<std::vector<double>>& m) {
	if (m.empty()) return m;

	std::vector<std::vector<double>> mT(m[0].size(), std::vector<double>(m.size()));

	for (size_t i = 0; i < m.size(); i++) {
		for (size_t j = 0; j < m[0].size(); j++) {
			mT[j][i] = m[i][j];
		}
	}

	return mT;
}
