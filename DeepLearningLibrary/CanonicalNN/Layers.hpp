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
	std::vector<double> outputs;
	std::vector<double> activatedOutputs;
	std::vector<std::vector<double>> gradientWeights;
	std::vector<double> gradientBiases;
	// partial derivative of cost with respect to weighted output(z)
	std::vector<double> gradientOutput;
public:
	Dense(size_t nodes);
	void initializeParams(size_t);

	std::vector<double> calculateOutput(std::vector<double>&);
	
	void setError(const std::vector<double>&);
	void computeGradients(const std::vector<double>&);
	void updateParameters(size_t, double);
	std::vector<double> computePreviousError();

	// getters
	size_t getNodesOut() const { return nodesOut; }
	const std::vector<std::vector<double>> getWeights() const { return weights; }
	const std::vector<double> getBiases() const { return biases; }
	const std::vector<double>& getActivatedOutput() const { return activatedOutputs; }
};

#endif // !LAYERS_HPP