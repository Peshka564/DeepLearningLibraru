#include <iostream>
#include "./engine.hpp"

int main() {
	Value v(5);
	Value g(10);
	Value p = v + g;
	p.grad = 3;
	std::cout << "Starts here:" << std::endl;
	p.backward();
	p.backward();
	std::cout << p.data << " " << p.grad << std::endl;
	std::cout << v.grad << " " << g.grad << std::endl;
}