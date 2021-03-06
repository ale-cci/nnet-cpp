#ifndef __NNET__
#define __NNET__
#include "layer.hpp"

class NeuralNetwork {
protected:
	// network constants
	uint16_t _inputs = 0;
	uint16_t _outputs = 0;
	uint8_t _hidden_layers = 0;

	Layer* l_hidden = nullptr;
	Layer l_output;
	float* error = nullptr;
	float* output = nullptr;

public:
	~NeuralNetwork();

	void allocate(uint16_t inputs, uint16_t outputs, uint16_t hidden_layers, ...);

	float train(float* inputs, float* expected_output);
	void backpropagate(float* inputs, float* expected_output);
	float* feed_forward(float* inputs);

	void save(const char* path) const;
	void load(const char* path);
};

float train(NeuralNetwork& nnet, uint64_t epoques, uint64_t batch);

#endif
