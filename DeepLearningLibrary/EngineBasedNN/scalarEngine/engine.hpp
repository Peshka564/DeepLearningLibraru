#ifndef SCALAR_ENGINE_HPP
#define SCALAR_ENGINE_HPP

#include <vector>
#include <functional>

class Value {
public:
	double data, grad;
	bool called;
	//std::vector<Value> chidren;
	std::function<void(double)> adjustGradients;

	void backward();
public:
	Value(double d);
	// add zero_grad and called = false

	friend Value operator+(Value& one, Value& other);
};

#endif