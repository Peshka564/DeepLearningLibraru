#include <iostream>
#include "engine.hpp"

Value::Value(double d) {
	data = d;
	grad = 0;
}

Value Value::operator+(Value& other) {
	Value out(this->data + other.data);
	// recursive call??
	out.backward = [&]() {
		std::cout << out.data << std::endl;
		this->grad += out.grad;
		other.grad += out.grad;
	};
	return out;
}