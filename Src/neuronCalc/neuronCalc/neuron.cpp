#include "stdafx.h"
#include "neuron.h"
#include<math.h>
#include "stdlib.h"

neuron::neuron()
{
	
	sum = 0.0;
	q = 0.0;
	for (int i = 0; i < 128; i++) {
		weightAry[i] = (double)rand()/ (double)RAND_MAX;
	}
	
}
neuron::~neuron()
{
}
/*private*/
double neuron::sigmoid(double gain, double x){
	return 1.0 / (1.0 + exp(-gain * x));
}
double neuron::steep(double mu, double x, double y) {
	static double y0;
	static double x0;
	double y1 = y;
	double x1 = x;
	if (x0 != x1) {
		x = x - mu * (y0 - y1) / (x0 - x1);
	};
	x0 = x1;
	y0 = y1;

	return x;
}
/*public*/
void neuron::setInputLayerSize(int size) {
	inputLayerSize = size;
	return;
}
void neuron::setSigmoidGain(double gain) {
	sigmoidGain = gain;
	return;
}
void neuron::setErr(double err) {
	this->err = err;
	return;
}
void neuron::setAns(double ans) {
	this->ans = ans;
	return;
}
double neuron::getAns() {
	return this->ans;
}
double neuron::getErr() {
	return err;
}
double neuron::getInput(int inputFrom) {
	return inputAry[inputFrom];
}
void neuron::reset() {
	sum = 0;
	err = 0;
	return;
}
void neuron::input(int inputFrom, double u)
{
	if (u == 0) {
		sum = sum;
	}
	else {
		inputAry[inputFrom] = u * weightAry[inputFrom];
		sum += inputAry[inputFrom];
	}
	return;
}
void neuron::calc() {
	double u;
	u = 2 * sum / inputLayerSize - 1.0;
	q = sigmoid(sigmoidGain, u);
	return;
}
double neuron::output()
{
	return q;
}
void neuron::feedback(double mu, int i, double y) {
	weightAry[i] = steep(mu, weightAry[i], y);
	return;
}