#include "utils/Vector.hpp"

Vector func() {
	Vector a({ 2, 3, 4 });
	a.push_back(1);
	a.print();
	return a;
}

int main() {
	/*Vector v1({ 1, 2, 3 });
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
	Vector v3(func());
	v2.pop_back();
	v2.print();
	v3.print();
	std::cout << v2[2] << std::endl;
	std::cout << v2.normal() << std::endl;
	v2[2] = -1 / 2.0;
	std::cout << v2[2] << std::endl;
	v2.insert(2, 69);
	v2.print();
	v2.remove(0);
	v2.print();
	std::cout << v2.size() << std::endl;
	v2[0] = 1;
	v2[1] = 2;
	v2[2] = 3;
	v2.print();*/
}