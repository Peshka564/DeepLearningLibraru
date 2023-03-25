#include "Vector.hpp"
#include <initializer_list>

// class methods
Vector::Vector() : vector(nullptr), capacity(0), length(0) {};

Vector::Vector(std::initializer_list<double> il) {
	// utilizing iterators and initLists
	for (double d : il) {
		push_back(d);
	}
}

Vector::Vector(int index) {
	if (index < 0) {
		throw std::invalid_argument("Invalid vector size");
	}
	vector = new double[index];
	length = 0;
	capacity = index;
}

Vector::Vector(const Vector& v) {
	vector = new double[v.capacity];
	length = v.length;
	capacity = v.capacity;
	copy(vector, v.vector);
}

Vector& Vector::operator=(const Vector& v) {
	// avoid deleting own memory
	if (this != &v) {
		// avoid memory leak
		// if size is bigger than v.size - don't deallocate
		delete[] vector;
		// copy
		vector = new double[v.capacity];
		length = v.length;
		capacity = v.capacity;
		copy(vector, v.vector);
	}
	return *this;
}

Vector::Vector(Vector&& v) {
	vector = v.vector;
	length = v.length;
	capacity = v.capacity;

	v.vector = nullptr;
	v.length = 0;
	v.capacity = 0;
}

Vector& Vector::operator=(Vector&& v) {
	if (this != &v) {
		clear();
		vector = v.vector;
		length = v.length;
		capacity = v.capacity;

		v.vector = nullptr;
		v.length = 0;
		v.capacity = 0;
	}
	return *this;
}

void Vector::pop_back() {
	if (length) {
		length--;
	}
}

void Vector::push_back(double d) {
	reallocate();
	vector[length++] = d;
}

void Vector::insert(int index, double d) {
	if (index < 0 || index > length) throw std::invalid_argument("Invalid vector index");
	if (index == length) {
		push_back(d);
		return;
	}
	push_back(vector[length - 1]);
	for (int i = length - 2; i > index; i--) {
		vector[i] = vector[i - 1];
	}
	vector[index] = d;
}

void Vector::clear() {
	delete[] vector;
	vector = nullptr;
	length = 0;
	capacity = 0;
}

double Vector::operator[](int index) const {
	if (index < 0 || (size_t)index >= length) throw std::invalid_argument("Invalid vector indexing");
	return vector[index];
}

double& Vector::operator[](int index) {
	if (index < 0 || (size_t)index >= length) throw std::invalid_argument("Invalid vector indexing");
	return vector[index];
}

void Vector::setAt(int index, double val) {
	if (index < 0 || (size_t)index >= length) throw std::invalid_argument("Invalid vector indexing");
	vector[index] = val;
}

void Vector::print() const {
	for (size_t i = 0; i < length; i++) {
		std::cout << vector[i] << " ";
	}
	std::cout << std::endl;
}

size_t Vector::size() const {
	return length;
}

bool Vector::isEmpty() const {
	return !size();
}

void Vector::reallocate() {
	if (length == capacity) {
		capacity = !capacity + capacity * 2;
		double* arr = new double[capacity];
		copy(arr, vector);
		delete[] vector;
		vector = arr;
	}
}

void Vector::copy(double* dest, double* src) {
	for (size_t i = 0; i < length; i++) {
		dest[i] = src[i];
	}
}

double Vector::normal() const {
	double res = 0;
	for (size_t i = 0; i < length; i++) {
		res += vector[i] * vector[i];
	}
	return std::sqrt(res);
}

Vector::~Vector() {
	clear();
}

// outside functions

Vector add(Vector& a, Vector& b) {
	if (a.size() != b.size()) throw std::invalid_argument("Sizes aren't matching");
	Vector c;
	for (size_t i = 0; i < a.size(); i++) {
		c.push_back(a[i] + b[i]);
	}
	return c;
}

Vector subtract(Vector& a, Vector& b) {
	if (a.size() != b.size()) throw std::invalid_argument("Sizes aren't matching");
	Vector c;
	for (size_t i = 0; i < a.size(); i++) {
		c.push_back(a[i] - b[i]);
	}
	return c;
}

Vector multiply(Vector& a, Vector& b) {
	if (a.size() != b.size()) throw std::invalid_argument("Sizes aren't matching");
	Vector c;
	for (size_t i = 0; i < a.size(); i++) {
		c.push_back(a[i] * b[i]);
	}
	return c;
}

double dotProduct(Vector& a, Vector& b) {
	if (a.size() != b.size()) throw std::invalid_argument("Sizes aren't matching");
	double res = 0;
	for (size_t i = 0; i < a.size(); i++) {
		res += a[i] * b[i];
	}
	return res;
}