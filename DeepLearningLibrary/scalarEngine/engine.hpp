#ifndef SCALAR_ENGINE_HPP
#define SCALAR_ENGINE_HPP

#include <vector>
#include <functional>

class Value {
public:
	double data, grad;
	//std::vector<Value> chidren;
	std::function<void()> backward;
public:
	Value(double d);
	Value operator+(Value& other);
};

#endif