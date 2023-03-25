//#include <iostream>
#include "utils/Vector.hpp"

Vector func() {
	Vector a({ 2, 3, 4 });
	a.push_back(1);
	a.print();
	return a;
}

int main() {
	Vector v1({ 1, 2, 3 });
	v1.print();

	v1.push_back(2);
	v1.push_back(3.3);
	v1.push_back(-4.6);
	v1.push_back(0);
	v1.print();
	Vector b = func();
	b.print();
	Vector v2({ 1, 2, 3, 4 });
	v2.print();
	v2 = func();
	Vector v3(v2);
	v2.pop_back();
	v2.print();
	v3.print();
	std::cout << v2[2] << std::endl;
	std::cout << v2.normal() << std::endl;
	v2[2] = -1 / 2;
	std::cout << v2[2] << std::endl;
}