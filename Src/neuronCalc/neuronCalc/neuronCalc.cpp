// neuronCalc.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "neuron.h"

int main()
{
	static const double sigmoidGain		=  1.0;
	static const int	inputLayerSize	=   32;
	static const int	hidenLayerSize	= 1024;
	static const int	outputLayerSize	=   16;
	neuron inputLayer [ inputLayerSize];
	neuron hidenLayer [ hidenLayerSize];
	neuron outputLayer[outputLayerSize];

	for (int i = 0; i < inputLayerSize; i++) {
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
    return 0;
}

