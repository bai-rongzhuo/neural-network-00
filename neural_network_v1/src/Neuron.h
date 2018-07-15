
#ifndef NEURON_H_
#define NEURON_H_

#include <vector>
#include "Connection.h"
#include <cmath>

using namespace std;

class Neuron {

private:
	int ActivationFunction;
	double Input;
	double Output;
	double Parameter;
public:
	vector<Connection*> Connections;
	Neuron();
	~Neuron();
	double GetWeight(int ConnectionNeuronNum) const;
	int GetActivationFunction() const;
	void SetConnectionWeight(int ConnectionNeuronNum, double Weight);
	void SetActivationFunction(int ActivationFN);

	double GetOutput() const;
	void SetOutput(double Out);
	void SetInput(double In);
	void Fire();
	double GetInput();

};

#endif /* NEURON_H_ */
