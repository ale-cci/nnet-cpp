#ifndef __LAYER_H__
#define __LAYER_H__
#include "neuron.h"
using namespace std;

class Layer {
private:
	Neuron* neuron = nullptr;
	uint8_t nof_neurons = 0;
	uint8_t prev_neurons = 0;
	float* output;
	float* error;
public:
	~Layer();

	void allocate(uint16_t nof_input, uint16_t nof_output);
	float* train(float* inputs, float* expected_results);
	float* feed_forward(float* inputs);

	float* last_output() const;
	// TODO: I/O on file
	void save(ofstream& input);
	void load(ifstream& output);
	friend ostream& operator<<(ostream&, Layer&);
};

#endif