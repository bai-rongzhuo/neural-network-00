/*
 * MainMenu.cpp
 *
 *  Created on: Jun 2, 2018
 *      Author: aboay
 */

#include <string>
#include <iostream>
//#include <limits>
#include "MainMenu.h"
#include "Neural_Network.h"

using namespace std;

int GetLayer(const NeuralNetwork* NN);
int GetNeuron(const NeuralNetwork* NN);
void ChangeMenu(const NeuralNetwork* NN);

void MainMenu(const NeuralNetwork* NN) {

	string Input;

	cout << "Welcome to the Neural Network Main Menu" << endl;

	do {

		cout
				<< "What would you like to do? Type 'Help' for all possible commands"
				<< endl;

		// ***********************************************************************************cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, Input);

		//Converts all letters to uppercase
		for (unsigned int i = 0; i <= Input.length(); i++) {
			Input[i] = toupper(Input[i]);
		}

		if (Input == "HELP") {
			cout << "Commands are:" << endl << "'Change' - Go to Change Menu"
					<< endl << "'Train' - Begins Neural Network Training"
					<< endl << "'Test' - Begins Neural Network Testing" << endl
					<< "'Exit' - Exit Main Menu" << endl;
		} else if (Input == "Change") {

			ChangeMenu(NN);

		}

	} while (Input != "EXIT");

}

void ChangeMenu(const NeuralNetwork* NN) {

	int NumIn = 0;
	string Input;

	cout << "Welcome to the Neural Network Change Menu" << endl;

	do {

		cout
				<< "What would you like to do? Type 'Help' for all possible commands"
				<< endl;

		// ***********************************************************************************cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, Input);

		//Converts all letters to uppercase
		for (unsigned int i = 0; i <= Input.length(); i++) {
			Input[i] = toupper(Input[i]);
		}

		if (Input == "HELP") {
			cout << "Commands are:" << endl
					<< "'Bias' - Change Bias Value for Layer" << endl
					<< "'Function' - Change Activation Function" << endl
					<< "'Output' - Calculate Output" << endl
					<< "'Weight' - Change a Weight Value" << endl
					<< "'Exit' - Exit Change Menu" << endl;
		} else if (Input == "BIAS") {

			int LayerNum = GetLayer(NN);

		} else if (Input == "FUNCTION") {

		} else if (Input == "OUTPUT") {

		} else if (Input == "WEIGHT") {

		}

	} while (Input != "EXIT");

}

int GetLayer(const NeuralNetwork* NN) {

	int NumIn;
	string Input;

	bool LayerFound = false;

	do{
	cout << "Please Enter the Type of Layer? Type 'Help' for all possible commands"
			<< endl;

	// ***********************************************************************************cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, Input);

	//Converts all letters to uppercase
	for (unsigned int i = 0; i <= Input.length(); i++) {
		Input[i] = toupper(Input[i]);
	}

	if (Input == "HELP") {
		cout << "Commands are:" << endl
				<< "'Input' - Input Layer" << endl
				<< "'Hidden' - Hidden Layers" << endl
				<< "'Output' - Output Layer" << endl;
	} else if(Input == "INPUT"){

	}else if(Input == "HIDDEN"){

		int i = NN->GetNumberOfHiddenLayers();

		do{

		} while(NumIn > 9||NumIn <1);


	}else if(Input == "OUTPUT"){

	}

	} while(LayerFound == false);



	return NumIn;
}


int GetNeuron(const NeuralNetwork* const NN){

	int NumIn;

	cout << "Please Enter the Neuron Number Starting at 1 from the Top: ";
	cin >> NumIn;

	return NumIn;
}
