#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <random>
#include "Layer.h"
#include "Neural_Network.h"
#include "Neuron.h"
#include "ReadTraining.h"
#include "Function.h"

using namespace std;

NeuralNetwork::NeuralNetwork() {
	OutputLayer = new Layer;
	InputLayer = new Layer;
	Learning_Rate = 0.5;

}

NeuralNetwork::~NeuralNetwork() {

	delete OutputLayer;
	delete InputLayer;

}

/**
 * This returns the number of hidden layers in the
 * neural network object
 *
 */
int NeuralNetwork::GetNumberOfHiddenLayers() const {

	return HiddenLayers.size();
}

/**
 * This returns the Number of neurons in a layer
 */
int NeuralNetwork::GetNumberOfNeurons(int LayerNum) const {

	int NumOfNeurons = 0;

	if (LayerNum == 1) {
		NumOfNeurons = InputLayer->Neurons.size();
	} else if (LayerNum > 1 && LayerNum < (HiddenLayers.size() + 2)) {
		NumOfNeurons = HiddenLayers[(LayerNum - 1)]->Neurons.size();
	} else {
		NumOfNeurons = OutputLayer->Neurons.size();
	}

	return NumOfNeurons;
}

/**
 * Returns a layer bias in form of a double
 */
double NeuralNetwork::GetLayerBias(int LayerNum) const {

	double Bias;

	if (LayerNum == 1) {
		Bias = InputLayer->bias;
	} else if (LayerNum > 1 && LayerNum < (HiddenLayers.size() + 2)) {
		Bias = HiddenLayers[(LayerNum - 1)]->bias;
	} else if (LayerNum == (HiddenLayers.size() + 2)) {
		Bias = OutputLayer->bias;
	}

	return Bias;
}

/**
 * Gets Layer Number, Neuron Number, and Connection Number from user
 * Returns weight of connection as double
 * Returns NULL if parameters are out of bounds
 */
double NeuralNetwork::GetConnectionWeight(int LayerNum, int NeuronNum,
		int ConnectionNeuronNum) const {

	double Weight = NULL;

	if (LayerNum == 1) {

		if ((NeuronNum < GetNumberOfNeurons(LayerNum))
				&& (ConnectionNeuronNum < GetNumberOfNeurons(LayerNum + 1))) {

			Weight = InputLayer->Neurons[(NeuronNum - 1)]->GetWeight(
					ConnectionNeuronNum);

		}

	} else if ((LayerNum < (HiddenLayers.size() + 2)) && LayerNum > 1) {
		if ((NeuronNum < GetNumberOfNeurons(LayerNum))
				&& (ConnectionNeuronNum < GetNumberOfNeurons(LayerNum + 1))) {

			Weight =
					HiddenLayers[(LayerNum - 1)]->Neurons[(NeuronNum - 1)]->GetWeight(
							ConnectionNeuronNum);

		}

	}

	return Weight;
}

int NeuralNetwork::GetActivationFunction(int LayerNum, int NeuronNum) const {

	int ActivationFn = NULL;
	if (NeuronNum < GetNumberOfNeurons(LayerNum)) {
		if (LayerNum == 1) {

			ActivationFn =
					InputLayer->Neurons[(NeuronNum - 1)]->GetActivationFunction();

		} else if ((LayerNum < (HiddenLayers.size() + 2)) && LayerNum > 1) {

			ActivationFn =
					HiddenLayers[(LayerNum - 1)]->Neurons[(NeuronNum - 1)]->GetActivationFunction();
		}
	}

	return ActivationFn;
}

void NeuralNetwork::SetNumberOfHiddenLayers(int NumOfHDDNLayers) {

}
void NeuralNetwork::SetNumberOfNeurons(int LayerNum, int NumOfNeurons) {

}
void NeuralNetwork::SetLayerBias(int LayerNum, double Bias) {

	if (LayerNum == 1) {
		InputLayer->bias = Bias;
	} else if (LayerNum > 1 && LayerNum < (HiddenLayers.size() + 2)) {
		HiddenLayers[(LayerNum - 1)]->bias = Bias;
	} else if (LayerNum == (HiddenLayers.size() + 2)) {
		OutputLayer->bias = Bias;
	}

}
void NeuralNetwork::SetConnectionWeight(int LayerNum, int NeuronNum,
		int ConnectionNeuronNum, double Weight) {

	if (LayerNum == 1) {
		InputLayer->Neurons[(NeuronNum - 1)]->SetConnectionWeight(
				ConnectionNeuronNum, Weight);
	} else if (LayerNum > 1 && LayerNum < (HiddenLayers.size() + 2)) {
		HiddenLayers[(LayerNum - 1)]->Neurons[(NeuronNum - 1)]->SetConnectionWeight(
				ConnectionNeuronNum, Weight);
	} else if (LayerNum == (HiddenLayers.size() + 2)) {
		OutputLayer->Neurons[(NeuronNum - 1)]->SetConnectionWeight(
				ConnectionNeuronNum, Weight);
	}

}
void NeuralNetwork::SetActivationFunction(int LayerNum, int NeuronNum,
		int ActivationFN) {

	if (LayerNum == 1) {
		InputLayer->Neurons[(NeuronNum - 1)]->SetActivationFunction(
				ActivationFN);
	} else if (LayerNum > 1 && LayerNum < (HiddenLayers.size() + 2)) {
		HiddenLayers[(LayerNum - 1)]->Neurons[(NeuronNum - 1)]->SetActivationFunction(
				ActivationFN);
	} else if (LayerNum == (HiddenLayers.size() + 2)) {
		OutputLayer->Neurons[(NeuronNum - 1)]->SetActivationFunction(
				ActivationFN);
	}

}

