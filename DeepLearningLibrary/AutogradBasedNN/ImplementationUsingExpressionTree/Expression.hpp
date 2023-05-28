#ifndef EXPRESSION
#define EXPRESSION

class Expression {
protected:
	Expression* left, *right;
	double grad;

	static Expression* copyChildPointer(Expression* e);
public:
	Expression(Expression* left, Expression* right);
	Expression(const Expression& e);
	Expression& operator=(const Expression& e);
	virtual ~Expression();

	Expression(Expression&& e);
	Expression& operator=(Expression&& e);

	virtual double eval() const = 0;
	virtual Expression* clone() const = 0;
};

#endif