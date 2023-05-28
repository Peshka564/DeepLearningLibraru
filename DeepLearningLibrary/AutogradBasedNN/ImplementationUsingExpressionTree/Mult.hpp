#ifndef MULT_EXPR
#define MULT_EXPR
#include "Expression.hpp"

class Mult : public Expression {
public:
	Mult(Expression* left, Expression* right) : Expression(left, right) {}

	double eval() const {
		return left->eval() * right->eval();
	}

	Expression* clone() const {
		return new Mult(*this);
	}
};

#endif