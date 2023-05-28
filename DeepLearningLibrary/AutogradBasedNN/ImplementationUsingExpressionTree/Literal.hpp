#ifndef LITERAL
#define LITERAL
#include "Expression.hpp"

class Literal : public Expression {
	double value;
public:
	// TO DO: replace value=0 with randomly generated one(i.e. normal from -1 to 1)
	Literal() : Expression(nullptr, nullptr), value(0) {}
	Literal(double value) : Expression(nullptr, nullptr), value(value) {}

	double eval() const { return value; }
	Expression* clone() const { return new Literal(*this); }
};

#endif