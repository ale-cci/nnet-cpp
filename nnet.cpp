#include "nnet.h"
#include "layer.h"
#include "utils"

#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

NeuralNetwork::~NeuralNetwork(){
	delete[] hidden_layer;
}

void NeuralNetwork::init(uint16_t inputs, uint16_t outputs, uint16_t hidden_layers, uint16_t hidden_layers_size = 0){
	if (hidden_layers_size == 0)
		hidden_layers_size = min(inputs, outputs);
	nof_inputs = inputs;
	nof_outputs = outputs;
	nof_hidden_layers = hidden_layers;
	this->hidden_layers_size = hidden_layers_size;

	hidden_layer = new Layer[hidden_layers];

	hidden_layer[0].allocate(inputs, hidden_layers_size);
	ffor(i, hidden_layers-1)
		hidden_layer[i+1].allocate(hidden_layers_size, hidden_layers_size);

	//hidden_layer[hidden_layers-1].allocate(hidden_layers_size, outputs);
	output_layer.allocate(hidden_layers_size, outputs);
}

float* NeuralNetwork::feed_forward(float* const inputs){
	float* data = inputs;//input_layer.normalize(inputs);
	ffor (i, nof_hidden_layers){
		data = hidden_layer[i].feed_forward(data);
	}

	data = output_layer.feed_forward(data);
	return data;
}


float NeuralNetwork::train(float* const inputs, float* expected_outputs) {
	float error[nof_outputs];
	float* output = feed_forward(inputs);
	float extimation = 0;

	ffor(i, nof_outputs) {
		error[i] = output[i]- expected_outputs[i];
		extimation += abs(error[i]);
	}
	float* data = output_layer.train(hidden_layer[nof_hidden_layers-1].last_output(), error);
	for (int i = nof_hidden_layers -1; i > 1; --i) {
		data = hidden_layer[i].train(hidden_layer[i-1].last_output(), data);
	}
	hidden_layer[0].train(inputs, data);

	return extimation;
}

ostream& operator<<(ostream& out, NeuralNetwork& net){
	out << "----] NET [----" << endl;
	ffor(i, net.nof_hidden_layers)
		out << net.hidden_layer[i];
	out << net.output_layer;
	return out;
}

void NeuralNetwork::save(const char* path){
	ofstream out(path, ios::out | ios::binary);
	assert(out.is_open());

	// Read Data from input
	out.write(spt(nof_inputs), sizeof(nof_inputs));
	out.write(spt(nof_outputs), sizeof(nof_outputs));
	out.write(spt(nof_hidden_layers), sizeof(nof_hidden_layers));
	out.write(spt(hidden_layers_size), sizeof(hidden_layers_size));
	cout << "Hidden layers" << int(*spt(nof_hidden_layers)) << endl;
	cout << "Writing " << int(nof_hidden_layers) << " -> " << path << endl;
	//init(nof_inputs, nof_outputs, nof_hidden_layers, hidden_layers_size);

	// Load layers data
	ffor(i, nof_hidden_layers)
		hidden_layer[i].save(out);
}

void NeuralNetwork::load(const char* path){
	// Opening File
	ifstream in(path, ios::in | ios::binary);
	assert(in.is_open());

	uint16_t nof_inputs, nof_outputs, nof_hidden_layers, hidden_layers_size;
	
	in.read(spt(nof_inputs), sizeof(nof_inputs));
	in.read(spt(nof_outputs), sizeof(nof_outputs));
	in.read(spt(nof_hidden_layers), sizeof(nof_hidden_layers));
	in.read(spt(hidden_layers_size), sizeof(hidden_layers_size));
	cout << "Hidden Layers: " << int(nof_hidden_layers) << endl;

	assert(nof_hidden_layers < 4 && "Input Error");

	init(nof_inputs, nof_outputs, nof_hidden_layers, hidden_layers_size);
	
	ffor(i, nof_hidden_layers)
		hidden_layer[i].load(in);
}