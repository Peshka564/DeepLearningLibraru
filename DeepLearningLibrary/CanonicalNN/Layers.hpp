#ifndef LAYERS_HPP
#define LAYERS_HPP

#include <vector>

//class Layer {
//public:
//	Layer();
//	Layer& operator=(const Layer&);
//};

// error checking for wrong input dimension
// input layer

class Dense /* : public Layer */ {
private:
	size_t nodesIn;
	size_t nodesOut;
	std::vector<std::vector<double>> weights;
	std::vector<double> biases;
	std::vector<double> output;
	std::vector<std::vector<double>> gradientWeights;
	std::vector<double> gradientBiases;
	// partial derivative of cost with respect to weighted output(z)
	std::vector<double> gradientOutput;
public:
	Dense(size_t nodes);
	size_t getNodesOut() const;
	void initializeParams(size_t);
	std::vector<double> calculateOutput(std::vector<double>&);
	std::vector<double> getActivatedOutput();
	void setError(const std::vector<double>&);
	void computeGradients(const std::vector<double>&);
	void updateParameters(size_t, double);
	std::vector<double> computePreviousError();
};

#endif // !LAYERS_HPP