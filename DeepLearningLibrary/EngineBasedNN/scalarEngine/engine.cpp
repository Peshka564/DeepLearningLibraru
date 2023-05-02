#include <iostream>
#include <cmath>
#include "engine.hpp"

Value::Value(double d) {
	data = d;
	grad = 0;
}

Value operator+(Value& one, Value& other) {
	Value out(one.data + other.data);
	out.adjustGradients = [&](double grad) {
		one.grad += grad;
		other.grad += grad;
	};
	return out;
}

Value operator*(Value& one, Value& other) {
	Value out(one.data * other.data);
	out.adjustGradients = [&](double grad) {
		one.grad += other.data * grad;
		other.grad += one.data * grad;
	};
	return out;
}

Value sigmoid(Value& one, Value& other) {
	Value out(1 / (1 + std::exp(-one.data)));
	out.adjustGradients = [&](double grad) {
		one.grad += out.data * (1 - out.data ) * grad;
	};
	return out;
}

void Value::backward() {
	// it's not working, need to toposort
	// test with bigger network to make sure
	std::cout << "Called backwards on data: " << data << std::endl;
	adjustGradients(this->grad);
}