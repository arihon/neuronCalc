#pragma once
class neuron
{
public:
	neuron();
	~neuron();
private:
	int inputLayerSize;
	double sigmoidGain;
	double sum;
	double weightAry[128];
	double inputAry[128];
	double q;
	double err;
	double ans;

	double sigmoid(double gain, double x);
	double steep(double mu, double x, double y);

public:
	void setInputLayerSize(int size);
	void setSigmoidGain(double gain);
	void setErr(double err);
	void setAns(double ans);
	double getAns();
	double getErr();
	double getInput(int inputFrom);
	void reset();
	void input(int inputFrom, double u);
	void calc();
	double output();
	void feedback(double mu,int i, double y);
};
