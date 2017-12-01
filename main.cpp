#include <iostream>
#include <fstream>
#include "HEADERS/utils"
#include "HEADERS/nnet"
#include "HEADERS/settings.h"

using namespace std;

const static int NOF_INPUTS = 2;
const static int NOF_OUTPUTS = 1;
const static int EPOQUES = 1000;
const static int checking = 4;


int main(){
	/*
	NeuralNetwork test(NOF_INPUTS, NOF_OUTPUTS, 2, 4, 2);
	/*/
	NeuralNetwork test;
	test.load("test.nnet");
	//*/
	
	ofstream out(PLOT_FILE);
	// training samples
	int test_cases = 4;
	float inputs[test_cases][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
	float outputs[test_cases][1] = {{0}, {1}, {1}, {0}};

	if (WRITE_ON_FILE)
		out << LEARNING_RATE << endl << MOMENTUM << endl << checking << endl;
	
	// Training Network
	ffor(i, EPOQUES) {
		ffor(j, test_cases){
			float error = test.train(inputs[j%4], outputs[j%4]);
			if (WRITE_ON_FILE)
				out << error << endl;
		}
	}

	test.save("test.nnet");
	// Debug Inteface
	float in[2];
	while(1){
		cout << "Insert outputs: " << endl;
		ffor(i, NOF_INPUTS)
			cin >> in[i];
		cout << (*(test.feed_forward(in)) );
	}
	out.close();
	return 0;
}