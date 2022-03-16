#ifndef NEURONET_H
#define NEURONET_H
#include "Neuron.h"

class NeuroNet {
public:
	class InputNeuron : public Neuron {
	public:
		double getSignal();
		void train(const double& err);
	};

	NeuroNet(const std::vector<double>& norm,
		const std::vector<int>& architecture);
	~NeuroNet();
	std::vector<double> feedforward(
		const std::vector<double>& x,
		const std::vector<double>& y);
	std::vector<double> predict(const std::vector<double>& x);
	void train(const std::vector<double>& err);
	std::vector<double> normalize(const std::vector<double>& x);

	void testing();

	std::vector<Neuron> outputLayout;
	std::vector<std::vector<Neuron*>> hiddenLayout;
	std::vector<InputNeuron*> inputLayout;
	std::vector<double> normalize_coef;
};

#endif