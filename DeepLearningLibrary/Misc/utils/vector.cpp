#include "vector.hpp"
#include <initializer_list>

// class methods
template <typename T>
Vector<T>::Vector() : vector(nullptr), capacity(0), length(0) {};

template <typename T>
Vector<T>::Vector(std::initializer_list<T> il) {
	// utilizing iterators and initLists
	for (T d : il) {
		push_back(d);
	}
}

template <typename T>
Vector<T>::Vector(int index) {
	if (index < 0) {
		throw std::invalid_argument("Invalid vector size");
	}
	vector = new T[index];
	length = 0;
	capacity = index;
}

template <typename T>
Vector<T>::Vector(const Vector<T>& v) {
	vector = new T[v.capacity];
	length = v.length;
	capacity = v.capacity;
	copy(vector, v.vector);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& v) {
	// avoid deleting own memory
	if (this != &v) {
		// avoid memory leak
		// if size is bigger than v.size - don't deallocate
		delete[] vector;
		// copy
		vector = new T[v.capacity];
		length = v.length;
		capacity = v.capacity;
		copy(vector, v.vector);
	}
	return *this;
}

template <typename T>
Vector<T>::Vector(Vector<T>&& v) noexcept {
	vector = v.vector;
	length = v.length;
	capacity = v.capacity;

	v.vector = nullptr;
	v.length = 0;
	v.capacity = 0;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& v) noexcept {
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

template <typename T>
void Vector<T>::pop_back() {
	if (length) {
		length--;
	}
}

template <typename T>
void Vector<T>::push_back(T d) {
	reallocate();
	vector[length++] = d;
}

template <typename T>
void Vector<T>::insert(int index, T d) {
	if (index < 0 || index > length) throw std::invalid_argument("Invalid vector index");
	if (index == length) {
		push_back(d);
		return;
	}
	push_back(vector[length - 1]);
	for (int i = (int)length - 2; i > index; i--) {
		vector[i] = vector[i - 1];
	}
	vector[index] = d;
}

template <typename T>
void Vector<T>::remove(int index) {
	if (index < 0 || index >= length) throw std::invalid_argument("Invalid vector index");
	if (index == length - 1) {
		pop_back();
		return;
	}
	for (int i = index; i < length - 1; i++) {
		vector[i] = vector[i + 1];
	}
	length--;
}

template <typename T>
void Vector<T>::clear() {
	delete[] vector;
	vector = nullptr;
	length = 0;
	capacity = 0;
}

template <typename T>
T Vector<T>::operator[](int index) const {
	if (index < 0 || (size_t)index >= length) throw std::invalid_argument("Invalid vector indexing");
	return vector[index];
}

template <typename T>
T& Vector<T>::operator[](int index) {
	if (index < 0 || (size_t)index >= length) throw std::invalid_argument("Invalid vector indexing");
	return vector[index];
}

template <typename T>
void Vector<T>::print() const {
	for (size_t i = 0; i < length; i++) {
		std::cout << vector[i] << " ";
	}
	std::cout << std::endl;
}

template <typename T>
size_t Vector<T>::size() const {
	return length;
}

template <typename T>
bool Vector<T>::isEmpty() const {
	return !size();
}

template <typename T>
void Vector<T>::reallocate() {
	if (length == capacity) {
		capacity = !capacity + capacity * 2;
		T* arr = new T[capacity];
		copy(arr, vector);
		delete[] vector;
		vector = arr;
	}
}

template <typename T>
void Vector<T>::copy(T* dest, T* src) {
	for (size_t i = 0; i < length; i++) {
		dest[i] = src[i];
	}
}

template <typename T>
T Vector<T>::normal() const {
	T res = 0;
	for (size_t i = 0; i < length; i++) {
		res += vector[i] * vector[i];
	}
	return std::sqrt(res);
}

template <typename T>
Vector<T>::~Vector() {
	clear();
}

// outside functions

template <typename T>
Vector<T> add(const Vector<T>& a, const Vector<T>& b) {
	if (a.size() != b.size()) throw std::invalid_argument("Sizes aren't matching");
	Vector<T> c;
	for (size_t i = 0; i < a.size(); i++) {
		c.push_back(a[i] + b[i]);
	}
	return c;
}

template <typename T>
Vector<T> subtract(const Vector<T>& a, const Vector<T>& b) {
	if (a.size() != b.size()) throw std::invalid_argument("Sizes aren't matching");
	Vector<T> c;
	for (size_t i = 0; i < a.size(); i++) {
		c.push_back(a[i] - b[i]);
	}
	return c;
}

template <typename T>
Vector<T> multiply(const Vector<T>& a, const Vector<T>& b) {
	if (a.size() != b.size()) throw std::invalid_argument("Sizes aren't matching");
	Vector<T> c;
	for (size_t i = 0; i < a.size(); i++) {
		c.push_back(a[i] * b[i]);
	}
	return c;
}

template <typename T>
T dotProduct(const Vector<T>& a, const Vector<T>& b) {
	if (a.size() != b.size()) throw std::invalid_argument("Sizes aren't matching");
	T res = 0;
	for (size_t i = 0; i < a.size(); i++) {
		res += a[i] * b[i];
	}
	return res;
}

// All necessary numeric types
template class Vector<int>;
template class Vector<long>;
template class Vector<long long>;
template class Vector<float>;
template class Vector<double>;
template class Vector<long double>;

template Vector<int> add<int>(const Vector<int>&, const Vector<int>&);
template Vector<long> add<long>(const Vector<long>&, const Vector<long>&);
template Vector<long long> add<long long>(const Vector<long long>&, const Vector<long long>&);
template Vector<float> add<float>(const Vector<float>&, const Vector<float>&);
template Vector<double> add<double>(const Vector<double>&, const Vector<double>&);
template Vector<long double> add<long double>(const Vector<long double>&, const Vector<long double>&);

template Vector<int> subtract<int>(const Vector<int>&, const Vector<int>&);
template Vector<long> subtract<long>(const Vector<long>&, const Vector<long>&);
template Vector<long long> subtract<long long>(const Vector<long long>&, const Vector<long long>&);
template Vector<float> subtract<float>(const Vector<float>&, const Vector<float>&);
template Vector<double> subtract<double>(const Vector<double>&, const Vector<double>&);
template Vector<long double> subtract<long double>(const Vector<long double>&, const Vector<long double>&);

template Vector<int> multiply<int>(const Vector<int>&, const Vector<int>&);
template Vector<long> multiply<long>(const Vector<long>&, const Vector<long>&);
template Vector<long long> multiply<long long>(const Vector<long long>&, const Vector<long long>&);
template Vector<float> multiply<float>(const Vector<float>&, const Vector<float>&);
template Vector<double> multiply<double>(const Vector<double>&, const Vector<double>&);
template Vector<long double> multiply<long double>(const Vector<long double>&, const Vector<long double>&);

template int dotProduct<int>(const Vector<int>&, const Vector<int>&);
template long dotProduct<long>(const Vector<long>&, const Vector<long>&);
template long long dotProduct<long long>(const Vector<long long>&, const Vector<long long>&);
template float dotProduct<float>(const Vector<float>&, const Vector<float>&);
template double dotProduct<double>(const Vector<double>&, const Vector<double>&);
template long double dotProduct<long double>(const Vector<long double>&, const Vector<long double>&);