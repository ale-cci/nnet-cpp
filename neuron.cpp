#include "neuron.h"
#include "utils"
#include <cstdlib>
#include <iostream>
#include <cassert>

const static float LEARNING_RATE = 0.3;
const static float MOMENTUM = 0.9;

using namespace std;

Neuron::Neuron(){
	bias = rand01() *2 - 1;
}

void Neuron::allocate(uint16_t nof_inputs) {
	this->nof_inputs = nof_inputs;
	weights = new float[nof_inputs];
	ffor(i, nof_inputs) 
		weights[i] = rand01();
}

float Neuron::feed_forward(float* inputs) {
	float sum = 0;
	ffor(i, nof_inputs){
		sum += inputs[i] * weights[i];
	}
	return sigmoid(bias + sum); // sigmoid
}

float deri(float x){
	return x*(1-x);
}

float tan_d(float x){
	return 1 - x*x;
}
void Neuron::train(float* const inputs, float error, float*errors) {
	float output = feed_forward(inputs);
	//float error = (output - expected_value);

	ffor(i, nof_inputs) {
		errors[i]  += weights[i] * error * deri(output) * MOMENTUM;
		weights[i] -= inputs[i] * deri(output) * (error) * LEARNING_RATE;
		bias 	   -= deri(output)*(error) * LEARNING_RATE;
	}
}

//void Neuron::save(ostream out)
Neuron::~Neuron(){
	delete[] weights;
}
ostream& operator<< (ostream& stream, Neuron& n){
	stream << "Bias: " << n.bias << endl;
	ffor(i, n.nof_inputs)
		stream << "W[" << i << "] \t" << n.weights[i] << endl;
	return stream;
}

void Neuron::save(ofstream& out){
	out.write(spt(bias), sizeof(bias));
	ffor(i, nof_inputs)
		out.write(spt(weights[i]), sizeof(weights[0]));
}

void Neuron::load(ifstream& in){
	in.read(spt(bias), sizeof(bias));
	ffor(i, nof_inputs)
		in.read(spt(weights[i]), sizeof(weights[i]));
}