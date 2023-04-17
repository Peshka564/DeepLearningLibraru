#include <iostream>
#include "engine.hpp"

Value::Value(double d) {
	data = d;
	grad = 0;
	called = false;
}

Value operator+(Value& one, Value& other) {
	Value out(one.data + other.data);
	out.adjustGradients = [&](double grad) {
		one.grad += grad;
		other.grad += grad;
		if (!one.called && one.adjustGradients) one.backward();
		if (!other.called && other.adjustGradients) other.backward();
	};
	return out;
}

void Value::backward() {
	adjustGradients(this->grad);
	called = true;
}