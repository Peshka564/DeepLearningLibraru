#include <iostream>
#include "engine.hpp"

Value::Value(double d) {
	data = d;
	grad = 0;
	//called = false;
}

Value operator+(Value& one, Value& other) {
	Value out(one.data + other.data);
	out.adjustGradients = [&](double grad) {
		one.grad += grad;
		other.grad += grad;
		// ?? recursion
		/*one.backward();
		other.backward();*/
	};
	return out;
}

void Value::backward() {
	adjustGradients(this->grad);
}