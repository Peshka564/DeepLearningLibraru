#include <iostream>

class Expression {
public:
	Expression* left, * right;
	double grad;

	static Expression* copyChildPointer(Expression* e) {
		if (e) return e->clone();
		return nullptr;
	}

public:
	Expression(Expression* left, Expression* right) : left(copyChildPointer(left)), right(copyChildPointer(right)), grad(0) {}
	Expression(const Expression& e) : left(copyChildPointer(e.left)), right(copyChildPointer(e.right)), grad(e.grad) {}
	virtual double eval() const = 0;
	virtual Expression* clone() const = 0;
	virtual ~Expression() {
		delete left;
		delete right;
	}
};

class Literal : public Expression {
	double value;
public:
	Literal(double value) : Expression(nullptr, nullptr), value(value) {}
	Literal(const Literal& l) : Expression(l), value(l.value) {}
	double eval() const {
		return value;
	}
	Expression* clone() const {
		return new Literal(*this);
	}
};

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

//class Sigmoid : public Expression {
//
//};

int main() {
	Expression* w1 = new Literal(5);
	Expression* x1 = new Literal(6);
	Expression* w2 = new Literal(7);
	Expression* x2 = new Literal(8);
	Expression* xd = new Mult(w1, x1);
	Expression* xdd = xd->clone();

	//Expression* res = new Add(new Mult(w1, x1), new Mult(w2, x2));
	std::cout << xd->left << " " << xd->right << std::endl;
	std::cout << xdd->left << " " << xdd->right << std::endl;
	std::cout << xdd->eval() << std::endl;
}