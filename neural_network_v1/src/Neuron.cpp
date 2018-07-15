#include <vector>
#include "Neuron.h"
#include <cmath>
#include <iostream>
#include "Function.h"
#include "Connection.h"
using namespace std;

Neuron::Neuron() {

	Output = 0;
	ActivationFunction = 2;
	Input = 0;
	Parameter = 0.1;

}

Neuron::~Neuron() {

}
/**
 * Returns the Weight of a Connection in form of a double
 */
double Neuron::GetWeight(int ConnectionNeuronNum) const {

	double Weight;

	Weight = Connections[(ConnectionNeuronNum + 1)]->Weight;

	return Weight;
}

/**
 * Returns an integer representing the activation function
 * 1 - for tanh function, 2 - sigmoid function, 3 - for ReLU function, 4 - for leaky ReLU function
 */
int Neuron::GetActivationFunction() const {
	int ActivationFn = ActivationFunction;
	return ActivationFn;
}

void Neuron::SetConnectionWeight(int ConnectionNeuronNum, double Weight) {

	Connections[(ConnectionNeuronNum - 1)]->Weight = Weight;

}
void Neuron::SetActivationFunction(int ActivationFN) {

	ActivationFunction = ActivationFN;

}

double Neuron::GetOutput() const {
	return Output;
}

void Neuron::Fire() {

	if (ActivationFunction == 1) {

		Output = tanh(Input);

	} else if (ActivationFunction == 2) {


		Output = Sigmoid(Input);

	} else if (ActivationFunction == 3) {

		Output = RELU(Input, 0);

	} else if(ActivationFunction == 4){

		Output = RELU(Input, Parameter);

	}

}

void Neuron::SetOutput(double Out){
	Output = Out;
}

void Neuron::SetInput(double In) {
	Input = In;
}

double Neuron::GetInput(){
	return Input;
}

