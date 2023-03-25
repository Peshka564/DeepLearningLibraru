// A custom vector class
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <initializer_list>
#include <cmath>

//namespace utils {

class Vector {
private:
	double* vector;
	size_t length;
	size_t capacity;

	void reallocate();
	void copy(double*, double*);
public:
	Vector();
	// can be skipped
	Vector(int);
	// easier initialisation than manual input
	Vector(std::initializer_list<double>);
	// copy
	Vector(const Vector&);
	Vector& operator=(const Vector&);
	// move
	Vector(Vector&&) noexcept;
	Vector& operator=(Vector&&) noexcept;
	~Vector();

	// core methods
	void push_back(double);
	void pop_back();
	void insert(int, double);
	void remove(int);
	double operator[](int) const;
	double& operator[](int);
	void print() const;
	bool isEmpty() const;
	void clear();
	size_t size() const;

	// task specific methods
	// get vector length
	double normal() const;
};

// use templates
//#include "vector.cpp"

// vector pointwise add
Vector add(const Vector&, const Vector&);
// vector pointwise subtract
Vector subtract(const Vector&, const Vector&);
// hadamard product
Vector multiply(const Vector&, const Vector&);
// dot product
double dotProduct(const Vector&, const Vector&);

#endif // !VECTOR_HPP