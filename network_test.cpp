#include <iostream>
#include <cstring>
#include "nnet.h"
#include "utils"

using namespace std;

static const uint8_t NOF_INPUTS = 2;
static const uint8_t NOF_OUTPUTS = 2;

int main(){
	NeuralNetwork n;
	float inputs[NOF_INPUTS];
	float outputs[NOF_OUTPUTS];

	n.init(NOF_INPUTS, NOF_OUTPUTS, 1, 2);

	cout << "Insert 2 vals: ";
	ffor(i, NOF_INPUTS)
		cin >> inputs[i];
	ffor(i, NOF_OUTPUTS)
		cin >> outputs[i];
	cout << n;
	n.train(inputs, outputs)
	cout << n;
	return 0;
}