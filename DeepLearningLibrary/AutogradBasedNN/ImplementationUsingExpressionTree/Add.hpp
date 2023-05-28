#ifndef ADD_EXPR
#define ADD_EXPR
#include "Expression.hpp"

class Add : public Expression {
public:
	Add(Expression* left, Expression* right) : Expression(left, right) {}

	double eval() const {
		return left->eval() + right->eval();
	}

	Expression* clone() const {
		return new Add(*this);
	}
};

#endif