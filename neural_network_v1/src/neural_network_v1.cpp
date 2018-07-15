//============================================================================
// Name        : neural_network_v1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
/*
#include "header.h"
using namespace std;

//probably a good idea as well to include the bias value in each neuron's input since bias oughtn't be constant

//tanh is already present in math.h

//sigmoid function
double sigmoid(double x){
	return 1/(1+exp(-x));
}

//The ReLU function, overloaded for leaky variants (e.g. y=0.01)
double relu(double x, double y = 0){
	if(x < 0){
		return y*x;
	} else {
		return x;
	}
}

//derivatives
double dsigmoid(double x){
	return sigmoid(x)*(1-sigmoid(x));
}

double dtanh(double x){
	return 1-(tanh(x)^2);
}

double drelu(double x, double y = 0){
	if(x < 0){
		return y;
	} else {
		return 1;
	}
}

//backprop
//returned value is the partial derivative of the weights
//and so the algorithm will subtract a scaled version of this returned vector to allow for backproping
vector<double> bp_sigmoid(vector<double> inputs){
	vector<double> output (inputs.size());
	for(int i=0; i<output.size; i++){
		output[i] = dsigmoid(inputs[i]);
	}
	return output;
}

//same deal with relu and tanh
vector<double> bp_tanh(vector<double> inputs){
	vector<double> output (inputs.size());
	for(int i=0; i<output.size; i++){
		output[i] = dtanh(inputs[i]);
	}
	return output;
}

vector<double> bp_relu(vector<double> inputs, double y = 0){
	vector<double> output (inputs.size());
	for(int i=0; i<output.size; i++){
		output[i] = drelu(inputs[i], y);
	}
	return output;
}


double dot(vector<double> v1, vector<double> v2){
	return inner_product(v1.begin(), v1.end(), v2.begin(),0);
}

struct layerinfo{
	int neurons;
	int act_fn; // 1 for tanh, 2 for sigmoid, 3 for relu
	double param;
	double learn_rate;
};

//we should use vectors of vectors here
//better; an actually viable cost fn regardless of act fn
double cost(vector<vector<double>> inputs, vector<double> weights, vector<double> results, int n, double param){
	double dprod = 0;
	double sum = 0;
	int i=0;
	for(int i=0; i<inputs.size(); i++){
		dprod = dot(inputs[i], weights);
		sum += (results[i]-dprod)^2;
	}
	return -1/n * sum;
}



class Neuron {
public:
	int bias;
	//The initial value applied to the output, which can (and probably should) be changed

	int output;
	//The output value calculated for each neuron

	vector<Connection *> Connections; //makes more sense if this is a connection from previous neurons
	//A vector containing each of a neurons connections
	//what the actual fuck is this shit

	void set_activation_function();
	//This sets the activation function for the neuron, this is essential in creating an output value.

	void set_weights();
	//Sets the weights of each of the neuron's connections

	void calculate_output();
	//determines the output of the neuron using the weights from its connections. The input value is the sum of all the outputs of the neurons in the last layer times the weights of their individual connections plus their individual biases. This is all put into the activation function and an output is calculated

};

struct Layer{
	vector<Neuron *> Neurons;
	Layer *nextLayer;
	Layer *prevLayer;
};
//Contains a vector of Neurons, and a pointer to the next and previous layers.

//what the actual fuck is this shit
// why is this even here - surely it ought to be easier to just implement vector<double> weight and vector<Neuron*> prev/next neurons
struct Connection {
	double weight; // why was this int
	//Neuron *nextNeuron;
	Neuron *prevNeuron;
};
//Contains a pointer to the two neurons being connected, and the weight value associated with the connection used to calculate the output of the next neuron.

class Neural_Network{

	Layer *input;
	//The input layer that contains all pixels in the 28 x 28 image

	Layer *output;
	//The output layer that will determine the number identification

	vector<Layer *> hidden;
	//A vector of hidden layers that apply the cost function to determine the output


	void connect_layers();
	//Connects each of the layers from input → hidden → output

	void create_neurons();
	//Creates the desired number of neurons in each of the layers

	void connect_neurons();
	//Connects each of the neurons in one layer to each of the neurons in the next layer

};

int main2(int argc, char* argv[]) {

	// prompts the user to enter a neural network configuration
	/*
	 * the user should enter the number of total layers first (minimum of 2, max 10)
	 * for each layer, the user enters its details (# of neurons, activation fn, parameters)
	 * this is best separated by a line
	 * the CLI should just handle the number of layers
	 * defaults:
	 * # neurons = sqrt(# neurons from prev layer)
	 * activation fn: relu, y=0
	 * params for relu: y=0
	 *

	int n_layers = atoi(argv[1]);
	layerinfo layers[n_layers];
	for (int i=0; i<n_layers; i++){
		cin >> layers[i].neurons;
		cin >> layers[i].act_fn;
		cin >> layers[i].param;
		cin >> layers[i].learn_rate;
	}

	//partial derivatives
	vector<double> weights;
	vector<double> inputs;
	vector<vector<double>> asdf;

	double dotprod = inner_product(inputs.begin(), inputs.end(), weights.begin(),0);
	return 0;

}
*/
