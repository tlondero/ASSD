#pragma once
#include <vector>
using namespace std;

class Guitar
{
public:
	Guitar();
	//pitch= frecuencia deseada, fs = sample rate, rf controla el decay time, para que sea una guitarra podes elegir el rf que quieras mientras sea igual a 1
	~Guitar();
	vector<double> composeSound(double cutFactor,int duration, int pitch, int SampleRate, double rf,double Normvelocity);
	double getSample(double rf);

private:

	double startSample;
	int currentSample;
	double previousSample;
	vector <double> waveTable;
	vector<double> Guitarsound;
};

