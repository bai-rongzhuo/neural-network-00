#include <string>
#include <iostream>
#include <fstream>
#include "Neural_Network.h"

using namespace std;

int FileSave(const string FileName, const NeuralNetwork NN) {

	fstream Fout;

	Fout.open(FileName, ios::binary | ios::out);

	if (Fout.fail()) {
		cerr << "The File " << FileName << " cannot be opened" << endl;
		return 1;
	}

	double Sdbl = 0;
	int Sint = 0;

	int NumOfHDDNLayers = NN.GetNumberOfHiddenLayers();

	Sint = NumOfHDDNLayers;
	Fout.write((char *) &Sint, sizeof(Sint));
	if (Fout.fail()) {
		cerr << "The File " << FileName << " cannot be written to" << endl;
		return 1;
	}

	//writes the results out to a file
	for (int i = 1; i <= (NumOfHDDNLayers + 3); i++) {
		Sint = NN.GetNumberOfNeurons(i);
		Fout.write((char *) &Sint, sizeof(Sint));
		if (Fout.fail()) {
			cerr << "The File " << FileName << " cannot be written to" << endl;
			return 1;
		}

		Sdbl = NN.GetLayerBias(i);
		Fout.write((char *) &Sdbl, sizeof(Sdbl));
		if (Fout.fail()) {
			cerr << "The File " << FileName << " cannot be written to" << endl;
			return 1;
		}

	}

	for (int i = 0; i < NumOfHDDNLayers; i++) {
		for (int n = 0; n < NN.GetNumberOfNeurons(i); n++) {
			Sint = NN.GetActivationFunction((i + 1), n);
			Fout.write((char *) &Sint, sizeof(Sint));
			if (Fout.fail()) {
				cerr << "The File " << FileName << " cannot be written to"
						<< endl;
				return 1;
			}

			for (int x = 0; x < NN.GetNumberOfNeurons(i + 2); x++) {

				Sdbl = NN.GetConnectionWeight((i + 1), (n + 1), (x + 1));
				Fout.write((char *) &Sdbl, sizeof(Sdbl));
				if (Fout.fail()) {
					cerr << "The File " << FileName << " cannot be written to"
							<< endl;
					return 1;
				}

			}

		}
	}

	return 0;
}

