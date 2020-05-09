#pragma once
#include "Instrument.h"
#include <vector>
#include "..\General.h"
class Banjo
{
public:
	Banjo();
	~Banjo();
	double getSample();
	std::vector<double> generateNote(double duration, double pitch, double Normvelocity, double cutFactor, char noiseType);
private:
	double a;
	double b;
	double rf;
	double startSample;
	int currentSample;
	double previousSample;
	std::vector <double> waveTable;
};

