
#include "MainMenu.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Neural_Network.h"

using namespace std;

int main(int argc, char *argv[]) {

	cout << "|Handwritten Number Identification Neural Network|" << endl;

	if (argc == 4) {
		const string files[3] = { argv[1], argv[2], argv[3] };
		cout << "Pixel Input file: " << files[0] << endl;
		cout << "Identification Input file: " << files[1] << endl;
		cout << "Neural Network Output file: " << files[2] << endl;

	} else {
		cerr
				<< "Incorrect number of command parameters: (Pixel Input file, Identification Input file, Neural Network Output file)"
				<< endl;
		//return 1;
	}

	NeuralNetwork NN;
	NN.connect_layers(1);
	NN.create_neurons(1, 784, 18, 10);
	NN.connect_neurons();

	NN.Test();
	NN.Train();
	NN.Test();
}

