#pragma once
class neuron
{
public:
	neuron();
	~neuron();
private:
	int inputLayerSize;
	double sigmoidGain;
	int sum;
	double weight[1024];
	double q;

	double sigmoid(double gain, double x);

public:
	void setInputLayerSize(int size);
	void setSigmoidGain(double gain);
	void reset();
	void input(int inputFrom, double u);
	void calc();
	double output();
};
