#pragma once
#include <vector>
#include "Instrument.h"
#include "..\General.h"

class Drum :public Instrument
{
public:
	Drum( );
	void setParams(double rf_, double prob_);
	~Drum();
	double getSample(void);
	std::vector<double> generateNote(double duration, double pitch, double Normvelocity, double cutFactor);
	// ponele que con pitch 20 da un redoblante
private:
	double prob;
	double rf;
	double startSample;
	int currentSample;
	double previousSample;
	std::vector <double> waveTable;
};

