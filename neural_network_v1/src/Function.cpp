#include <vector>
#include <cmath>
#include <numeric>
#include <iostream>
#include "Function.h"

using namespace std;

double Sigmoid(double x) {

	return static_cast<double>(1 / (1 + exp(-x)));
}

//The ReLU function, overloaded for leaky variants (e.g. y=0.01)
//This function returns x for x>0 and y for x<0, where -1<y<=0
double RELU(double x, double y) {
	if (x < 0) {
		return y * x;
	} else {
		return x;
	}
}


//derivative of the sigmoid function wrt x
double DerivativeSigmoid(double x) {
	return Sigmoid(x) * (1 - Sigmoid(x));
}

//derivative of the tanh (hyperbolic tangent) function wrt x
double DerivativeTanh(double x) {
	return 1 - pow(tanh(x), 2);
}

//derivative of the ReLU function wrt x and y
double DerivativeRELU(double x, double y) {
	if (x < 0) {
		return y;
	} else {
		return 1;
	}
}

//calculates the partial derivatives of the sigmoid function for a vector
//returns a vector of doubles corresponding to each partial derivative
vector<double> bp_sigmoid(vector<double> inputs) {
	vector<double> output(inputs.size());
	for (int i = 0; i < output.size(); i++) {
		output[i] = DerivativeSigmoid(inputs[i]);
	}
	return output;
}

//calculates the partial derivatives of the tanh function
vector<double> bp_tanh(vector<double> inputs) {
	vector<double> output(inputs.size());
	for (int i = 0; i < output.size(); i++) {
		output[i] = DerivativeTanh(inputs[i]);
	}
	return output;
}

//calculates the partial derivatives of the relu function
vector<double> bp_relu(vector<double> inputs, double y) {
	vector<double> output(inputs.size());
	for (int i = 0; i < output.size(); i++) {
		output[i] = DerivativeRELU(inputs[i], y);
	}
	return output;
}

//calculates the dot product between two vectors of doubles
double dot(vector<double> v1, vector<double> v2) {
	return inner_product(v1.begin(), v1.end(), v2.begin(), 0);
}

//calculates the error function of the neuron (sum of squares)
double cost(vector<vector<double>> inputs, vector<double> weights,
		vector<double> results, int n, double param) {
	double dprod = 0;
	double sum = 0;
	for (int i = 0; i < inputs.size(); i++) {
		dprod = dot(inputs[i], weights);
		sum += pow((results[i] - dprod), 2);
	}
	return -1 / n * sum;
}

//the softmax function for the final layer
double SoftMax(double Input, vector<double> Inputs) {

	double sum = 0;

	for (int i = 0; i < Inputs.size(); i++) {
		sum += exp(Inputs[i]);
	}

	Input = exp(Input);

	double Output = Input / sum;

	return Output;

}

//the cost function
double Mean_Cost(vector<double> Actual, vector<double> Answers) {

	double sum = 0;

	for (int i = 0; i < Actual.size(); i++) {

		sum += pow(Actual[i] - Answers[i],2);

	}

	return sum;

}

//update function
double Update(double Intial, double LearningRate, double Derivative) {
	double final;

	final = Intial - (LearningRate * Derivative);

	return final;
}

//The error function in the final layer
vector<double> ErrorInOuterLayer(vector<double> Inputs, vector<double> Answer,
		vector<double> Outputs) {

	vector<double> Error;

	for(int i = 0; i < Inputs.size(); i++){

		Error.push_back(((Outputs[i] - Answer[i])*Inputs[i]));

	}

return Error;
}

//the error function in the previous layer
vector<double> ErrorInPrevLayer(vector<vector<double>> Weights, vector<double> ErrorInNextLayer,
		vector<double> Outputs) {

	vector<double> Error;

	for(int i = 0; i < Weights.size(); i++){

		double sum = 0;

		for(int j = 0; j < Weights[i].size(); j ++){

			sum += Weights[i][j] * ErrorInNextLayer[j];

		}

		double In = DerivativeSigmoid(Outputs[i]);

		Error.push_back((sum * In));

	}

	return Error;

}


double ChangeInWeight(double ChangeinNextLayer,double Output){
	double NewWeight = ChangeinNextLayer * Output;

	return NewWeight;
}

//cross-entropy (-log) cost function
double Cross_Entropy(vector<double> Answers, vector<double> Actual){

	double sum;

	for(int i = 0; i < Answers.size();i++){

		sum += -(Actual[i]*log(Answers[i])+(1-Actual[i])*log(1-Answers[i]));

	}

	return sum;
}







