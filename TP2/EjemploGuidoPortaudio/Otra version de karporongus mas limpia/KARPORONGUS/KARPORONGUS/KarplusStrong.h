#pragma once
#include <vector>
class KarplusStrong
{
public:
	KarplusStrong();
	KarplusStrong(std::vector<double> input, int pitch, double decay, int TotalSamples);// pitch == frecuencia, dependiendo de la M y el periodo de muestreo tengo la frecuencia. decay es la constante de la envolvente
	~KarplusStrong();

	void calcY(void);//calcula la salida.
//	Getters
	std::vector<double>  gety();
	std::vector<double> getInput();
	int getPitch();
	double getDecay();
//	Setters
	void setPitch(int M);
	void setDecay(double alfa);
	void setInput(std::vector<double> input);

private:
	std::vector<double> x;
	std::vector<double> y;
	int pitch;
	double decay;
	int N;

};

