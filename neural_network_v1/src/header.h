/*
 * header.h
 *
 *  Created on: Apr 24, 2018
 *      Author: baijack273
 */
// newest purchases are added to the head, and oldest purchase taken from the end
//this is a fifo thing

#ifndef HEADER_H_
#define HEADER_H_

#include <math.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <string.h>
#include <iomanip>
#include <ctype.h>
#include <vector>
#include <numeric>

/*
struct Layer{
	vector<Neuron *> Neurons;
	Layer *nextLayer;
	Layer *prevLayer;
};
//Contains a vector of Neurons, and a pointer to the next and previous layers.


struct Connection {
	int weight;
	Neuron *nextNeuron;
	Neuron *prevNeuron;
};
//Contains a pointer to the two neurons being connected, and the weight value associated with the connection used to calculate the output of the next neuron.
*/

struct Layer;
struct Connection;
using namespace std;

#endif /* HEADER_H_ */
