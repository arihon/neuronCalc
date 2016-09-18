#pragma once
class neuron
{
public:
	neuron(int inputLayerSize, double sigmoidGain);
	~neuron();
private:
	int size;
	double gain;
	int sum;
	double weight[1024];
	double q;

	double sigmoid(double gain, double x);

public:
	void reset();
	void input(int inputFrom, double u);
	void calc();
	double output();
};
