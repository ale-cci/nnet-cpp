#include <iostream>
#include <cstring>
#include "utils"
#include "nnet.h"
//#include "neuron.h"


const static int NOF_INPUTS = 2;
const static int NOF_OUTPUTS = 1;
const static int EPOQUES =10000;

using namespace std;



int main(){
	NeuralNetwork n;
	float error;
	float inputs[NOF_INPUTS];
	float outputs[NOF_OUTPUTS];
	n.load("test.nnet");
	//n.init(NOF_INPUTS, NOF_OUTPUTS, 2, 2);

	//cout << n;
	/*
	ffor(_, EPOQUES){
		ffor(i, NOF_INPUTS)
			inputs[i] = rand()%2;
		outputs[0] = int(inputs[0]) && int (inputs[1]) ;

		error = n.train(inputs, outputs);
		//cout << n;
		cout << "Error: " << pow(error, 2)*0.5 << endl;
	}
	*/
	cout << n << endl;
	//n.save("test.nnet");

	while(1){
		cout << "Insert vals: "; 
		ffor(i, NOF_INPUTS)
			cin >> inputs[i];
		cout << "Prediction: " << *(n.feed_forward(inputs)) << endl;
	}
	return 0;
}

/*
int main(){
	float inputs[NOF_INPUTS];
	float neurons[NOF_INPUTS];
	float exp_val = 0;
	float error = 0;
	/*
	NeuralNetwork n;

	n.init(NOF_INPUTS, NOF_OUTPUTS, 3, 1);
	
	ffor(_ , EPOQUES) {
		inputs[0] = rand() % 2;
		inputs[1] = rand() % 2;
		exp_val = int(inputs[0]) || int(inputs[1]);
		cout << n.train(inputs, &exp_val) << endl;
	}

	while(true) {
		cout << endl << "Insert 2 values: ";
		cin >> inputs[0] >> inputs[1];
		cout << endl << "Prediction: " << n.feed_forward(inputs)[0] << endl;
	}
	*/
	/*
	Neuron n;
	n.allocate(NOF_INPUTS);
	while(1){
		cout << "Insert Inputs: ";
		ffor(i, NOF_INPUTS)
			cin >> inputs[i];
		cout << "Insert Expected val: ";
		cin >> exp_val;
		error = n.feed_forward(inputs);

		cout << "First Prediction: " << error << endl;
		cout << n << endl;

		memset(neurons, 0, NOF_INPUTS);
		n.train(inputs, error - exp_val, neurons);
		cout << "Last error: " << n.feed_forward(inputs) << endl;
		cout << n << endl;
	}
	
	return 0;
}*/