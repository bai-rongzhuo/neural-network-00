#include <string>
#include <iostream>
#include <fstream>
#include "Neural_Network.h"

using namespace std;

int FileOpen(const string FileName, NeuralNetwork NN) {

	fstream Fin;

	Fin.open(FileName, ios::binary | ios::in);

	if (Fin.fail()) {
		cerr << "The File " << FileName << " cannot be opened" << endl;
		return 1;
	}

	//sizedouble and sizeint?
	double Sdbl = 0;
	int Sint = 0;

	//reads from the input file
	Fin.read((char *) &Sint, sizeof(Sint));
	if (Fin.fail()) {
		cerr << "The File " << FileName << " cannot be read from" << endl;
		return 1;
	}

	int NumOfHDDNLayers = Sint;
	int NumOfNeurons[NumOfHDDNLayers + 2];

	//reads in the image pixels from the file into internal memory
	for (int i = 1; i <= (NumOfHDDNLayers + 3); i++) {

		Fin.read((char *) &Sint, sizeof(Sint));
		if (Fin.fail()) {
			cerr << "The File " << FileName << " cannot be read from" << endl;
			return 1;
		}

		NumOfNeurons[(i - 1)] = Sint;

		Fin.read((char *) &Sdbl, sizeof(Sdbl));
		if (Fin.fail()) {
			cerr << "The File " << FileName << " cannot be read from" << endl;
			return 1;
		}

		NN.SetLayerBias(i, Sdbl);

	}

	//sets the activation functions
	for (int i = 0; i < NumOfHDDNLayers; i++) {
		for (int n = 0; n < NN.GetNumberOfNeurons(i); n++) {
			Fin.read((char *) &Sint, sizeof(Sint));
			if (Fin.fail()) {
				cerr << "The File " << FileName << " cannot be read from"
						<< endl;
				return 1;
			}

			NN.SetActivationFunction((i + 1), (n + 1), Sint);

			for (int x = 0; x < NN.GetNumberOfNeurons(i + 2); x++) {

				Fin.read((char *) &Sdbl, sizeof(Sdbl));
				if (Fin.fail()) {
					cerr << "The File " << FileName << " cannot be read from"
							<< endl;
					return 1;
				}

				NN.SetConnectionWeight((i+1),(n+1),(x+1),Sdbl);

			}

		}
	}

	return 0;
}
