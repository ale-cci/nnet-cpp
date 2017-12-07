#ifndef __LAYER_H__
#define __LAYER_H__
#include <iostream>
#include <cmath>
#include "settings.hpp"

float sigmoid(float);
float sigmoid_prime(float);

float tanh_x(float);
float tanh_dy(float);

class Layer{
private:
	uint16_t _inputs = 0;
	uint16_t _neurons = 0;

	// pointer to activation function
	float (*theta)(float) = sigmoid;
	float (*theta_prime)(float) = sigmoid_prime;

	// layer data
	float** _weight = nullptr;
	float* _bias = nullptr;

 	// Past errors 
	float** E_weight = nullptr;
	float* E_bias = nullptr;

	float* _output = nullptr;
	float* _error = nullptr;
public:
	~Layer();

	void init(const int nof_inputs, const int nof_neurons);
	void set_activation(float (*activation)(float), float (*activation_dy)(float));
	float* const get_output() const;
	uint16_t nof_neurons() const;
	uint16_t nof_inputs() const;


	// Network operations
	float* feed_forward(float* inputs); 	// takes the inputs from the previous layer and returns the processed input
	float* train(float* last_inputs, float* error);		// takes the list of errors & previous inputs and returns the partial errors of the previous layer

	// IO operations
	void save(std::ofstream& stream) const;
	void load(std::ifstream& stream);

	friend std::ostream& operator<<(std::ostream& stream, Layer& out);
};

#endif