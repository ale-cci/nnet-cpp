#ifndef __NEURON_H__
#define __NEURON_H__
#include <fstream>

using namespace std;


const static float LEARNING_RATE = 0.25;
const static float MOMENTUM = 0.9;

class Neuron{
private:
	float* weights = nullptr;
	float* werrors = nullptr;
	float bias = 0;
	uint8_t nof_inputs;
	float berror = 0;
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