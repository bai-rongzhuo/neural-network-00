#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <vector>
using namespace std;

//activation functions
//tanh is included in the standard math library <numeric>
double Sigmoid(double x);
double RELU(double x, double y);
//derivatives
double DerivativeSigmoid(double x);
double DerivativeTanh(double x);
double DerivativeRELU(double x, double y);
//partial derivates for backpropagaion (should not be used, I screwed up, ignore pls)
vector<double> bp_sigmoid(vector<double> inputs);
vector<double> bp_tanh(vector<double> inputs);
vector<double> bp_relu(vector<double> inputs, double y);
//dot product
double dot(vector<double> v1, vector<double> v2);
//cost function (sum of squares)
double cost(vector<vector<double>> inputs, vector<double> weights,
		vector<double> results, int n, double param);
//softmax for the final layer
double SoftMax(double Input, vector<double> Inputs);
//mean cost function
double Mean_Cost(vector<double> Actual, vector<double> Answers);
//update layer
double Update(double Intial, double LearningRate, double Derivative);
//errors in other layers
vector<double> ErrorInOuterLayer(vector<double> Inputs, vector<double> Answer,
		vector<double> Outputs);
vector<double> ErrorInPrevLayer(vector<vector<double>> Weights,
		vector<double> ErrorInNextLayer, vector<double> Outputs);
double ChangeInWeight(double ChangeinNextLayer, double Output);
double Cross_Entropy(vector<double> Answers, vector<double> Actual);

#endif /* FUNCTION_H_ */
