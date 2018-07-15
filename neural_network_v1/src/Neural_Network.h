#ifndef NEURAL_NETWORK_H_
#define NEURAL_NETWORK_H_

#include <vector>
#include "Layer.h"

using namespace std;

class NeuralNetwork {

private:
	double Learning_Rate;
	Layer* InputLayer;
	vector<Layer*> HiddenLayers;
	Layer* OutputLayer;
public:

	NeuralNetwork();
	~NeuralNetwork();
	int GetNumberOfHiddenLayers() const;
	int GetNumberOfNeurons(int LayerNum) const;
	double GetLayerBias(int LayerNum) const;
	double GetConnectionWeight(int LayerNum, int NeuronNum,
			int ConnectionNeuronNum) const;
	int GetActivationFunction(int LayerNum, int NeuronNum) const;
	void SetNumberOfHiddenLayers(int NumOfHDDNLayers);
	void SetNumberOfNeurons(int LayerNum, int NumOfNeurons);
	void SetLayerBias(int LayerNum, double Bias);
	void SetConnectionWeight(int LayerNum, int NeuronNum,
			int ConnectionNeuronNum, double Weight);
	void SetActivationFunction(int LayerNum, int NeuronNum, int ActivationFN);

	void create_neurons(int num_of_hidden_layers, int input_neurons_per_layer, int hidden_neurons_per_layer, int output_neurons_per_layer);
	void connect_layers(int num_of_hidden_layers);
	void connect_neurons();

	vector<double> Fire(vector<double> Inputs);
	int Train();
	int Test();
};

#endif /* NEURAL_NETWORK_H_ */