void NeuralNetwork::create_neurons(int num_of_hidden_layers,
		int input_neurons_per_layer, int hidden_neurons_per_layer,
		int output_neurons_per_layer) {

	for (int i = 0; i < input_neurons_per_layer; i++) {

		//new nueron is created until the required neurons is reached for input layer
		InputLayer->Neurons.push_back(new Neuron());

	}

	for (int j = 0; j < num_of_hidden_layers; j++) {

		//runs through each hidden layer

		for (int i = 0; i < hidden_neurons_per_layer; i++) {

			//new nueron is created until the required neurons is reached for hidden layer
			HiddenLayers[j]->Neurons.push_back(new Neuron());

		}

	}

	for (int i = 0; i < output_neurons_per_layer; i++) {

		//new nueron is created until the required neurons is reached for output layer
		OutputLayer->Neurons.push_back(new Neuron());

	}

}

void NeuralNetwork::connect_layers(int num_of_hidden_layers) {

	default_random_engine generator;
	normal_distribution<double> distribution(0.0, 1.0);

	//creates and connects each of the hidden layers together
	for (int i = 0; i < num_of_hidden_layers; i++) {

		HiddenLayers.push_back(new Layer());

		//if it is not the first hidden layer it is conneted with the previous hidden layer
		if (i > 0) {
			HiddenLayers[i]->prevLayer = HiddenLayers[i - 1];
			HiddenLayers[i - 1]->nextLayer = HiddenLayers[i];
		}
		//first hidden layer is connected with the input layer
		else {
			HiddenLayers[i]->nextLayer = NULL;
			HiddenLayers[i]->prevLayer = InputLayer;
		}

		double RndNum = distribution(generator) / 100;
		HiddenLayers[i]->bias = RndNum;

	}

	//connects the input and output layers to the hidden layers
	InputLayer->nextLayer = HiddenLayers.front();
	InputLayer->prevLayer = NULL;
	OutputLayer->prevLayer = HiddenLayers.back();
	OutputLayer->nextLayer = NULL;
	HiddenLayers.back()->nextLayer = OutputLayer;

	double RndNum = distribution(generator) / 100;
	OutputLayer->bias = RndNum;

}

void NeuralNetwork::connect_neurons() {

	default_random_engine generator;
	normal_distribution<double> distribution(0.0, 1.0);

	cout << "Input layer Connecting" << endl;

	for (int j = 0; j < InputLayer->Neurons.size(); j++) {

		for (int i = 0; i < HiddenLayers[0]->Neurons.size(); i++) {

			InputLayer->Neurons[j]->Connections.push_back(new Connection()); //creates new connection
			InputLayer->Neurons[j]->Connections[i]->ConnectedNeuron =
					HiddenLayers[0]->Neurons[i]; // Sets to address of the connected neuron in the next layer

			double RndNum = distribution(generator) / 100;
			InputLayer->Neurons[j]->SetConnectionWeight((i + 1), RndNum);

		}

	}

	cout << "Input layer Connected" << endl;

	//Runs through each hidden layer except the last one
	for (int k = 0; k < (HiddenLayers.size() - 1); k++) {
		cout << "Hidden layer " << k << " Connecting" << endl;

		//Runs through each neuron in the layer being connected
		for (int j = 0; j < HiddenLayers[k]->Neurons.size(); j++) {

			//Connects each neuron to the neurons in the next hidden layer
			for (int i = 0; i < HiddenLayers[k + 1]->Neurons.size(); i++) {

				HiddenLayers[k]->Neurons[j]->Connections.push_back(
						new Connection); //creates new connection
				HiddenLayers[k]->Neurons[j]->Connections[i]->ConnectedNeuron =
						HiddenLayers[k + 1]->Neurons[i]; // Sets to address of the connected neuron in the next layer

				double RndNum = distribution(generator) / 100;
				HiddenLayers[k]->Neurons[j]->SetConnectionWeight((i + 1),
						RndNum);

			}

		}

		cout << "Hidden layer " << k << " Connected" << endl;

	}

	//Runs through each neuron in the layer being connected
	for (int j = 0; j < HiddenLayers.back()->Neurons.size(); j++) {

		//Makes a connection to each neuron in the next layer
		for (int i = 0; i < OutputLayer->Neurons.size(); i++) {

			HiddenLayers.back()->Neurons[j]->Connections.push_back(
					new Connection); //creates new connection
			HiddenLayers.back()->Neurons[j]->Connections[i]->ConnectedNeuron =
					HiddenLayers[0]->Neurons[i]; // Sets to address of the connected neuron in the next layer

			double RndNum = distribution(generator);
			HiddenLayers.back()->Neurons[j]->Connections[i]->Weight = RndNum;

		}

	}

}

