#include <iostream>
#include <cmath>
#include <vector>
#include "engine.hpp"

Value::Value(double d) {
	data = d;
	grad = 0;
	adjustGradients = [&](double grad, double data) {};
}

Value operator+(Value& one, Value& other) {
	Value out(one.data + other.data);

	out.children.push_back(&one);
	out.children.push_back(&other);

	out.adjustGradients = [&](double grad, double data) {
		one.grad += grad;
		other.grad += grad;
	};

	return out;
}

Value operator-(Value& one, Value& other) {
	Value out(one.data - other.data);

	out.children.push_back(&one);
	out.children.push_back(&other);

	out.adjustGradients = [&](double grad, double data) {
		one.grad += grad;
		other.grad += -grad;
	};

	return out;
}

Value operator*(Value& one, Value& other) {
	Value out(one.data * other.data);

	out.children.push_back(&one);
	out.children.push_back(&other);

	out.adjustGradients = [&](double grad, double data) {
		one.grad += other.data * grad;
		other.grad += one.data * grad;
	};
	return out;
}

Value sigmoid(Value& one) {
	Value out(1 / (1 + std::exp(-one.data)));

	out.children.push_back(&one);

	out.adjustGradients = [&](double grad, double data) {
		//σ'(z) = σ(z)(1 - σ(z))
		one.grad += data * (1 - data ) * grad;
	};
	return out;
}

void Value::backward() const {
	std::cout << "Called backwards on value: " << data << std::endl;
	adjustGradients(this->grad, this->data);
}

bool isPresent(const Value* v, std::vector<const Value*>& visited) {
	for (size_t i = 0; i < visited.size(); i++) {
		if (v == visited[i]) return true;
	}
	return false;
}

void Value::buildTopo(std::vector<const Value*>& visited, std::vector<const Value*>& topo) const {
	if (!isPresent(this, visited)) {
		visited.push_back(this);
		for (size_t i = 0; i < children.size(); i++) {
			children[i]->buildTopo(visited, topo);
		}
		topo.push_back(this);
	}
}

// currently the algorithm assumes we have only 1 source
// will be fixed when implementing tensor based engine
std::vector<const Value*> Value::topoSort() const {
	std::vector<const Value*> visited;
	std::vector<const Value*> topo;
	buildTopo(visited, topo);
	return topo;
}

void Value::backprop() {
	std::vector<const Value*> proxy = topoSort();
	// we need to reverse the topoSorted array
	std::vector<const Value*> topo;
	for (int i = proxy.size() - 1; i >= 0; i--) topo.push_back(proxy[i]);

	this->grad = 1;

	// now we can update the gradients of the values
	for (size_t i = 0; i < topo.size(); i++) topo[i]->backward();
}

std::ostream& operator<<(std::ostream& os, const Value& v) {
	os << "Data: " << v.data << " Grad: " << v.grad;
	return os;
}