#include <iostream>
#include <cstring>
#include "utils"
#include "nnet.h"
// paolo fornacciari (palazzina1)
//#include "neuron.h"


const static int NOF_INPUTS = 2;
const static int NOF_OUTPUTS = 1;
const static int EPOQUES = 100000; // 10^6

const static char* WORKING_FILE = "xor.nnet";

using namespace std;



int main(){
	NeuralNetwork n;
	float error;
	float inputs[NOF_INPUTS];
	float outputs[NOF_OUTPUTS];
	n.load(WORKING_FILE);
	//n.init(NOF_INPUTS, NOF_OUTPUTS, 2, 10);
	int cases[4] = {0, 1, 1 , 0};
	//cout << n;
	
	ffor(x, EPOQUES){
		ffor(i, NOF_INPUTS)
			inputs[i] = cases[(x+i)%4];
		outputs[0] = int(inputs[0]) ^ int (inputs[1]) ;
		error = n.train(inputs, outputs);
		//cout << n;
		//cout << "Error: " << pow(error, 2)*0.5 << endl;
	}
	
	//cout << n << endl;
	n.save(WORKING_FILE);
	while(1){
		cout << "Insert vals: "; 
		ffor(i, NOF_INPUTS)
			cin >> inputs[i];
		cout << "Prediction: " << *(n.feed_forward(inputs)) << endl;
	}
	return 0;
}