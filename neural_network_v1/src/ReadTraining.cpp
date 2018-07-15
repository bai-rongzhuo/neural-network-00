#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include "Neural_Network.h"
#include "ReadTraining.h"
#include "Function.h"
using namespace std;

vector<double> ReadTraining(int * Fail, int pics, int * Answer) {

	vector<double> Inputs;
	Fail = 0;

	if (pics < 0 || pics > 60000) {
		cerr << "Pic Number is out of bounds(0 - 60000)" << endl;
		(*Fail) = 1;
		return Inputs;
	}

	int Width = 28;
	int Height = 28;

	fstream Fin;
	fstream FLblin;

	Fin.open("train-images.idx3-ubyte", ios::in | ios::binary);

	if (Fin.fail() == true) {

		cerr
				<< "There was an error with the opening of the train-images.idx3-ubyte file"
				<< endl;

		(*Fail) = 1;
		return Inputs;

	}

	FLblin.open("train-labels.idx1-ubyte", ios::in | ios::binary);

	if (FLblin.fail() == true) {

		cerr
				<< "There was an error with the opening of the train-labels.idx1-ubyte file"
				<< endl;

		(*Fail) = 1;
		return Inputs;

	}

	FLblin.seekg(8 + pics, ios::beg);

	for (int row = 0; row < Height; row++) {
		for (int col = 0; col < Width; col++) {

			Fin.seekg((16 + (pics * Width * Height) + (Width * row) + col),
					ios::beg);

			int GrayTint = 0;

			Fin.read((char *) &GrayTint, sizeof(unsigned char));

			if (Fin.fail() == true) {

				cerr
						<< "There was an error with the reading of the train-images.idx3-ubyte file"
						<< endl;

				(*Fail) = 1;
				return Inputs;

			}

			if (GrayTint > 1000 || GrayTint < 0) {
				cerr
						<< "There was an error with the reading of the train-images.idx3-ubyte file kek"
						<< endl;

				(*Fail) = 1;
				return Inputs;
			}

			double Inp = (double) log(GrayTint+1);
			Inputs.push_back(Inp);

		}

	}

	int Num = 0;

	FLblin.read((char *) &Num, sizeof(unsigned char));

	if (FLblin.fail() == true) {

		cerr
				<< "There was an error with the reading of the train-labels.idx1-ubyte file"
				<< endl;
		(*Fail) = 1;
		return Inputs;
	}

	(*Answer) = Num;

	//int NumberofLabels = FLblin.tellg() - 8;
	int NumberofPics = Fin.tellg() - 16;

	Fin.close();

	if (Fin.fail() == true) {

		cerr
				<< "There was an error with the opening of the train-images.idx3-ubyte file"
				<< endl;

		(*Fail) = 1;
		return Inputs;

	}

	FLblin.close();

	if (FLblin.fail() == true) {

		cerr
				<< "There was an error with the closing of the train-labels.idx1-ubyte file"
				<< endl;

		(*Fail) = 1;
		return Inputs;

	}

	return Inputs;
}
