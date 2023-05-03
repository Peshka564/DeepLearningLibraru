#include <iostream>
#include <vector>
#include "./engine.hpp"

int main() {
	Value x1(1), x2(0.2355);
	Value y2 = x1 * x2;
	Value y1(0), y3(0.0665), y4(-2);
	Value z1 = y1 + y2, z2 = y3 * y4;
	Value finale = z1 + z2;

	finale.backprop();

	std::cout << "finale -> data: " << finale.getData() << " grad: " << finale.getGrad() << std::endl;
	std::cout << "z1 -> data: " << z1.getData() << " grad: " << z1.getGrad() << std::endl;
	std::cout << "z2 -> data: " << z2.getData() << " grad: " << z2.getGrad() << std::endl;
	std::cout << "y1 -> data: " << y1.getData() << " grad: " << y1.getGrad() << std::endl;
	std::cout << "y2 -> data: " << y2.getData() << " grad: " << y2.getGrad() << std::endl;
	std::cout << "y3 -> data: " << y3.getData() << " grad: " << y3.getGrad() << std::endl;
	std::cout << "y4 -> data: " << y4.getData() << " grad: " << y4.getGrad() << std::endl;
	std::cout << "x1 -> data: " << x1.getData() << " grad: " << x1.getGrad() << std::endl;
	std::cout << "x2 -> data: " << x2.getData() << " grad: " << x2.getGrad() << std::endl;
}