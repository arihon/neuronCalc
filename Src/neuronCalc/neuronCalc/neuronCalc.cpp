// neuronCalc.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//
#include "stdafx.h"
#include <iostream>
#include "stdlib.h"
#include <bitset>
#include "neuron.h"
#include "math.h"
using namespace std;


bool uint2bool(int n, unsigned int x) {
	unsigned int x_work;
	x_work = x >> n;
	x_work = x & 0x0001;
	return x_work != 0;
}
unsigned int bool2uint(int n, unsigned int x, bool b) {
	unsigned int work;
	unsigned int q;
	if (b) {
		work = pow(2 , n);
		q = x | work;
	}
	else{
		q = x;
	}
	return  q;
}
double bool2double(bool x) {
	double q;
	if (x) {
		q = 1.0;
	}
	else {
		q = 0.0;
	}
	return q;
}

int main()
{
	static const double sigmoidGain		=  5.0;
	static const int	inputLayerSize	=   64;
	static const int	hidenLayerSize	=  128;
	static const int	outputLayerSize	=   32;
	static const double mu = 0.001;

	neuron inputLayer [ inputLayerSize];
	neuron hidenLayer [ hidenLayerSize];
	neuron outputLayer[outputLayerSize];

	for (int i = 0; i < inputLayerSize-1; i++) {
		inputLayer[i].setInputLayerSize(1);
		inputLayer[i].setSigmoidGain(sigmoidGain);
	}
	for (int i = 0; i < hidenLayerSize; i++) {
		hidenLayer[i].setInputLayerSize(inputLayerSize);
		hidenLayer[i].setSigmoidGain(sigmoidGain);
	}
	for (int i = 0; i < outputLayerSize; i++) {
		outputLayer[i].setInputLayerSize(hidenLayerSize);
		outputLayer[i].setSigmoidGain(sigmoidGain);
	}
	
	bool u[hidenLayerSize];
	int x0,x1;
	bool en = true;
	int count=0;
	while (en) {
		//createInputData
		/*
		x0 = rand() % 10;
		x1 = rand() % 10;
		*/
		x0 = 3;
		x1 = 4;
		
		bitset<32> in0(x0);
		bitset<32> in1(x1);
		bitset<32> ans(x0+x1);
		for (int j = 0; j < 32; j++) {
			u[j   ] = in0[j];
			u[j+32] = in1[j];
		}
		//inputLayer
		for (int i_in = 0; i_in < inputLayerSize; i_in++) {
			double in;
			if (u[i_in]) {
				in = 1.0;
			}
			else {
				in = 0.0;
			}
			inputLayer[i_in].reset();
			inputLayer[i_in].input(0, in);
			inputLayer[i_in].calc();
		}
		//hidenLayer
		for (int i_hd = 0; i_hd < hidenLayerSize; i_hd++) {
			hidenLayer[i_hd].reset();
			for (int i_in = 0; i_in < inputLayerSize; i_in++) {
				double u = inputLayer[i_in].output();
				hidenLayer[i_hd].input(i_in, u);
			}
			hidenLayer[i_hd].calc();
		}
		//outputLayer
		unsigned int out = 0;
		for (int i_ot = 0; i_ot < outputLayerSize; i_ot++) {
			outputLayer[i_ot].reset();
			for (int i_hd = 0; i_hd < hidenLayerSize; i_hd++) {
				double u = hidenLayer[i_hd].output();
				outputLayer[i_ot].input(i_hd, u);
			}
			outputLayer[i_ot].calc();
			if (outputLayer[i_ot].output() > 0.5) {
				out = bool2uint(i_ot, out, 1);
			}else {
				out = bool2uint(i_ot, out, 0);
			}
		}

		if (fabs(out - (x0 + x1)) == 0 ) {
			en = true;
		}

		//feedBack
		//outputLayer( ans - output )
		double errIn;
		double errOut;
		double ansOut;
		for (int i_ot = 0; i_ot < outputLayerSize; i_ot++) {
			ansOut = bool2double(ans[i_ot]);
			outputLayer[i_ot].setAns(ansOut);
			errOut = outputLayer[i_ot].output() - ansOut;
			errOut = pow(2, i_ot) * errOut;
			outputLayer[i_ot].setErr(errOut);
			for (int i_hd = 0; i_hd < hidenLayerSize; i_hd++) {
				errIn  = fabs(outputLayer[i_ot].getInput(i_hd) - ansOut);
				outputLayer[i_ot].feedback(mu, i_hd, errIn);
			}
		}
		// hidenLayer
		for (int i_hd = 0; i_hd < hidenLayerSize; i_hd++) {		
			double sum = 0,tmp;
			for (int i_ot = 0; i_ot < outputLayerSize; i_ot++) {
				tmp = outputLayer[i_ot].getInput(i_hd) - outputLayer[i_ot].getAns();
				sum += tmp;
			}
			errOut = sum;
			hidenLayer[i_hd].setErr(errOut);
			ansOut = hidenLayer[i_hd].output() - errOut;
			hidenLayer[i_hd].setAns(ansOut);
			for (int i_in = 0; i_in < inputLayerSize; i_in++) {
				errIn = fabs(hidenLayer[i_hd].getInput(i_in) - ansOut);
				hidenLayer[i_hd].feedback(mu, i_in, errIn);
			}
		}
		// inputLayer
		for (int i_in = 0; i_in < inputLayerSize; i_in++) {
			double sum = 0,tmp;
			for (int i_hd = 0; i_hd < hidenLayerSize; i_hd++) {
				tmp = hidenLayer[i_hd].getInput(i_in) - hidenLayer[i_hd].getAns();
				sum += tmp;
			}
			errOut = sum;
			inputLayer[i_in].setErr(errOut);
			ansOut = inputLayer[i_in].output() - errOut;
			inputLayer[i_in].setAns(ansOut);
			errIn = fabs(inputLayer[i_in].getInput(0) - ansOut);
			inputLayer[i_in].feedback(mu,0,errIn);
		}

		//printf("%d:%d+%d = %d\n", count, x0, x1, out);
		if (count == 0) {
			printf("%5.d,",  (x0 + x1) - out);
			for (int n=0; n < 16; n++) {
				printf("%+.5lf,", outputLayer[n].getErr());
			}
			printf("\n");
		}
		count++;
		if (count > 9999)count = 0;
	}
    return 0;
}

