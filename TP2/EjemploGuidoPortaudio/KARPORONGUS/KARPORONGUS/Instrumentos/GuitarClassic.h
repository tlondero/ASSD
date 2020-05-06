#pragma once
#include <vector>
using namespace std;
#include "Instrument.h"
#include "..\General.h"
class GuitarClassic: public Instrument
{
public:
	GuitarClassic();
	//pitch= frecuencia deseada, fs = sample rate, rf controla el decay time, para que sea una guitarra podes elegir el rf que quieras mientras sea igual a 1
	~GuitarClassic();
	void setParam(double rf);
	vector<double> generateNote(double duration, double pitch,double Normvelocity, double cutFactor,char noiseType);
	double getSample();

private:
	double rf;
	double startSample;
	int currentSample;
	double previousSample;
	vector <double> waveTable;
};

