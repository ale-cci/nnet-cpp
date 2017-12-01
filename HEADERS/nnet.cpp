#include <cstring>
#include <cstdarg>
#include <cmath>
#include <fstream>
#include "nnet"
#include "utils"

NeuralNetwork::NeuralNetwork(){}

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

	// hidden layers + output layers
	//layer_input = new float*[hidden_layers+1];
}

NeuralNetwork::~NeuralNetwork() {
	delete[] l_hidden;
}

// Input processing
float* NeuralNetwork::feed_forward(float* input) {

	ffor(i, _hidden_layers)
		input = l_hidden[i].feed_forward(input);

	return output = l_output.feed_forward(input);
}


float NeuralNetwork::train(float* input, float* expected_output) {
	float error_extimation = 0;
	//memset(error, 0., sizeof(float) * _outputs);
	feed_forward(input);
	ffor(i, _outputs){
		error[i] = output[i] - expected_output[i];
		error_extimation += std::abs(error[i]);
	}
	
	// Backpropagating errors
	float* data = l_output.train(l_hidden[_hidden_layers-1].get_output(), error);

	for(int i=_hidden_layers-1; i > 0; --i)
		data = l_hidden[i].train(l_hidden[i-1].get_output(), data);
	l_hidden[0].train(input, data);

	return error_extimation;
}

void NeuralNetwork::save(const char* path) const {
	std::ofstream out(path, std::ios::out | std::ios::binary);
	
	// Writing constructor data
	out.write(cstp(& _inputs), sizeof(_inputs));
	out.write(cstp(& _outputs), sizeof(_outputs));
	out.write(cstp(& _hidden_layers), sizeof(_hidden_layers));

	// loading layers data
	ffor(i, _hidden_layers)
		l_hidden[i].save(out);
	l_output.save(out);
}

void NeuralNetwork::load(const char* path){
	std::ifstream in(path, std::ios::in |std::ios::binary);

	in.read(stp(& _inputs), sizeof(_inputs));
	in.read(stp(& _outputs), sizeof(_outputs));
	in.read(stp(& _hidden_layers), sizeof(_hidden_layers));

	// allocating data
	l_hidden = new Layer[_hidden_layers];
	error = new float[_outputs];

	// loading layers data
	ffor(i, _hidden_layers)
		l_hidden[i].load(in);
	l_output.load(in);
}