#include "layer.h"
#include "neuron.h"
#include "utils"
#include <cstring>
#include <iostream>

Layer::~Layer(){
	delete[] neuron;
}

void Layer::allocate(uint16_t prev_neurons, uint16_t nof_neurons){
	this->prev_neurons = prev_neurons;
	this->nof_neurons = nof_neurons;

	output = new float[nof_neurons];
	error = new float[prev_neurons];
	neuron = new Neuron[nof_neurons];
	ffor(i, nof_neurons)
		neuron[i].allocate(prev_neurons);
}

float* Layer::feed_forward(float* inputs) {
	ffor(i, nof_neurons)
		output[i] = neuron[i].feed_forward(inputs);
	return output;
}

float* Layer::train(float* inputs, float* errors) {
	memset(error, 0, prev_neurons);
	ffor(i, nof_neurons)
		neuron[i].train(inputs, errors[i], error);
	return error;
}

float* Layer::last_output() const {
	return output;
}

ostream& operator<<(ostream& out, Layer& layer){
	out << "__Layer(" << int(layer.nof_neurons) <<")__"<< endl;
	ffor(i, layer.nof_neurons)
		out << layer.neuron[i] << endl;
	return out;
}

void Layer::save(ofstream& out){
	ffor(i, nof_neurons)
		neuron[i].save(out);
}

void Layer::load(ifstream& in){
	ffor(i, nof_neurons)
		neuron[i].load(in);
}