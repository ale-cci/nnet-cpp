#include <iostream>
#include <fstream>
#include "HEADERS/utils"
#include "HEADERS/nnet"

using namespace std;

const static char* PLOT_FILE = "PLOTS/plotdata.txt";
const static int NOF_INPUTS = 2;
const static int NOF_OUTPUTS = 1;
const static int EPOQUES = 5000;
const static int checking = 4;
const static bool WRITE_ON_FILE = true;

int main(){
	NeuralNetwork test(NOF_INPUTS, NOF_OUTPUTS, 2, 4, 2);
	ofstream out(PLOT_FILE);
	// training samples
	float inputs[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
	float outputs[4][1] = {{0}, {1}, {1}, {0}};

	// Training Network
	if (WRITE_ON_FILE)
		out << LEARNING_RATE << endl << MOMENTUM << endl << checking << endl;
	ffor(i, EPOQUES) {
		float error = test.train(inputs[i%4], outputs[i%4]);
		if (WRITE_ON_FILE)
			out << error << endl;

	}

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