vector<double> NeuralNetwork::Fire(vector<double> Inputs) {

	for (int i = 0; i < Inputs.size(); i++) {
		//cout << Inputs[i] << endl;
	}

	vector<double> Output;

	for (int i = 0; i < HiddenLayers.size(); i++) {

		for (int j = 0; j < HiddenLayers[i]->Neurons.size(); j++) {

			double sum = 0;

			if (i == 0) {

				for (int k = 0; k < InputLayer->Neurons.size(); k++) {

					sum += ((Inputs[k]
							* InputLayer->Neurons[k]->Connections[j]->Weight)
							+ HiddenLayers[i]->bias);
				}

			} else {

				for (int k = 0; k < HiddenLayers[(i - 1)]->Neurons.size();
						k++) {

					sum +=
							((HiddenLayers[(i - 1)]->Neurons[k]->GetOutput()
									* HiddenLayers[(i - 1)]->Neurons[k]->Connections[j]->Weight)
									+ HiddenLayers[i]->bias);

				}

			}
			HiddenLayers[i]->Neurons[j]->SetInput(sum);
			HiddenLayers[i]->Neurons[j]->Fire();

		}

	}

	vector<double> SMIn;

	for (int j = 0; j < OutputLayer->Neurons.size(); j++) {

		double sum = 0;
		for (int k = 0; k < HiddenLayers.back()->Neurons.size(); k++) {
			sum += (HiddenLayers.back()->Neurons[k]->GetOutput()
					* HiddenLayers.back()->Neurons[k]->Connections[j]->Weight);
		}
		OutputLayer->Neurons[j]->SetInput(sum);
		SMIn.push_back(sum);
	}

	for (int j = 0; j < OutputLayer->Neurons.size(); j++) {

		OutputLayer->Neurons[j]->SetActivationFunction(4);
		OutputLayer->Neurons[j]->SetOutput(
				SoftMax(OutputLayer->Neurons[j]->GetInput(), SMIn));

		Output.push_back(OutputLayer->Neurons[j]->GetOutput());
	}

	return Output;
}

