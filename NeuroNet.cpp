#include "NeuroNet.h"
#include "Neuron.h"
#include "Math.h"
#include <iostream>
double NeuroNet::InputNeuron::getSignal()
{
	return value;
}

void NeuroNet::InputNeuron::train(const double& err)
{
	return;
}

NeuroNet::NeuroNet(const std::vector<double>& norm,
	const std::vector<int>& architecture)
{
	normalize_coef = norm;
	
	// InputLayot charging
	for (int i = 0; i < architecture[0]; i++) {
		inputLayout.push_back(new InputNeuron());
	}

	// Input+Output layout
	if (architecture.size() == 2) {
		for (int i = 0; i < architecture[1]; i++) {
			std::vector<Neuron::Dendrit> temp;
			for (InputNeuron* n : inputLayout) {
				temp.push_back(Neuron::Dendrit(n));
			}
			outputLayout.push_back(Neuron(temp));
		}
	}

	// 1 hidden layout exist
	if (architecture.size() == 3) {
		hiddenLayout.push_back(std::vector<Neuron*>());
		for (int i = 0; i < architecture[1]; i++) {
			std::vector<Neuron::Dendrit> temp;
			for (InputNeuron* n : inputLayout) {
				temp.push_back(Neuron::Dendrit(n));
			}

			hiddenLayout[0].push_back(new Neuron(temp));
		}

		for (int i = 0; i < architecture[2]; i++) {
			std::vector<Neuron::Dendrit> temp;
			for (Neuron* n : hiddenLayout[0]) {
				temp.push_back(Neuron::Dendrit(n));
			}

			outputLayout.push_back(Neuron(temp));
		}


	}

	// more then 1 hidden layout exist
	if (architecture.size() > 3) {
		hiddenLayout.push_back(std::vector<Neuron*>());

		for (int i = 0; i < architecture[1]; i++) {
			std::vector<Neuron::Dendrit> temp;
			for (InputNeuron* n : inputLayout) {
				temp.push_back(Neuron::Dendrit(n));
			}
			hiddenLayout[0].push_back(new Neuron(temp));
		}

		for (int i = 2; i < architecture.size() - 1; i++) {
			hiddenLayout.push_back(std::vector<Neuron*>());

			for (int j = 0; j < architecture[i]; j++) {
				std::vector<Neuron::Dendrit> temp;
				for (Neuron* n : hiddenLayout[i-2]) {
					temp.push_back(Neuron::Dendrit(n));
				}

				hiddenLayout[i-1].push_back(new Neuron(temp));
			}
		}

		for (int i = 0; i < architecture[architecture.size()-1]; i++) {
			std::vector<Neuron::Dendrit> temp;
			for (Neuron* n : hiddenLayout[hiddenLayout.size()-1]) {
				temp.push_back(Neuron::Dendrit(n));
			}

			outputLayout.push_back(Neuron(temp));
		}
	}
}

NeuroNet::~NeuroNet()
{
	for (std::vector<Neuron*> n_vec : hiddenLayout) {
		{
			for (Neuron* n : n_vec) {
				delete n;
			}
		}
	}
	for (InputNeuron* n : inputLayout) {
		delete n;
	}
}

std::vector<double> NeuroNet::feedforward(
	const std::vector<double>& x_train,
	const std::vector<double>& y_train)
{
	std::vector<double> result;
	std::vector<double> x = this->normalize(x_train);
	for (int i = 0; i < inputLayout.size(); i++) {
		inputLayout[i]->value = x[i];
	}

	for (Neuron& n : outputLayout) {
		result.push_back(n.getSignal());
	}

	train(vector_diff(y_train,result));
	return result;
}

std::vector<double> NeuroNet::predict(const std::vector<double>& x_test)
{
	std::vector<double> result;
	std::vector<double> x = this->normalize(x_test);
	for (int i = 0; i < inputLayout.size(); i++) {
		inputLayout[i]->value = x[i];
	}

	for (Neuron& n : outputLayout) {
		result.push_back(n.getSignal());
	}
	return result;
}

void NeuroNet::train(const std::vector<double>& err)
{
	for (int i = 0; i < outputLayout.size(); i++)
	{
		outputLayout[i].train(err[i]);
	}	
}

std::vector<double> NeuroNet::normalize(const std::vector<double>& x)
{
	return vector_diff(x, normalize_coef);
}

void NeuroNet::testing()
{
	std::cout << "Input:\n";
	for (InputNeuron*& n : inputLayout) {
		std::cout << n << " ";
	}
	std::cout << "\nHidden:\n";
	for (int i = 0; i < hiddenLayout.size(); i++) {
		std::cout << i << " layer\n";
		for (int j = 0; j < hiddenLayout[i].size(); j++)
		{
			std::cout << hiddenLayout[i][j]<<" "<< hiddenLayout[i][j]->bias<<"\n";
			for (int k = 0; k < hiddenLayout[i][j]->dendrits.size(); k++) {
				std::cout << "  " << hiddenLayout[i][j]->dendrits[k].inputNeuron<<" "<< hiddenLayout[i][j]->dendrits[k].weight<<"\n";
			}
		}
	}
	std::cout << "Output:\n";
	for (int j = 0; j < outputLayout.size(); j++)
	{
		std::cout << j<< ")"<< outputLayout[j].bias<<"\n";
		for (int k = 0; k < outputLayout[j].dendrits.size(); k++) {
			std::cout << "  " << outputLayout[j].dendrits[k].inputNeuron << " " << outputLayout[j].dendrits[k].weight << "\n";
		}
	}
}
