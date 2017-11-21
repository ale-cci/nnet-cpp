#ifndef __NEURON_H__
#define __NEURON_H__
#include <fstream>

using namespace std;

class Neuron{
private:
	float* weights = nullptr;
	float bias = 0;
	uint8_t nof_inputs;
public:
	Neuron();
	~Neuron();

	void allocate(uint16_t nof_inputs);
	float feed_forward(float* inputs);
	void train(float* const inputs, float expected_value, float* errors);
	// I/O on file
	friend ostream& operator<< (ostream& stream, Neuron& n);
	void save(ofstream& out);
	void load(ifstream& in);
};

#endif