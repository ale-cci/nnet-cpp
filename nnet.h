#ifndef __NNET_H__
#define __NNET_H__

#include "layer.h"

class NeuralNetwork {
private:
	Layer output_layer;
	Layer* hidden_layer = nullptr;

	uint16_t nof_hidden_layers;
	uint16_t nof_inputs;
	uint16_t hidden_layers_size;
	uint16_t nof_outputs;

public:
	~NeuralNetwork();

	void init(uint16_t inputs, uint16_t outputs, uint16_t hidden_layers, uint16_t hidden_layers_size);
	float* feed_forward(float* const inputs);
	float train(float* const inputs, float* const expected_values);

	void save(const char* filename);
	void load(const char* filename);
	friend ostream& operator<<(ostream& out, NeuralNetwork& net);
};

#endif