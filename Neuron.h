#ifndef NEURON_H
#define NEURON_H
#include <vector>
#include <ctime>

class Neuron
{
public:
    class Dendrit {
    public:
        double weight=0.1;
        Neuron* inputNeuron;

        Dendrit(Neuron* input = nullptr);
    };
    Neuron(const double& value = 0);
    Neuron(const std::vector<Dendrit>& dendrits,const double& bias=0);
    Neuron(const Neuron& n);

    virtual double getSignal();
    virtual void train(const double& err);

    double value=0;
    double bias=0;
    std::vector<Dendrit> dendrits;
};
#endif