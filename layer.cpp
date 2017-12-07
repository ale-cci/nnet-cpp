#include <cstring>
#include <cassert>
#include <fstream>
#include <cmath>
#include "utils"
#include "layer.hpp"


float sigmoid(float x) {
	return 1 / (1 + exp(-x));
}

float sigmoid_prime(float y) {
	return y * (1 - y);
}

// coming soon activation funciton
float tanh_x(float x){
	return tanh(x);
}
float tanh_dy(float y){
	return 1 - y*y;
}


// Initialize layer memory
void Layer::init(const int nof_inputs, const int nof_neurons){
	assert(nof_neurons > 0);
	assert(nof_inputs > 0);

	_inputs = nof_inputs;
	_neurons = nof_neurons;

	// Initializing network weights
	_weight = new float*[_neurons];
	E_weight = new float*[_neurons];
	
	float bond = 1/sqrt(_inputs);

	ffor(neuron, _neurons) {
		_weight[neuron] = new float[_inputs];
		ffor(i, _inputs)
			_weight[neuron][i] = randTo(-bond, +bond);

		E_weight[neuron] = new float[_inputs];
		memset(E_weight[neuron], 0, _inputs);
	}

	// Initializing biases
	_bias = new float[_neurons];
	ffor(i, _neurons)
		_bias[i] = randTo(-bond, +bond);

	E_bias = new float[_neurons];
	memset(E_bias, 0, sizeof(float)*_neurons);

	// Init output values
	_output = new float[_neurons];
	_error = new float[_inputs];
}

Layer::~Layer(){
	delete[] _bias;
	delete[] E_bias;
	ffor(neuron, _neurons){
		delete[] E_weight[neuron];
		delete[] _weight[neuron];
	}
	delete[] E_weight;
	delete[] _weight;
	delete[] _error;
	delete[] _output;
}

// Change activation function
void Layer::set_activation(float (*activation)(float), float (*activation_dy)(float)){
	theta = activation;
	theta_prime = activation_dy;
}

// Input Processing
float* Layer::feed_forward(float* input) {
	memset(_output, 0, sizeof(float) * _neurons);
	ffor(neuron, _neurons) {
		ffor(i, _inputs)
			_output[neuron] += _weight[neuron][i] * input[i];

		_output[neuron] = theta(_output[neuron] + _bias[neuron]);
	}

	return _output;
}

// Get last layer output
float* const Layer::get_output() const{
	return _output;
}

// Trains the input based on the errors
float* Layer::train(float* input, float* error) {
	// Calculating output derivatives first for better performance
	ffor(i, _neurons){
		_output[i] = theta_prime(_output[i]);
	}

	memset(_error, 0, sizeof(float)*_inputs);

	ffor(neuron, _neurons){
		// updating biases
		E_bias[neuron] = MOMENTUM*E_bias[neuron] - LEARNING_RATE*error[neuron]*_output[neuron];
		_bias[neuron] += E_bias[neuron];

		ffor(i, _inputs){
			// calculating Weights and activations error
			E_weight[neuron][i] = MOMENTUM*E_weight[neuron][i] - LEARNING_RATE*error[neuron]*_output[neuron]*input[i];
			_error[i] += error[neuron]*_output[neuron]*_weight[neuron][i];
			// updating weights
			_weight[neuron][i] += E_weight[neuron][i];
		}
	}

	return _error;
}


std::ostream& operator<<(std::ostream& stream, Layer& l) {
	stream << "Layer [" << l._inputs << " x " << l._neurons << "]" << std::endl;
	stream << "Biases: " << std::endl;
	ffor(i, l._neurons)
		stream << l._bias[i] << " " << std::flush;
	stream << std::endl << "Weights: " << std::endl;
	ffor(neuron, l._neurons){
		ffor(i, l._inputs)
			stream << l._weight[neuron][i] << std::endl;
		stream << std::endl;
	}
	return stream;
}


uint16_t Layer::nof_neurons() const{
	return _neurons;
}
uint16_t Layer::nof_inputs() const{
	return _inputs;
}

void Layer::save(std::ofstream& out) const{
	out.write(cstp(& _inputs), sizeof(_inputs));
	out.write(cstp(& _neurons), sizeof(_neurons));

	ffor(i, _neurons)
		out.write(cstp(_weight[i]), sizeof(float) * _inputs);
	out.write(cstp(_bias), sizeof(float)*_neurons);
}

void Layer::load(std::ifstream& in){
	in.read(stp(& _inputs), sizeof(_inputs));
	in.read(stp(& _neurons), sizeof(_neurons));

	_bias = new float[_neurons];
	_weight = new float*[_neurons];
	ffor(i, _neurons){
		_weight[i] = new float[_inputs];
		in.read(stp(_weight[i]), sizeof(float)*_inputs);
	}
	in.read(stp(_bias), sizeof(float)*_neurons);

	// Init other memory
	_error = new float[_inputs];
	E_bias = new float[_neurons];
	E_weight = new float*[_neurons];
	_output = new float[_neurons];

	ffor(i, _neurons){
		E_weight[i] = new float[_inputs];
		memset(E_weight[i], 0, _inputs);
	}
	memset(E_bias, 0, _neurons);
}