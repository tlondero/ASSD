#pragma once
#include <vector>
using namespace std;
#include "Instrument.h"
#include "..\General.h"

class GuitarImproved
{
public:
	GuitarImproved(double rf);
	~GuitarImproved();
	vector<double> generateNote(double duration, double pitch, double Normvelocity, double cutFactor, char noiseType);
	vector<double> generateNoteElectric(double duration, double pitch, double Normvelocity, double cutFactor, char noiseType);
	double getSample();

private:
	double a;
	double b;
	double rf;
	double startSample;
	int currentSample;
	double previousSample;
	vector <double> waveTable;
};

