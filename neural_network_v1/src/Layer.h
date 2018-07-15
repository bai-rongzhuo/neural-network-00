

#ifndef LAYER_H_
#define LAYER_H_

#include <vector>
#include "Neuron.h"

using namespace std;

struct Layer{
	vector<Neuron*> Neurons;
	int NumberOfNeurons;
	int LayerNumber;
	double bias;
	Layer *nextLayer;
	Layer *prevLayer;
};



#endif /* LAYER_H_ */
