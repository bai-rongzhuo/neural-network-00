

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include "Neuron.h"
using namespace std;

class Neuron;

struct Connection{
	double Weight;
	Neuron* ConnectedNeuron;
};



#endif /* CONNECTION_H_ */
