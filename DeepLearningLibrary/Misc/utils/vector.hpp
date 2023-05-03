// A custom vector class
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <initializer_list>
#include <cmath>

//namespace utils {

template <typename T>
class Vector {
private:
	T* vector;
	size_t length;
	size_t capacity;

	void reallocate();
	void copy(T*, T*);
public:
	Vector();
	// can be skipped
	Vector(int);
	// easier initialisation than manual input
	Vector(std::initializer_list<T>);
	// copy
	Vector(const Vector&);
	Vector& operator=(const Vector&);
	// move
	Vector(Vector&&) noexcept;
	Vector& operator=(Vector&&) noexcept;
	~Vector();

	// core methods
	void push_back(T);
	void pop_back();
	void insert(int, T);
	void remove(int);
	T operator[](int) const;
	T& operator[](int);
	void print() const;
	bool isEmpty() const;
	void clear();
	size_t size() const;

	// task specific methods
	// get vector length
	T normal() const;
};

// vector pointwise add
template <typename T>
Vector<T> add(const Vector<T>&, const Vector<T>&);
// vector pointwise subtract
template <typename T>
Vector<T> subtract(const Vector<T>&, const Vector<T>&);
// hadamard product
template <typename T>
Vector<T> multiply(const Vector<T>&, const Vector<T>&);
// dot product
template <typename T>
T dotProduct(const Vector<T>&, const Vector<T>&);

#endif // !VECTOR_HPP