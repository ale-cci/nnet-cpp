#include <cstring>
#include <cstdarg>
#include <cmath>
#include "nnet"
#include "utils"


NeuralNetwork::NeuralNetwork(uint16_t inputs, uint16_t outputs, uint16_t hidden_layers, ...) {
	va_list args;
	va_start(args, hidden_layers);
	_inputs = inputs;
	_outputs = outputs;
	_hidden_layers = hidden_layers;

	l_hidden = new Layer[hidden_layers];
	error = new float[_outputs];

	int last_size = inputs;
	for(int i=0; i<hidden_layers; ++i){
		int hl_size = va_arg(args, int);
		l_hidden[i].init(last_size, hl_size);
		last_size = hl_size;
	}

	l_output.init(last_size, outputs);
	std::cout << l_output << std::endl;

	// hidden layers + output layers
	layer_input = new float*[hidden_layers+1];
}

NeuralNetwork::~NeuralNetwork() {
	delete[] l_hidden;
}

// Input processing
float* NeuralNetwork::feed_forward(float* input) {
	layer_input[0] = input;
	ffor(i, _hidden_layers){
		layer_input[i +1] = l_hidden[i].feed_forward(layer_input[i]);
	}

	return l_output.feed_forward(layer_input[_hidden_layers]);
}


float NeuralNetwork::train(float* input, float* expected_output) {
	float error_extimation = 0;
	memset(error, 0., sizeof(float) * _outputs);
	output = feed_forward(input);

	ffor(i, _outputs){
		error[i] = output[i] - expected_output[i];
		error_extimation += std::abs(error[i]);
	}
	
	float* data = l_output.train(layer_input[_hidden_layers], error);
	for(int i=_hidden_layers-1; i >= 0; --i){
		data = l_hidden[i].train(layer_input[i], data);
	}
	return error_extimation;
}