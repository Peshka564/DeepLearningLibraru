#ifndef SIGMOID_EXPR
#define SIGMOID_EXPR
#include "Expression.hpp"
#include <cmath>

class Sigmoid : public Expression {
public:
	Sigmoid(Expression* left, Expression* right) : Expression(left, nullptr) {}

	double eval() const {
		return 1 / (1 + std::exp(-left->eval()));
	}

	Expression* clone() const {
		return new Sigmoid(*this);
	}
};

#endif