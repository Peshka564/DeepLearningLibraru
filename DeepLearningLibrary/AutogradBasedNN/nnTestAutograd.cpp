#include <iostream>
#include <vector>
#include "./scalarEngine/engine.hpp"
#include "Layer.hpp"
#include "MLP.hpp"

Value f(Value& a, Value& b) {
	Value c = a - b;
	return c;
}

int main() {

	//MultiLayerPerceptron model(3, { 4, 4, 1 });
	//std::vector<std::vector<Value>> xs = { {2, 3, -1}, {3, -1, 0.5}, {0.5, 1, 1}, {1, 1, -1} };
	//std::vector<Value> predictions;
	//std::vector<Value> ys = { 1, -1, -1, 1 };
	///*for (size_t i = 0; i < xs.size(); i++) {
	//	for (auto& val : model.feedForward(xs[i])) {
	//		std::cout << val << std::endl;
	//		predictions.push_back(val);
	//	}
	//}*/
	//std::vector<Value> p = model.feedForward(xs[0]);
	//p[0].backprop();
	/*Value temp0 = ys[0] - predictions[0];
	Value temp1 = ys[1] - predictions[1];
	Value temp2 = ys[2] - predictions[2];
	Value temp3 = ys[3] - predictions[3];

	Value proxy0 = temp0 * temp0;
	Value proxy1 = temp1 * temp1;
	Value proxy2 = temp2 * temp2;
	Value proxy3 = temp3 * temp3;

	Value final1 = proxy0 + proxy1;
	Value final2 = proxy2 + proxy3;

	Value loss = final1 + final2;
	std::cout << "---------------" << std::endl;
	std::cout << loss << std::endl;
	std::cout << final2 << std::endl;
	loss.backprop();*/

	Value a(5), b(10);
	Value d = f(a, b);
	d.backprop();
	std::cout << a << std::endl << b << std::endl;
}