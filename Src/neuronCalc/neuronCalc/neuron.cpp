#include "neuron.h"
#include<math.h>


neuron::neuron(int inputLayerSize, double sigmoidGain)
{
	/*コンストラクタ*/
	size = inputLayerSize;
	gain = sigmoidGain;
	sum = 0.0;
	q = 0.0;
	for (int i = 0; i < size; i++) {
		weight[i] = 1.0;
	}
}


neuron::~neuron()
{
}
/*private*/
double neuron::sigmoid(double gain, double x)
{
	return 1.0 / (1.0 + exp(-gain * x));
}
/*public*/
void neuron::reset() {
	sum = 0;
	return;
}
void neuron::input(int inputFrom, double u)
{
	sum += u * weight[inputFrom];
	return;
}
void neuron::calc() {
	q = sigmoid(gain, sum);
	return;
}
double neuron::output()
{
	return q;
}