#include "Math.h"
#include "Neuron.h"
#include <iostream>
/*
Neuron::Neuron(std::vector<double> weights, double bias) {
	this->weights = weights;
	this->bias = bias;
}
double Neuron::feedforward(const std::vector<double>& x) {
	double total = scalar_mul(weights, x) + bias;
	return sigmoid(total);
}
*/

Neuron::Neuron(const double& value) {
	this->value = value;
}

double Neuron::getSignal() {
	double result=0;
	for (Dendrit d : dendrits) {
		result += d.inputNeuron->getSignal() * d.weight;
	}
	value = sigmoid(result);
	return value;
}

void Neuron::train(const double& err)
{
	double learn_rate = 1;
	for (Dendrit& d : dendrits) {
		d.inputNeuron->train(err * d.weight);
		d.weight += learn_rate * err * d.inputNeuron->value * sigmoid_der(value);
	}
//	bias += learn_rate * err * sigmoid_der(value);
}

Neuron::Dendrit::Dendrit(Neuron* input) {
	this->inputNeuron = input;
	this->weight = double(rand())/RAND_MAX;
}

Neuron::Neuron(const std::vector<Dendrit>& dendrits, const double& bias) {
	this->dendrits = dendrits;
	this->bias = bias;
}

Neuron::Neuron(const Neuron& n)
{
	this->dendrits = n.dendrits;
	this->bias = n.bias;
}
