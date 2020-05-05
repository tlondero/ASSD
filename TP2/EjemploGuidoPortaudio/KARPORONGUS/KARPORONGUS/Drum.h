#pragma once
#include <vector>
#include "Instrument.h"
#include "General.h"

class Drum :public Instrument
{
public:
	Drum( double rf_,double prob_);
	~Drum();
	double getSample(void);
	std::vector<double> generateNote(double duration, double pitch, double Normvelocity, double cutFactor);
private:
	double prob;
	double rf;
	double startSample;
	int currentSample;
	double previousSample;
	std::vector <double> waveTable;
};

