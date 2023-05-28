#include "Expression.hpp"

Expression* Expression::copyChildPointer(Expression* e) {
	if (e) return e->clone();
	return nullptr;
}

Expression::Expression(Expression* left, Expression* right) : left(copyChildPointer(left)), right(copyChildPointer(right)), grad(0) {}

Expression::Expression(const Expression& e) : left(copyChildPointer(e.left)), right(copyChildPointer(e.right)), grad(e.grad) {}

Expression& Expression::operator=(const Expression& e) {
	if (this != &e) {
		delete left;
		delete right;

		left = copyChildPointer(e.left);
		right = copyChildPointer(e.right);
		grad = e.grad;
	}
	return *this;
}

Expression::~Expression() {
	delete left;
	delete right;
}

Expression::Expression(Expression&& e) {
	left = e.left;
	right = e.right;
	grad = e.grad;

	e.left = nullptr;
	e.right = nullptr;
	e.grad = 0;
}

Expression& Expression::operator=(Expression&& e) {
	if (this != &e) {
		delete left;
		delete right;
		
		left = e.left;
		right = e.right;
		grad = e.grad;

		e.left = nullptr;
		e.right = nullptr;
		e.grad = 0;
	}
	return *this;
}