int NeuralNetwork::Train() {

	int fail = 0;
	int Answer = 0;

	double Cost = 0;

	vector<vector<double>> InputVector;

	int loop = 0;

	while (true) {

		vector<vector<vector<double>>> PicError;

		for (int l = (1000*loop); l < (1000*(loop+1)); l++) {
			vector<double> Inputs = ReadTraining(&fail, l, &Answer);

			if (fail == 1) {
				return 1;
			}

			vector<double> Outputs = Fire(Inputs);

			vector<double> Answers = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
			Answers[Answer] = 1;

			Cost += Cross_Entropy(Outputs, Answers);

			vector<vector<double>> LayerError;
			vector<double> OutInputs;
			for (int i = 0; i < OutputLayer->Neurons.size(); i++) {
				OutInputs.push_back(OutputLayer->Neurons[i]->GetInput());
			}

			vector<vector<vector<double>>> Weights;

			for (int i = 0; i < (HiddenLayers.size() + 1); i++) {

				vector<vector<double>> LW;

				if (i == 0) {
					for (int j = 0; j < InputLayer->Neurons.size(); j++) {

						vector<double> NW;

						for (int k = 0;
								k < InputLayer->Neurons[j]->Connections.size();
								k++) {

							NW.push_back(
									InputLayer->Neurons[j]->Connections[k]->Weight);
						}

						LW.push_back(NW);

					}

				} else {
					for (int j = 0; j < HiddenLayers[i - 1]->Neurons.size();
							j++) {

						vector<double> NW;

						for (int k = 0;
								k
										< HiddenLayers[i - 1]->Neurons[j]->Connections.size();
								k++) {

							NW.push_back(
									HiddenLayers[i - 1]->Neurons[j]->Connections[k]->Weight);

						}

						LW.push_back(NW);

					}
				}

				Weights.push_back(LW);

			}

			LayerError.push_back(
					ErrorInOuterLayer(OutInputs, Answers, Outputs));

			for (int i = 0; i < (HiddenLayers.size() + 1); i++) {

				vector<double> InOutputs;

				if (i == HiddenLayers.size()) {
					for (int r = 0; r < InputLayer->Neurons.size(); r++) {
						InOutputs.push_back(
								InputLayer->Neurons[r]->GetOutput());
					}
					LayerError.insert(LayerError.begin(),
							ErrorInPrevLayer(Weights[HiddenLayers.size() - 1],
									LayerError[0], InOutputs));
				} else {
					for (int r = 0;
							r
									< HiddenLayers[HiddenLayers.size() - 1 - i]->Neurons.size();
							r++) {

						InOutputs.push_back(
								HiddenLayers[HiddenLayers.size() - i - 1]->Neurons[r]->GetOutput());
					}
					LayerError.insert(LayerError.begin(),
							ErrorInPrevLayer(Weights[HiddenLayers.size() - i],
									LayerError[0], InOutputs));
				}
			}
			PicError.push_back(LayerError);

		}

		Cost /= 1000;
		cout << "Average Cost --> " << Cost << endl;

		vector<vector<double>> AverageError(PicError[0].size());

		for (int g = 0; g < PicError[0].size(); g++) {
			for (int p = 0; p < PicError[g][0].size(); p++) {
				AverageError[g].push_back(0);
			}
		}

		for (int x = 0; x < PicError.size(); x++) {
			for (int q = 0; q < PicError[x].size(); q++) {
				for (int k = 0; k < PicError[x][q].size(); k++) {
					AverageError[q][k] += PicError[x][q][k];

				}
			}

		}

		for (int q = 0; q < AverageError.size(); q++) {
			for (int k = 0; k < AverageError[q].size(); k++) {
				AverageError[q][k] /= PicError.size();

			}
		}

		for (int e = 0; e < HiddenLayers.size(); e++) {
			double sum;
			for (int x = 0; x < HiddenLayers[e]->Neurons.size(); x++) {
				sum += AverageError[e][x];
			}
			sum /= HiddenLayers[e]->Neurons.size();

			HiddenLayers[e]->bias = Update(HiddenLayers[e]->bias, Learning_Rate,
					sum);

		}

		for (int e = 0; e < (HiddenLayers.size() + 1); e++) {
			if (e == 0) {
				for (int x = 0; x < InputLayer->Neurons.size(); x++) {
					for (int o = 0;
							o < InputLayer->Neurons[x]->Connections.size();
							o++) {
						InputLayer->Neurons[x]->Connections[o]->Weight = Update(
								InputLayer->Neurons[x]->Connections[o]->Weight,
								Learning_Rate,
								(AverageError[1][o]
										* InputLayer->Neurons[x]->GetOutput()));
					}
				}

			} else {
				for (int x = 0; x < HiddenLayers[e - 1]->Neurons.size(); x++) {
					for (int o = 0;
							o
									< HiddenLayers[e - 1]->Neurons[x]->Connections.size();
							o++) {

						HiddenLayers[e - 1]->Neurons[x]->Connections[o]->Weight =
								Update(
										HiddenLayers[e - 1]->Neurons[x]->Connections[o]->Weight,
										Learning_Rate,
										(AverageError[e][o]
												* HiddenLayers[e - 1]->Neurons[x]->GetOutput()));

					}
				}
			}

		}

		if(Cost > 1000){
			return 0;
		}

		Cost = 0;

		loop ++;

		if(loop == 50){
			loop = 0;
		}

	}

	return 0;
}

int NeuralNetwork::Test() {

	double Stat = 0;

	for (int i = 0; i < 10000; i++) {
		int fail;
		int Answer;

		vector<double> Inputs = ReadTraining(&fail, i, &Answer);

		if (fail == 1) {
			return 1;
		}

		int guess;

		vector<double> Outputs = Fire(Inputs);

		for(int l = 0; l < Outputs.size(); l++){
			if(Outputs[l] > 0.5){
				guess = l;
			}
		}

		if(guess == Answer){
			Stat++;
		}


	}

	cout << "Neural Network answered " << Stat <<"/10000 correctly" << endl;

	Stat /= 10000;

	cout << "Score: " << Stat << "%" << endl;

	return 0;
}

