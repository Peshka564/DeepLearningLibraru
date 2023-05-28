#include "ExprNeuron.hpp"
#include "Literal.hpp"
#include <iostream>

int main() {
	{	
		ExprNeuron n(5);
		Expression** input = new Expression * [5];
		input[0] = new Literal(5);
		input[1] = new Literal(3);
		input[2] = new Literal(6);
		input[3] = new Literal(1);
		input[4] = new Literal(2);
		std::cout << (n.activate(input)->eval()) << std::endl;
		for (size_t i = 0; i < 5; i++) delete input[i];
		delete[] input;
	}
	_CrtDumpMemoryLeaks();
}